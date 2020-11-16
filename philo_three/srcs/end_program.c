/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   end_program.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: user42 <user42@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/09/01 19:50:07 by lemarabe          #+#    #+#             */
/*   Updated: 2020/11/16 17:58:28 by user42           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo_three.h"

void	wait_for_philo_thread(t_args *args)
{
	pthread_join(args->philo.control, NULL);
	pthread_join(args->philo.thread, NULL);
	sem_close(args->philo.state);
	free(args->philo.name);
	clean_and_exit(args, (args->nb_philo + 5), "");
}

void	close_semaphores(t_args *args, int to_close)
{
	sem_close(args->philo.forks);
	if (to_close > 2)
	{
		sem_close(args->philo.channel);
		if (to_close > 3)
		{
			sem_close(args->philo.quit);
			if (to_close > 4)
				sem_close(args->philo.full);
		}
	}
}

int		clean_and_exit(t_args *args, int to_free, char *str)
{
	if (to_free)
	{
		if (to_free > 1)
			close_semaphores(args, to_free);
		unlink_previous_semaphores(args);
		free(args->pids);
	}
	write(2, str, ft_strlen(str));
	write(2, "\n", 1);
	exit(0);
}
