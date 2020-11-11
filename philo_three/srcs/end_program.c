/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   end_program.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: user42 <user42@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/09/01 19:50:07 by lemarabe          #+#    #+#             */
/*   Updated: 2020/11/11 00:26:03 by user42           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo_three.h"

void	wait_for_all_threads(t_args *args)
{
	int status;

	if (args->philo.pid > 0)
	{
		write(1, "#", 1);
		waitpid(-1, &status, 0);
		write(1, "=", 1);
	}
	else
	{
		write(1, "%", 1);
		pthread_join(args->philo.control, NULL);
		pthread_join(args->philo.thread, NULL);
		sem_close(args->philo.forks);
		sem_close(args->philo.channel);
		sem_close(args->philo.quit);
		sem_close(args->philo.full);
		sem_close(args->philo.state);
		free(args->philo.name);
		//free(args->philo);
		exit(0);
	}
	//kill(0, 0);
}

void	destroy_semaphores(t_args *args, int nb_philo)
{
	int	i;
	char *name;
	(void)args;

	sem_unlink("/forks");
//	sem_close(args->forks);
	if (nb_philo)
	{
		sem_unlink("/channel");
	//	sem_close(args->channel);
		if (nb_philo > 1)
		{
			sem_unlink("/quit");
		//	sem_close(args->forks);
			if (nb_philo > 2)
			{
				sem_unlink("/full");
		//		sem_close(args->channel);
				i = -1;
				while (++i < nb_philo)
				{
					name = semaphore_name(ft_itoa(i + 1));
					sem_unlink(name);
					free(name);
			//		sem_close(args->philo[i].state);
				}
			}
		}
	}
}

int		clean_and_exit(t_args *args, int to_free, char *str)
{
	if (to_free)
	{
		if (to_free == 1)
			destroy_semaphores(args, 0);
		else if (to_free == 2)
			destroy_semaphores(args, 1);
		else if (to_free == 3)
			destroy_semaphores(args, 2);
		else if (to_free == 4)
			destroy_semaphores(args, 3);
		if (to_free > 4)
			destroy_semaphores(args, (to_free - 5));
	}
	write(2, str, ft_strlen(str));
	write(2, "\n", 1);
	exit(0);
}
