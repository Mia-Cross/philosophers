/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_one.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: user42 <user42@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/08/27 18:30:38 by lemarabe          #+#    #+#             */
/*   Updated: 2020/11/07 02:42:29 by user42           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo_one.h"

void	display_action(t_philo *philo, char *action)
{
	char	*time;

	if (*philo->quit == 0)
		return ;
	time = ft_itoa(get_time_since_start(philo->time->start));
	pthread_mutex_lock(philo->channel);
	write(1, time, ft_strlen(time));
	write(1, " ", 1);
	write(1, philo->name, ft_strlen(philo->name));
	write(1, " ", 1);
	write(1, action, ft_strlen(action));
	pthread_mutex_unlock(philo->channel);
	free(time);
}

void	*simulation_control(void *arg)
{
	t_philo	*philo;

	philo = (t_philo *)arg;
	update_death_clock(&philo->death, philo->time->to_die);
	while (*philo->quit)
	{
		pthread_mutex_lock(&philo->state);
		if (check_death_clock(philo->death))
		{
			pthread_mutex_unlock(&philo->state);
			usleep(2000);
		}
		else
		{
			display_action(philo, "died\n");
			*philo->quit = 0;
			pthread_mutex_unlock(&philo->state);
		}
	}
	return (NULL);
}

void	eat_if_allowed(t_philo *philo)
{
	pthread_mutex_lock(&philo->state);
	display_action(philo, "is eating\n");
	if (check_death_clock(philo->death))
		update_death_clock(&philo->death, philo->time->to_die);
	pthread_mutex_unlock(&philo->state);
}

void	*philo_life(void *arg)
{
	t_philo	*philo;

	philo = (t_philo *)arg;
	while (*philo->quit)
	{
		pthread_mutex_lock(philo->fork_right);
		display_action(philo, "has taken a fork\n");
		pthread_mutex_lock(philo->fork_left);
		display_action(philo, "has taken a fork\n");
		eat_if_allowed(philo);
		if (philo->laps_left >= 0)
			philo->laps_left -= 1;
		if (!philo->laps_left && *philo->quit > 0)
			*philo->quit -= 1;
		usleep(philo->time->to_eat);
		pthread_mutex_unlock(philo->fork_right);
		pthread_mutex_unlock(philo->fork_left);
		display_action(philo, "is sleeping\n");
		usleep(philo->time->to_sleep);
		display_action(philo, "is thinking\n");
	}
	return (NULL);
}

int		main(int ac, char **av)
{
	t_args	args;

	get_arguments(ac, av, &args);
	start_mutexes(&args);
	set_philosophers(&args);
	start_threads(&args);
	wait_for_all_threads(&args);
	destroy_mutexes(&args);
	clean_and_exit(&args, 3, "");
	return (0);
}
