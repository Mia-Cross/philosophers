#include "philo_two.h"

void *philo_control(void *arg)
{
	t_philo *philo;

	philo = (t_philo *)arg;
	update_death_clock(&philo->death, philo->time->to_die);
	/*if (philo->time->to_die < philo->time->to_eat)
		usleep(philo->time->to_die);
	else
		usleep(philo->time->to_eat); */
	while (*philo->quit)
	{
		sem_wait(philo->state);
		if (!check_death_clock(philo->death, philo->channel))
		{
			display_action(philo, "died\n");
			*philo->quit = 0;
			sem_post(philo->state);
		}
		else
		{
		//	update_death_clock(&philo->death, philo->time->to_die);
			sem_post(philo->state);
			usleep(1000);
		}
	}
	free(philo->name);
	return (NULL);
}

void *philo_life(void *arg)
{
    t_philo *philo;

    philo = (t_philo *)arg;
//	sem_wait(philo->state);
	pthread_create(&philo->control, NULL, &philo_control, philo);
    while (*philo->quit)
    {
		sem_wait(philo->forks);
		display_action(philo, "has taken a fork\n");
		sem_wait(philo->forks);
		display_action(philo, "has taken a fork\n");
        sem_post(philo->state);
	//	sleep(100);
		sem_wait(philo->state);
		display_action(philo, "is eating\n");
		update_death_clock(&philo->death, philo->time->to_die);
		if (philo->laps_left >= 0)
			philo->laps_left -= 1;
		//if (!philo->laps_left && *philo->quit > 0)
		if (!philo->laps_left)
			*philo->full += 1;
		usleep(philo->time->to_eat);
		sem_post(philo->forks);
		sem_post(philo->forks);
		display_action(philo, "is sleeping\n");
    	usleep(philo->time->to_sleep);
		display_action(philo, "is thinking\n");
    }
    return (NULL);
}


void detach_philo_threads(t_args *args)
{
	int i;

	i = -1;
	while (++i < args->nb_philo)
	{
		pthread_detach(args->philo[i].thread);
	//	pthread_detach(args->philo[i].control);
	}
}

void start_threads(t_args *args)
{
	int i;

	i = -1;
	while (++i < args->nb_philo)
	{
		pthread_create(&args->philo[i].thread, NULL, &philo_life, &args->philo[i]);
		//pthread_create(&args->philo[i].control, NULL, &philo_control, &args->philo[i]);
	}
}

int main(int ac, char **av)
{
	t_args  args;

    get_arguments(ac, av, &args);
	unlink_previous_semaphores(&args);
    start_semaphores(&args);
    set_philosophers(&args);
	start_threads(&args);
	detach_philo_threads(&args);
	while (args.quit)
		usleep(1);
    clean_and_exit(&args, (args.nb_philo + 3), "bye\n");
    return (0);
}