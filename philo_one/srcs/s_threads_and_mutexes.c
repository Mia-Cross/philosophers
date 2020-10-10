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

    i = 0;
    while (i < args->nb_philo)
        pthread_mutex_init(&args->fork_tab[i++], NULL);
}

void destroy_mutexes(t_args *args)
{
    int i;

    i = 0;
    while (i < args->nb_philo)
        pthread_mutex_destroy(&args->fork_tab[i++]);
}

void prepare_threads(t_args *args)
{
	int i;

    i = -1;
	while (++i < args->nb_philo)
	{
		memset(&args->philo[i], 0, sizeof(t_philo));
        args->philo[i].num = i;
        args->philo[i].name = ft_itoa(i + 1);
        args->philo[i].time = &args->time;
        args->philo[i].laps_left = args->nb_laps;
        args->philo[i].fork_left = &args->fork_tab[i];
		if (i > 0)
        	args->philo[i].fork_right = &args->fork_tab[i - 1];
		else
    		args->philo[i].fork_right = &args->fork_tab[args->nb_philo - 1];
	}
}

int clean_and_exit(t_args *args, int to_free, char *str)
{
	int i;
	
    if (to_free)
    {
        free(args->fork_tab);
        if (to_free > 1)
        {
			destroy_mutexes(args);
			i = -1;
			while (++i < args->nb_philo)
				free(args->philo[i].name);
            free(args->philo);
        }
    }
//	system("leaks philo_one");
    write(2, str, ft_strlen(str));
    write(2, "\n", 1);
    exit(0);
}