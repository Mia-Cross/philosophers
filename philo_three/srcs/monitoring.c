/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   monitoring.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: user42 <user42@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/16 17:33:03 by user42            #+#    #+#             */
/*   Updated: 2020/11/16 17:59:39 by user42           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo_three.h"

void	*wait_end_signal(void *arg)
{
	int		i;
	t_args	*args;

	i = 0;
	args = (t_args *)arg;
	while (i < args->nb_philo)
	{
		sem_wait(args->philo.full);
		i++;
	}
	return (NULL);
}

void	*wait_death_signal(void *arg)
{
	t_args	*args;

	args = (t_args *)arg;
	sem_wait(args->philo.quit);
	return (NULL);
}

void	start_lap_monitoring(t_args *args, pid_t *pid, int i)
{
	if (*pid)
		*pid = fork();
	if (*pid < 0)
		clean_and_exit(args, (args->nb_philo + 6), "Failed to fork processes");
	else if (*pid == 0)
	{
		pthread_create(&args->lap_monitor, NULL, &wait_end_signal, args);
		pthread_join(args->lap_monitor, NULL);
		clean_and_exit(args, (args->nb_philo + 5), "");
	}
	else
	{
		args->pids[i++] = *pid;
		*pid = fork();
	}
}

void	start_death_monitoring(t_args *args, pid_t *pid, int i)
{
	if (*pid < 0)
		clean_and_exit(args, (args->nb_philo + 6), "Failed to fork processes");
	else if (*pid == 0)
	{
		pthread_create(&args->death_monitor, NULL, &wait_death_signal, args);
		pthread_join(args->death_monitor, NULL);
		clean_and_exit(args, (args->nb_philo + 5), "");
	}
	else
	{
		args->pids[i] = *pid;
		waitpid(-1, NULL, 0);
		while (i >= 0)
			kill(args->pids[i--], SIGKILL);
	}
}
