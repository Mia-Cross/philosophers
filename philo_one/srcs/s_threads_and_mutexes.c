/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   actions.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lemarabe <lemarabe@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/09/01 19:50:07 by lemarabe          #+#    #+#             */
/*   Updated: 2020/09/08 20:39:26 by lemarabe         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo_one.h"

void start_mutexes(t_args *args)
{
    int i;

	pthread_mutex_init(&args->channel, NULL);
	pthread_mutex_init(&args->forks[args->nb_philo - 1], NULL);
    i = -1;
    while (++i < args->nb_philo - 1)
	{
		pthread_mutex_init(&args->forks[i], NULL);
        pthread_mutex_init(&args->philo[i].state, NULL);
	}
}

void destroy_mutexes(t_args *args)
{
    int i;

    i = 0;
	while (i < args->nb_philo)
	{
		pthread_mutex_unlock(&args->philo[i].state);
		pthread_mutex_unlock(&args->forks[i]);
		pthread_mutex_destroy(&args->philo[i].state);
		pthread_mutex_destroy(&args->forks[i++]);
	}
	pthread_mutex_unlock(&args->channel);
	pthread_mutex_destroy(&args->channel);
}

void start_philo_threads(t_args *args)
{
	int i;

    i = -1;
	gettimeofday(&args->time.start, NULL);
	while (++i < args->nb_philo)
	{
		memset(&args->philo[i], 0, sizeof(t_philo));
        args->philo[i].name = ft_itoa(i + 1);
        args->philo[i].time = &args->time;
        args->philo[i].laps_left = args->nb_laps;
	//	args->philo[i].alive = 1;
		args->philo[i].quit = &args->quit;
		args->philo[i].channel = &args->channel;
        args->philo[i].fork_left = &args->forks[i];
		if (i > 0)
        	args->philo[i].fork_right = &args->forks[i - 1];
		else
    		args->philo[i].fork_right = &args->forks[args->nb_philo - 1];
		usleep(200);
		pthread_create(&args->philo[i].thread, NULL, &philo_life, &args->philo[i]);
	//	pthread_mutex_lock(&args->philo[i].state);
		pthread_create(&args->state_thread[i], NULL, &death_reaper, &args->philo[i]);
	}
}

int clean_and_exit(t_args *args, int to_free, char *str)
{
	int i;
	
    if (to_free)
    {
        if (to_free > 1)
        {
			if (to_free > 2)
			{
				i = -1;
				while (++i < args->nb_philo)
					free(args->philo[i].name);
            	free(args->philo);
			}
			free(args->state_thread);
        }
        free(args->forks);
    }
    write(2, str, ft_strlen(str));
    write(2, "\n", 1);
    exit(0);
}