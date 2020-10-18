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
		display_action(philo->channel, philo->time->start, philo->name, "has taken a fork\n");
		if (!philo->laps_left)
		{
			pthread_mutex_unlock(&philo->state);
			return (NULL);
		}
		pthread_mutex_lock(philo->fork_left);
		display_action(philo->channel, philo->time->start, philo->name, "has taken a fork\n");
		if (!philo->laps_left)
		{
			pthread_mutex_unlock(&philo->state);
			return (NULL);
		}
    	update_death_clock(&philo->death, philo->time->to_die);
		display_action(philo->channel, philo->time->start, philo->name, "is eating\n");
		usleep(philo->time->to_eat);
		pthread_mutex_unlock(philo->fork_right);
		pthread_mutex_unlock(philo->fork_left);
		if (philo->laps_left > 0)
			philo->laps_left -= 1;
		if (!philo->laps_left)
		{
			pthread_mutex_unlock(&philo->state);
			return (NULL);
		}
		display_action(philo->channel, philo->time->start, philo->name, "is sleeping\n");
    	usleep(philo->time->to_sleep);
		display_action(philo->channel, philo->time->start, philo->name, "is thinking\n");
    }
	pthread_mutex_unlock(&philo->state);
    return (NULL);
}

void *monitor_clocks_and_laps(void *arg)
{
	int i;
	int quit;
	t_args *args;
	
    args = (t_args *)arg;
	quit = args->nb_philo;
	usleep(args->time.to_die - 10);
	while (quit)
	{
		usleep(10);
		i = -1;
		while (++i < args->nb_philo)
		{
			if (check_death_clock(args->philo[i].death))
			{
				args->philo[i].laps_left = 0;
				pthread_mutex_unlock(&args->philo[i].state);
				display_action(&args->channel, args->philo[i].time->start, args->philo[i].name, "died\n");
				return (NULL);
			}
			if (!args->philo[i].laps_left)
			{
				pthread_mutex_unlock(&args->philo[i].state);
//				pthread_join(args->philo[i].thread, NULL);
				quit--;
			}
		}
	}
	return (NULL);
}

void *death_reaper(void *arg)
{
	t_philo *philo;

	philo = (t_philo *)arg;
	pthread_mutex_lock(&philo->state);
	pthread_join(philo->thread, NULL);
	return (philo);
}

int main(int ac, char **av)
{
    t_args  args;
	int i;

    get_arguments(ac, av, &args);
    start_mutexes(&args);
//	prepare_threads(&args);
    start_threads(&args);
	pthread_create(&args.clock, NULL, &monitor_clocks_and_laps, &args);
	i = -1;
	while (++i < args.nb_philo)
		pthread_create(&args.states[i], NULL, &death_reaper, &args.philo[i]);
	i = -1;
	while (++i < args.nb_philo)
		pthread_join(args.states[i], NULL);
	pthread_join(args.clock, NULL);
	clean_and_exit(&args, 3, "");
	return (0);
}