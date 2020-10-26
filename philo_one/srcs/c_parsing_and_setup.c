/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing_and_exit.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lemarabe <lemarabe@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/09/08 20:16:50 by lemarabe          #+#    #+#             */
/*   Updated: 2020/09/08 20:48:44 by lemarabe         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo_one.h"

char *check_args(char **av, t_args *args)
{
    if (ft_atoi_ulong(av[1]) < 2)
        return ("You should have more than 1 philosopher !");
    args->nb_philo = ft_atoi_ulong(av[1]);
    if (ft_atoi_ulong(av[2]) <= 0)
        return ("Time to die must be a strictly positive number !");
    args->time.to_die = 1000 * ft_atoi_ulong(av[2]);
    if (ft_atoi_ulong(av[3]) <= 0)
        return ("Time to eat must be a strictly positive number !");
    args->time.to_eat = 1000 * ft_atoi_ulong(av[3]);
    if (ft_atoi_ulong(av[4]) <= 0)
        return ("Time to sleep must be a strictly positive number !");
    args->time.to_sleep = 1000 * ft_atoi_ulong(av[4]);
    if (av[5])
    {
        if (ft_atoi_ulong(av[5]) <= 0)
            return ("Number of rounds must be a strictly positive number !");
        args->nb_laps = ft_atoi_ulong(av[5]);
    }
	else
		args->nb_laps = -1;
	args->quit = args->nb_philo;
    return (NULL);
}

void get_arguments(int ac, char **av, t_args *args)
{
    char    *err;
    
    if (!(ac == 5 || ac == 6))
        clean_and_exit(args, 0, "Wrong number of parameters !");
    memset(args, 0, sizeof(t_args));
	if ((err = check_args(av, args)) && err)
		clean_and_exit(args, 0, err);
	if (!(args->forks = malloc(sizeof(pthread_mutex_t) * args->nb_philo)))
		clean_and_exit(args, 0, "Malloc in forks_tab failed...");
    if (!(args->philo = malloc(sizeof(t_philo) * args->nb_philo)))
		clean_and_exit(args, 1, "Malloc in philo_tab failed...");
}

void display_action(pthread_mutex_t *channel, t_timeval start, char *philo, char *action)
{
    char *time;

    if (channel == NULL)
        return ;
    time = ft_itoa(get_time_since_start(start));
	pthread_mutex_lock(channel);
	write(1, time, ft_strlen(time));
	write(1, " ", 1);
	write(1, philo, ft_strlen(philo));
	write(1, " ", 1);
    write(1, action, ft_strlen(action));
    pthread_mutex_unlock(channel);
    free(time);
}