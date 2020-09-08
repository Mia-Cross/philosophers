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

void stop_thread(t_args *args, int i)
{
    display_action(args->philo[i].time->start, args->philo[i].name, "died\n");
//	pthread_detach(args->thread_tab[i]);
//	pthread_join(args->thread_tab[i], NULL);
}

int clean_and_exit(t_args *args, int to_free, char *str)
{
	int i;
	
    if (to_free)
    {
        if (to_free > 1)
        {
            free(args->fork_tab);
            if (to_free > 2)
			{
				i = -1;
//				usleep(90000);
				while (++i < args->nb_philo)
				{
//					pthread_join(args->thread_tab[i], NULL);
					free(args->philo[i].name);
				}
                free(args->philo);
			}
        }
        free(args->thread_tab);
    }
	system("leaks philo_one");
    write(2, str, ft_strlen(str));
    write(2, "\n", 1);
    exit(0);
}

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
	if (!(args->thread_tab = malloc(sizeof(pthread_t) * args->nb_philo)))
		clean_and_exit(args, 0, "Malloc in thread_tab failed...");
	if (!(args->fork_tab = malloc(sizeof(pthread_mutex_t) * args->nb_philo)))
		clean_and_exit(args, 1, "Malloc in forks_tab failed...");
    if (!(args->philo = malloc(sizeof(t_philo) * args->nb_philo)))
		clean_and_exit(args, 2, "Malloc in philo_tab failed...");
}