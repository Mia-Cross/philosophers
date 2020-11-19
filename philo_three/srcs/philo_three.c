/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_three.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: user42 <user42@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/08/27 18:30:38 by lemarabe          #+#    #+#             */
/*   Updated: 2020/11/16 18:51:31 by user42           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo_three.h"

void	display_action(t_philo *philo, char *action)
{
	char	*time;

	if (!philo->alive)
		return ;
	time = ft_itoa(get_time_since_start(philo->time.start));
	sem_wait(philo->channel);
	write(1, time, ft_strlen(time));
	write(1, " ", 1);
	write(1, (philo->name + 1), (ft_strlen(philo->name) - 1));
	write(1, " ", 1);
	write(1, action, ft_strlen(action));
	if (ft_strlen(action) != 5)
		sem_post(philo->channel);
	free(time);
}

void	*philo_control(void *arg)
{
	t_philo	*philo;

	philo = (t_philo *)arg;
	update_death_clock(&philo->death, philo->time.to_die);
	usleep(philo->time.to_die - 10000);
	while (philo->alive)
	{
		sem_wait(philo->state);
		if (check_death_clock(philo->death))
		{
			sem_post(philo->state);
			usleep(2000);
		}
		else
		{
			display_action(philo, "died\n");
			philo->alive = 0;
			sem_post(philo->quit);
			sem_post(philo->state);
		}
	}
	return (NULL);
}

void	eat_if_allowed(t_philo *philo)
{
	sem_wait(philo->state);
	if (check_death_clock(philo->death))
		update_death_clock(&philo->death, philo->time.to_die);
	display_action(philo, "is eating\n");
	sem_post(philo->state);
}

void	*philo_life(void *arg)
{
	t_philo	*philo;

	philo = (t_philo *)arg;
	while (philo->alive)
	{
		sem_wait(philo->forks);
		display_action(philo, "has taken a fork\n");
		sem_wait(philo->forks);
		display_action(philo, "has taken a fork\n");
		eat_if_allowed(philo);
		if (philo->laps_left >= 0)
			philo->laps_left -= 1;
		if (!philo->laps_left)
			sem_post(philo->full);
		usleep(philo->time.to_eat);
		sem_post(philo->forks);
		sem_post(philo->forks);
		display_action(philo, "is sleeping\n");
		usleep(philo->time.to_sleep);
		display_action(philo, "is thinking\n");
	}
	return (NULL);
}

int		main(int ac, char **av)
{
	t_args	args;

	get_arguments(ac, av, &args);
	unlink_previous_semaphores(&args);
	start_semaphores(&args);
	start_all_processes(&args);
	clean_and_exit(&args, (args.nb_philo + 5), "");
	return (0);
}
