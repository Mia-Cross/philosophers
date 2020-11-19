/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing_and_setup.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: user42 <user42@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/09/08 20:16:50 by lemarabe          #+#    #+#             */
/*   Updated: 2020/11/15 21:25:38 by user42           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo_two.h"

char	*check_args(char **av, t_args *args)
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

void	get_arguments(int ac, char **av, t_args *args)
{
	char	*err;
	int		i;

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

void	start_semaphores(t_args *args)
{
	int	i;

	args->forks = open_new_semaphore("/forks", args->nb_philo);
	if (!args->forks)
		clean_and_exit(args, 1, "Failed to open semaphore : forks");
	args->channel = open_new_semaphore("/channel", 1);
	if (!args->channel)
		clean_and_exit(args, 2, "Failed to open semaphore : channel");
	i = -1;
	while (++i < args->nb_philo)
	{
		args->philo[i].state = open_new_semaphore(args->philo[i].name, 1);
		if (!args->philo[i].state)
			clean_and_exit(args, (i + 3), "Failed to open semaphore : state");
	}
}

void	set_philosophers(t_args *args)
{
	int	i;

	i = -1;
	while (++i < args->nb_philo)
	{
		args->philo[i].time = &args->time;
		args->philo[i].laps_left = args->nb_laps;
		args->philo[i].quit = &args->quit;
		args->philo[i].forks = args->forks;
		args->philo[i].channel = args->channel;
	}
}

void	start_threads(t_args *args)
{
	int		i;
	time_t	wait;

	i = -1;
	wait = 5000;
	while (wait > 1000 && wait * args->nb_philo >= args->time.to_die)
		wait -= 1000;
	gettimeofday(&args->time.start, NULL);
	while (++i < args->nb_philo)
	{
		pthread_create(&args->philo[i].thread, NULL, &philo_life,
			&args->philo[i]);
		pthread_create(&args->philo[i].control, NULL, &philo_control,
			&args->philo[i]);
		usleep(wait);
	}
}
