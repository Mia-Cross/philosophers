/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   c_parsing_and_setup.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: user42 <user42@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/09/08 20:16:50 by lemarabe          #+#    #+#             */
/*   Updated: 2020/11/08 19:15:58 by user42           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo_two.h"

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
    int i;
    
    if (!(ac == 5 || ac == 6))
        clean_and_exit(args, 0, "Wrong number of parameters !");
    memset(args, '\0', sizeof(t_args));
	if ((err = check_args(av, args)) && err)
		clean_and_exit(args, 0, err);
    if (!(args->philo = malloc(sizeof(t_philo) * args->nb_philo)))
		clean_and_exit(args, 0, "Malloc in philo_tab failed...");
    i = -1;
    while (++i < args->nb_philo)
    {
        memset(&args->philo[i], '\0', sizeof(t_philo));
        args->philo[i].name = semaphore_name(ft_itoa(i + 1));
    }
}

void display_action(t_philo *philo, char *action)
{
    char *time;

    if (!philo->quit)
        return ;
    time = ft_itoa(get_time_since_start(philo->time->start));
	sem_wait(philo->channel);
	write(1, time, ft_strlen(time));
	write(1, " ", 1);
	write(1, (philo->name + 1), (ft_strlen(philo->name) - 1));
	write(1, " ", 1);
    write(1, action, ft_strlen(action));
    sem_post(philo->channel);
    free(time);
}