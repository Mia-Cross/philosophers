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
	if (!(args->fork_tab = malloc(sizeof(pthread_mutex_t) * args->nb_philo)))
		clean_and_exit(args, 0, "Malloc in forks_tab failed...");
    if (!(args->philo = malloc(sizeof(t_philo) * args->nb_philo)))
		clean_and_exit(args, 1, "Malloc in philo_tab failed...");
}

void display_action(t_timeval start, char *philo, char *action)
{
    char *time;
    char *msg;
    int i;
	int j;

    time = ft_itoa(get_time_since_start(start));
    if (!(msg = malloc(sizeof(char) * (ft_strlen(time) + ft_strlen(philo) + ft_strlen(action) + 8))))
        return;
    i = 0;
	j = 0;
    while (time[j] != '\0')
        msg[i++] = time[j++];
    msg[i++] = ' ';
    while (*philo != '\0')
        msg[i++] = *philo++;
    msg[i++] = ' ';
    while (*action != '\0')
        msg[i++] = *action++;
    msg[i++] = '\0';
    write(1, msg, ft_strlen(msg));
	free(time);
    free(msg);
}


void start_threads(t_args *args)
{
    int i;

    i = -1;
	gettimeofday(&args->time.start, NULL);
	while (++i < args->nb_philo)
		pthread_create(&args->philo[i].thread, NULL, &philo_routine, &args->philo[i]);
}

void join_threads(t_args *args)
{
    int i;

    i = -1;
	while (++i < args->nb_philo)
		pthread_join(args->philo[i].thread, NULL);
}