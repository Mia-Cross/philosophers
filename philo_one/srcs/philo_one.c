/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_one.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lemarabe <lemarabe@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/08/27 18:30:38 by lemarabe          #+#    #+#             */
/*   Updated: 2020/09/08 20:53:23 by lemarabe         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo_one.h"

void *simulation_control(void *arg)
{
	t_philo *philo;

	philo = (t_philo *)arg;
	update_death_clock(&philo->death, philo->time->to_die);
	while (*philo->quit)
	{
		pthread_mutex_lock(&philo->state);
		if (check_death_clock(philo->death))
		{
			pthread_mutex_unlock(&philo->state);
			usleep(2000);
		}
		else
		{
			display_action(philo, "died\n");
			*philo->quit = 0;
			pthread_mutex_unlock(&philo->state);
		}
	}
	return (NULL);
}

void *philo_life(void *arg)
{
    t_philo *philo;

    philo = (t_philo *)arg;
    while (*philo->quit)
    {
		pthread_mutex_lock(philo->fork_right);
		display_action(philo, "has taken a fork\n");
		pthread_mutex_lock(philo->fork_left);
		display_action(philo, "has taken a fork\n");
		pthread_mutex_lock(&philo->state);
		display_action(philo, "is eating\n");
		if (check_death_clock(philo->death))
			update_death_clock(&philo->death, philo->time->to_die);
		pthread_mutex_unlock(&philo->state);
		if (philo->laps_left >= 0)
			philo->laps_left -= 1;
		if (!philo->laps_left && *philo->quit > 0)
			*philo->quit -= 1;
		usleep(philo->time->to_eat);
		pthread_mutex_unlock(philo->fork_right);
		pthread_mutex_unlock(philo->fork_left);
		display_action(philo, "is sleeping\n");
    	usleep(philo->time->to_sleep);
		display_action(philo, "is thinking\n");
    }
    return (NULL);
}


void start_threads(t_args *args)
{
	int i;

	i = -1;
	gettimeofday(&args->time.start, NULL);
	while (++i < args->nb_philo)
	{
		pthread_create(&args->philo[i].thread, NULL, &philo_life, &args->philo[i]);
		pthread_create(&args->philo[i].control, NULL, &simulation_control, &args->philo[i]);
	//	pthread_detach(args->philo[i].thread);
		usleep(args->time.to_eat);
	//	usleep(1000);
	}
}

void wait_for_all_threads(t_args *args)
{
	int i;

	i = -1;
	while (++i < args->nb_philo)
		pthread_join(args->philo[i].control, NULL);
	i = -1;
	while (++i < args->nb_philo)
		pthread_join(args->philo[i].thread, NULL);
}

int main(int ac, char **av)
{
    t_args  args;

    get_arguments(ac, av, &args);
    start_mutexes(&args);
    set_philosophers(&args);
	start_threads(&args);
//	while (args.quit)
//		usleep(1);
	wait_for_all_threads(&args);
	destroy_mutexes(&args);
	clean_and_exit(&args, 3, "gne");
	return (0);
}