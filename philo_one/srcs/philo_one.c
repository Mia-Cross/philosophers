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

void *philo_life(void *arg)
{
    t_philo *philo;

    philo = (t_philo *)arg;
	update_death_clock(&philo->death, philo->time->to_die);
    while (philo->quit)
    {
		pthread_mutex_lock(philo->fork_right);
		display_action(philo->channel, philo->time->start, philo->name, "has taken a fork\n");
		if (!philo->quit)
			return (NULL);
		pthread_mutex_lock(philo->fork_left);
		display_action(philo->channel, philo->time->start, philo->name, "has taken a fork\n");
		if (!philo->quit)
			return (NULL);
    	update_death_clock(&philo->death, philo->time->to_die);
		display_action(philo->channel, philo->time->start, philo->name, "is eating\n");
		usleep(philo->time->to_eat);
		pthread_mutex_unlock(philo->fork_right);
		pthread_mutex_unlock(philo->fork_left);
		if (!philo->quit)
			return (NULL);
		if (philo->laps_left > 0)
			philo->laps_left -= 1;
		display_action(philo->channel, philo->time->start, philo->name, "is sleeping\n");
    	usleep(philo->time->to_sleep);
		display_action(philo->channel, philo->time->start, philo->name, "is thinking\n");
    }
    return (NULL);
}

void lock_alive_state(t_philo *philo, int nb_philo)
{
	int i;

	i = -1;
	while (++i < nb_philo)
		pthread_mutex_lock(&philo[i].state);
}

void *simulation_control(void *arg)
{
	t_args *args;
	int i;

	args = (t_args *)arg;
	lock_alive_state(args->philo, args->nb_laps);
	while (args->quit)
	{
		usleep(10);
		i = -1;
		while (++i < args->nb_philo)
		{
			if (!args->philo[i].laps_left)
			{
				if (args->quit > 0)
					args->quit -= 1;
				args->philo[i].laps_left = -1;
			}
			if (check_death_clock(args->philo[i].death))
			{
				pthread_mutex_unlock(&args->philo[i].state);
				display_action(args->philo[i].channel, args->philo[i].time->start, args->philo[i].name, "died\n");
				args->quit = 0;
			}
		}
	}
	return (NULL);
}

void *death_reaper(void *arg)
{
	t_philo *philo;

	philo = (t_philo *)arg;
	usleep(philo->time->to_die - 100);
	pthread_mutex_lock(&philo->state);
//	write(1, "reaper said you're done\n", 24);
//	pthread_join(philo->thread, NULL);
//	write(1, "philo thread stopped\n", 21);
	return (philo);
}

void end_simulation(t_args *args)
{
	int i;

	i = -1;
	while (++i < args->nb_philo)
	{
	//	args->philo[i].alive = 0;
		pthread_join(args->philo[i].thread, NULL);
	}
	destroy_mutexes(args);
}

int main(int ac, char **av)
{
    t_args  args;
	int i;

    get_arguments(ac, av, &args);
    start_mutexes(&args);
    start_philo_threads(&args);
	pthread_create(&args.clock, NULL, &simulation_control, &args);
//	pthread_create(&args.lap_counter, NULL, &monitor_laps, &args);
	i = -1;
	while (++i < args.nb_philo)
	{
		pthread_join(args.state_thread[i], NULL);
//		write(1, "state thread joined\n", 20);
	}
//	write(1, "shit\n", 5);
//	pthread_join(args.lap_counter, NULL);
//	end_simulation(&args);
	clean_and_exit(&args, 3, "");
	return (0);
}