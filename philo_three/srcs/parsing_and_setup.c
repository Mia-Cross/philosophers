/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing_and_setup.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: user42 <user42@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/09/08 20:16:50 by lemarabe          #+#    #+#             */
/*   Updated: 2020/11/16 18:00:05 by user42           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo_three.h"

char	*check_args(char **av, t_args *args)
{
	if (ft_atoi_ulong(av[1]) < 2)
		return ("You should have more than 1 philosopher !");
	args->nb_philo = ft_atoi_ulong(av[1]);
	if (ft_atoi_ulong(av[2]) <= 0)
		return ("Time to die must be a strictly positive number !");
	args->philo.time.to_die = 1000 * ft_atoi_ulong(av[2]);
	if (ft_atoi_ulong(av[3]) <= 0)
		return ("Time to eat must be a strictly positive number !");
	args->philo.time.to_eat = 1000 * ft_atoi_ulong(av[3]);
	if (ft_atoi_ulong(av[4]) <= 0)
		return ("Time to sleep must be a strictly positive number !");
	args->philo.time.to_sleep = 1000 * ft_atoi_ulong(av[4]);
	if (av[5])
	{
		if (ft_atoi_ulong(av[5]) <= 0)
			return ("Number of rounds must be a strictly positive number !");
		args->philo.laps_left = ft_atoi_ulong(av[5]);
	}
	else
		args->philo.laps_left = -1;
	return (NULL);
}

void	get_arguments(int ac, char **av, t_args *args)
{
	char	*err;

	if (!(ac == 5 || ac == 6))
		clean_and_exit(args, 0, "Wrong number of parameters !");
	memset(args, '\0', sizeof(t_args));
	if ((err = check_args(av, args)) && err)
		clean_and_exit(args, 0, err);
	if (!(args->pids = malloc(sizeof(pid_t) * (args->nb_philo + 2))))
		clean_and_exit(args, 0, "Malloc in pid_tab failed...");
	args->philo.alive = 1;
}

void	start_semaphores(t_args *args)
{
	args->philo.forks = open_new_semaphore("/forks", args->nb_philo);
	if (!args->philo.forks)
		clean_and_exit(args, 1, "Failed to open semaphore : forks");
	args->philo.channel = open_new_semaphore("/channel", 1);
	if (!args->philo.channel)
		clean_and_exit(args, 2, "Failed to open semaphore : channel");
	args->philo.quit = open_new_semaphore("/quit", 0);
	if (!args->philo.quit)
		clean_and_exit(args, 3, "Failed to open semaphore : quit signal");
	args->philo.full = open_new_semaphore("/full", 0);
	if (!args->philo.full)
		clean_and_exit(args, 4, "Failed to open semaphore : philo full count");
}

void	start_philo_process(t_args *args, pid_t *pid, int i, time_t wait)
{
	if (*pid)
		*pid = fork();
	if (*pid < 0)
		clean_and_exit(args, (args->nb_philo + 5), "Failed to fork processes");
	else if (*pid == 0)
	{
		args->philo.name = semaphore_name(ft_itoa(i + 1));
		args->philo.state = open_new_semaphore(args->philo.name, 1);
		if (!args->philo.state)
		{
			free(args->philo.name);
			clean_and_exit(args, (i + 5), "Failed to open semaphore : state");
		}
		pthread_create(&args->philo.control, NULL, &philo_control,
			&args->philo);
		pthread_create(&args->philo.thread, NULL, &philo_life,
			&args->philo);
		wait_for_philo_thread(args);
	}
	else
	{
		args->pids[i] = *pid;
		usleep(wait);
	}
}

void	start_all_processes(t_args *args)
{
	int		i;
	pid_t	pid;
	time_t	wait;

	i = -1;
	pid = 1;
	wait = 5000;
	while (wait > 1000 && wait * args->nb_philo >= args->philo.time.to_die)
		wait -= 1000;
	gettimeofday(&args->philo.time.start, NULL);
	while (++i < args->nb_philo)
		start_philo_process(args, &pid, i, wait);
	start_lap_monitoring(args, &pid, i);
	start_death_monitoring(args, &pid, i);
}
