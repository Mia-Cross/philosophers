/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing_and_setup.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: user42 <user42@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/09/08 20:16:50 by lemarabe          #+#    #+#             */
/*   Updated: 2020/11/11 04:17:27 by user42           ###   ########.fr       */
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
	//if (!(args->philo = malloc(sizeof(t_philo))))
	//	clean_and_exit(args, 0, "Malloc in philo_tab failed...");
	if (!(args->pids = malloc(sizeof(pid_t) * (args->nb_philo + 2))))
		clean_and_exit(args, 0, "Malloc in pid_tab failed...");
	//memset(&args->philo, '\0', sizeof(t_philo));
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
		clean_and_exit(args, 4, "Failed to open semaphore : counter for philos left");
}

void	start_threads(t_args *args)
{
	int	i;
//	int status;
//	pid_t exited;
	pid_t pid;

	i = -1;
	pid = 1;
	gettimeofday(&args->philo.time.start, NULL);
	while (++i < args->nb_philo)
	{
		if (pid)
			pid = fork();
		if (pid < 0)
			clean_and_exit(args, (args->nb_philo + 6), "Failed to fork processes");
		else if (pid == 0)
		{
			args->philo.name = semaphore_name(ft_itoa(i + 1));
			args->philo.state = open_new_semaphore(args->philo.name, 1);
			if (!args->philo.state)
				clean_and_exit(args, (i + 5), "Failed to open semaphore : state");
			//write(1, "-", 1);
			//printf("-pid = %u\n", getpid());
			pthread_create(&args->philo.control, NULL, &philo_control,
				&args->philo);
			////write(1, "%", 1);
			pthread_create(&args->philo.thread, NULL, &philo_life,
				&args->philo);
			////write(1, "%", 1);
			pthread_join(args->philo.control, NULL);
			//write(1, "[-]", 3);
			pthread_join(args->philo.thread, NULL);
			sem_close(args->philo.forks);
			sem_close(args->philo.channel);
			sem_close(args->philo.quit);
			sem_close(args->philo.full);
			sem_close(args->philo.state);
			free(args->philo.name);
			free(args->pids);
			exit(0);
		}
		else
		{
			args->pids[i] = pid;
			usleep(args->philo.time.to_die / args->nb_philo);
		}
	}
	
	if (pid)
		pid = fork();
	if (pid < 0)
		clean_and_exit(args, (args->nb_philo + 6), "Failed to fork processes");
	else if (pid == 0)
	{
		//write(1, "!", 1);
		//printf("!{pid = %u\n", getpid());
		pthread_create(&args->lap_monitor, NULL, &wait_end_signal, args);
		pthread_join(args->lap_monitor, NULL);
		//write(1, "!", 1);
		exit(0);
	}
	else
	{
		args->pids[i++] = pid;
		pid = fork();
	}

	if (pid < 0)
		clean_and_exit(args, (args->nb_philo + 6), "Failed to fork processes");
	else if (pid == 0)
	{
		//write(1, "?", 1);
		//printf("?(pid = %u\n", getpid());
		pthread_create(&args->death_monitor, NULL, &wait_death_signal, args);
		pthread_join(args->death_monitor, NULL);
		//write(1, "?", 1);
	}
	else
	{
		//write(1, "#", 1);
		args->pids[i] = pid;
		//printf("#pid = %u\n", getpid());
		//exited = waitpid(-1, &status, 0);
		waitpid(-1, NULL, 0);
		//write(1, "=", 1);
		//printf("expid = %u\n", exited);
		while (i >= 0)
			kill(args->pids[i--], SIGKILL);
	}
}
