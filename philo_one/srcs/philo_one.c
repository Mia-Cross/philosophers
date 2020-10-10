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

void *philo_routine(void *arg)
{
    t_philo *philo;

    philo = (t_philo *)arg;
	update_death_clock(&philo->death, philo->time->to_die);
    while (philo->laps_left)
    {
		display_action(philo->time->start, philo->name, "is thinking\n");
		pthread_mutex_lock(philo->fork_right);
		display_action(philo->time->start, philo->name, "has taken a fork\n");
		pthread_mutex_lock(philo->fork_left);
//		if (check_death_clock(philo->death))
		display_action(philo->time->start, philo->name, "has taken a fork\n");
    	update_death_clock(&philo->death, philo->time->to_die);
		display_action(philo->time->start, philo->name, "is eating\n");
		usleep(philo->time->to_eat);
		pthread_mutex_unlock(philo->fork_right);
		pthread_mutex_unlock(philo->fork_left);
		if (philo->laps_left > 0)
			philo->laps_left -= 1;
		if (!philo->laps_left)
			return (NULL);
		display_action(philo->time->start, philo->name, "is sleeping\n");
    	usleep(philo->time->to_sleep);
    }
    return (NULL);
}

int some_are_left(t_args args)
{
	int i;

	i = -1;
	while (++i < args.nb_philo)
	{
		if (args.philo[i].laps_left != 0)
			return (1);
	}
	return (0);
}

void monitor_death_clocks(t_args args)
{
	int i;
	
	usleep(10000);
	write(1, "monitor start\n", 14);
	while (some_are_left(args))
	{
		i = -1;
		while (++i < args.nb_philo)
		{
			if (check_death_clock(args.philo[i].death))
			{
				args.philo[i].laps_left = 0;
				display_action(args.philo[i].time->start, args.philo[i].name, "died\n");
				clean_and_exit(&args, 3, "\nBYE (inside)\n");
			}
		}
		usleep(10);
	}
	clean_and_exit(&args, 3, "\nBYE (outside)\n");
}

int main(int ac, char **av)
{
    t_args  args;
//	pthread_mutex_t **fork_tab;

    get_arguments(ac, av, &args);
//	write(1, "1", 1);
    start_mutexes(&args);
//	write(1, "2", 1);
	prepare_threads(&args);
//	write(1, "3", 1);
    start_threads(&args);
//	write(1, "4", 1);
	monitor_death_clocks(args);
//	join_threads(&args);
	return (0);
}