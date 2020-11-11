/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_semaphore.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: user42 <user42@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/08 19:59:23 by user42            #+#    #+#             */
/*   Updated: 2020/11/09 21:13:44 by user42           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo_two.h"

void	unlink_previous_semaphores(t_args *args)
{
	int	i;

	sem_unlink("/forks");
	sem_unlink("/channel");
	i = -1;
	while (++i < args->nb_philo)
		sem_unlink(args->philo[i].name);
}

char	*semaphore_name(char *number)
{
	char	*sem_name;
	int		i;

	if (!(sem_name = malloc(sizeof(char) * (ft_strlen(number) + 1) + 1)))
		return (NULL);
	sem_name[0] = '/';
	i = -1;
	while (number[++i] && i < 8)
		sem_name[i + 1] = number[i];
	sem_name[i + 1] = '\0';
	free(number);
	return (sem_name);
}

sem_t	*open_new_semaphore(char *name, int value)
{
	sem_t	*sem;

	if (!name)
		return (NULL);
	if (!(sem = sem_open(name, O_CREAT | O_EXCL, 0600, value)))
		return (NULL);
	return (sem);
}
