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
		pthread_mutex_lock(philo->fork_left);
		display_action(philo->channel, philo->time->start, philo->name, "has taken a fork\n");
		pthread_mutex_lock(&philo->state);
		pthread_mutex_unlock(&philo->state);
    	update_death_clock(&philo->death, philo->time->to_die);
		display_action(philo->channel, philo->time->start, philo->name, "is eating\n");
		usleep(philo->time->to_eat);
		pthread_mutex_unlock(philo->fork_right);
		pthread_mutex_unlock(philo->fork_left);
		if (philo->laps_left > 0)
			philo->laps_left -= 1;
		display_action(philo->channel, philo->time->start, philo->name, "is sleeping\n");
    	usleep(philo->time->to_sleep);
		display_action(philo->channel, philo->time->start, philo->name, "is thinking\n");
    }
    return (NULL);
}

void disable_display(t_philo *philo, int nb_philo)
{
	int i;

	i = -1;
	while (++i < nb_philo)
		philo[i].channel = NULL;
}

void detach_philo_threads(t_philo *philo, int nb_philo)
{
	int i;

	i = -1;
	while (++i < nb_philo)
		pthread_detach(philo[i].thread);
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
				pthread_mutex_lock(&args->philo[i].state);
				display_action(args->philo[i].channel, args->philo[i].time->start, args->philo[i].name, "died\n");
				disable_display(args->philo, args->nb_philo);
				args->quit = 0;
			}
		}
	}
	write(1, "yo tout le monde c'est squeezie", 31);
	disable_display(args->philo, args->nb_philo);
//	pthread_mutex_unlock(&args->channel);
//	pthread_mutex_destroy(&args->channel);
//	memset(&args->channel, 0, sizeof(pthread_mutex_t));
	return (NULL);
}


int main(int ac, char **av)
{
    t_args  args;

    get_arguments(ac, av, &args);
    start_mutexes(&args);
    start_philo_threads(&args);
	pthread_create(&args.control, NULL, &simulation_control, &args);
	pthread_join(args.control, NULL);
	detach_philo_threads(args.philo, args.nb_philo);
	destroy_mutexes(&args);
	clean_and_exit(&args, 3, "");
	return (0);
}