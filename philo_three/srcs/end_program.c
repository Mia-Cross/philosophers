/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   end_program.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: user42 <user42@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/09/01 19:50:07 by lemarabe          #+#    #+#             */
/*   Updated: 2020/11/08 20:18:55 by user42           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo_two.h"

void	wait_for_all_threads(t_args *args)
{
	int	i;

	i = -1;
	while (++i < args->nb_philo)
		pthread_join(args->philo[i].control, NULL);
	i = -1;
	while (++i < args->nb_philo)
		pthread_join(args->philo[i].thread, NULL);
}

void	destroy_semaphores(t_args *args, int nb_philo)
{
	int	i;

	sem_unlink("/forks");
	sem_close(args->forks);
	if (nb_philo)
	{
		sem_unlink("/channel");
		sem_close(args->channel);
		if (nb_philo > 1)
		{
			i = -1;
			while (++i < nb_philo)
			{
				sem_unlink(args->philo[i].name);
				sem_close(args->philo[i].state);
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
		if (to_free > 2)
			destroy_semaphores(args, (to_free - 3));
		free(args->philo);
	}
	write(2, str, ft_strlen(str));
	write(2, "\n", 1);
	exit(0);
}
