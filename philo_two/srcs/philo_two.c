#include "philo_two.h"

void *philo_life(void *arg)
{
    t_philo *philo;

    philo = (t_philo *)arg;
	update_death_clock(&philo->death, philo->time->to_die);
    while (philo->quit)
    {
        sem_wait(philo->forks);
		display_action(philo, "has taken a fork\n");
		sem_wait(philo->forks);
		display_action(philo, "has taken a fork\n");
		sem_wait(philo->state);
        sem_post(philo->state);
    	update_death_clock(&philo->death, philo->time->to_die);
		display_action(philo, "is eating\n");
		if (philo->laps_left > 0)
			philo->laps_left -= 1;
		usleep(philo->time->to_eat);
		sem_post(philo->forks);
		sem_post(philo->forks);
		display_action(philo, "is sleeping\n");
    	usleep(philo->time->to_sleep);
		display_action(philo, "is thinking\n");
    }
    return (NULL);
}

void *simulation_control(void *arg)
{
    t_args *args;
	int i;

	args = (t_args *)arg;
	while (args->quit)
	{
		usleep(10);
		i = -1;
		while (++i < args->nb_philo && args->quit)
		{
            if (!args->philo[i].laps_left)
			{
				if (args->quit > 0)
					args->quit -= 1;
				args->philo[i].laps_left = -1;
			}
			if (check_death_clock(args->philo[i].death))
			{
				sem_wait(args->philo[i].state);
				display_action(&args->philo[i], "died\n");
				args->quit = 0;
			}
		}
	}
	return (NULL);
}

int main(int ac, char **av)
{
	t_args  args;

    get_arguments(ac, av, &args);
    start_semaphores(&args);
    start_philo_threads(&args);
    write(1, "1", 1);
    pthread_create(&args.control, NULL, &simulation_control, &args);
    pthread_join(args.control, NULL);
    clean_and_exit(&args, 1, "bye\n");
    return (0);
}