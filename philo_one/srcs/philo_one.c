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
		pthread_mutex_lock(philo->fork_right);
		display_action(philo->time->start, philo->name, "has taken a fork\n");
		pthread_mutex_lock(philo->fork_left);
		display_action(philo->time->start, philo->name, "has taken a fork\n");
    	update_death_clock(&philo->death, philo->time->to_die);
		display_action(philo->time->start, philo->name, "is eating\n");
		usleep(philo->time->to_eat);
		pthread_mutex_unlock(philo->fork_right);
		pthread_mutex_unlock(philo->fork_left);
		if (philo->laps_left > 0)
			philo->laps_left -= 1;
		if (!philo->laps_left)
		{
			pthread_detach(philo->thread);
			return (NULL);
		}
		display_action(philo->time->start, philo->name, "is sleeping\n");
    	usleep(philo->time->to_sleep);
		display_action(philo->time->start, philo->name, "is thinking\n");
    }
    return (NULL);
}

void *monitor_death_clocks(void *arg)
{
	int i;
	int quit;
	t_args *args;
	
//	write(1, "monitor start\n", 14);
    args = (t_args *)arg;
	quit = args->nb_philo;
	usleep(args->time.to_die);
	while (quit)
	{
		i = -1;
		while (++i < args->nb_philo)
		{
			if (check_death_clock(args->philo[i].death))
			{
				display_action(args->philo[i].time->start, args->philo[i].name, "died\n");
				return (NULL);
			}
			if (!args->philo[i].laps_left)
				quit--;
			if (!quit)
				return (NULL);
		}
		usleep(10);
	}
	return (NULL);
}

int main(int ac, char **av)
{
    t_args  args;

    get_arguments(ac, av, &args);
    start_mutexes(&args);
	prepare_threads(&args);
 //   start_threads(&args);
	pthread_create(&args.clock, NULL, &monitor_death_clocks, &args);
	pthread_join(args.clock, NULL);
//	clean_and_exit();	a reecrire proprement
//	monitor_death_clocks(args);
	return (0);
}