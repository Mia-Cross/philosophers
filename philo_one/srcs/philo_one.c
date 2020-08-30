/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_one.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lemarabe <lemarabe@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/08/27 18:30:38 by lemarabe          #+#    #+#             */
/*   Updated: 2020/08/30 20:45:10 by lemarabe         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo_one.h"

void *philo_routine(void *arg)
{
    t_args *args;

    args = (t_args *)arg;
    gettimeofday(&args->time.start, NULL);
    while (1)
    {
		update_death_clock(&args->time, args->philo_num);
        if (!philosopher_eats(args))
			return (NULL);
		if (!philosopher_sleeps(args))
			return (NULL);
		philosopher_thinks(args);
    }
    return (NULL);
}

char *check_args(int ac, char **av, t_args *args)
{
    if (!(ac == 5 || ac == 6))
        return ("Wrong number of parameters !");
    if (ft_atoi_ulong(av[1]) < 2)
        return ("You should have more than 1 philosopher !");
    args->nb_philo = ft_atoi_ulong(av[1]);
    if (ft_atoi_ulong(av[2]) <= 0)
        return ("Time to die must be a strictly positive number !");
    args->time.to_die = ft_atoi_ulong(av[2]);
    if (ft_atoi_ulong(av[3]) <= 0)
        return ("Time to eat must be a strictly positive number !");
    args->time.to_eat = ft_atoi_ulong(av[3]);
    if (ft_atoi_ulong(av[4]) <= 0)
        return ("Time to sleep must be a strictly positive number !");
    args->time.to_sleep = ft_atoi_ulong(av[4]);
    if (av[5])
    {
        if (ft_atoi_ulong(av[5]) <= 0)
            return ("Number of rounds must be a strictly positive number !");
        args->nb_laps = ft_atoi_ulong(av[5]);
    }
    return (NULL);
}

int main(int ac, char **av)
{
    pthread_t   *thread_tab;
    t_args      args;
    char        *err;
    int         i;

	if ((err = check_args(ac, av, &args)) && err)
		return (parse_error(err));
	if (!(thread_tab = malloc(sizeof(pthread_t) * args.nb_philo)))
		return (parse_error("Malloc in thread_tab failed..."));
	if (!(args.fork = malloc(sizeof(pthread_mutex_t) * args.nb_philo)))
	{
		free(thread_tab);
		return (parse_error("Malloc in forks mutex failed..."));
	}
	if (!(args.time.death = malloc(sizeof(t_timeval) * args.nb_philo)))
	{
		free(thread_tab);
		free(args.fork);
		return (parse_error("Malloc in forks mutex failed..."));
	}
	i = 0;
	while (i < args.nb_philo)
		pthread_mutex_init(&args.fork[i++], NULL);
	i = 0;
	while (i < args.nb_philo)
	{
		args.philo_num = i;
		pthread_create(&thread_tab[i], NULL, &philo_routine, &args);
		i++;
	}
	i = 0;
	while (i < args.nb_philo)
		pthread_join(thread_tab[i++], NULL);
	free(thread_tab);
	free(args.fork);
	free(args.time.death);
	return (0);
}