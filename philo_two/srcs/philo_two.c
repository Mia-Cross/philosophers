/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_two.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lemarabe <lemarabe@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/08/27 18:30:38 by lemarabe          #+#    #+#             */
/*   Updated: 2020/09/08 20:53:23 by lemarabe         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo_two.h"

void *philo_routine(void *arg)
{
    t_philo *philo;

    philo = (t_philo *)arg;
	update_death_clock(&philo->death, philo->time->to_die);
    while (philo->laps_left)
    {
		display_action(philo->time->start, philo->name, "is thinking\n");
		sem_wait(philo->sem);
		display_action(philo->time->start, philo->name, "has taken a fork\n");
		sem_wait(philo->sem);
		display_action(philo->time->start, philo->name, "has taken a fork\n");
    	update_death_clock(&philo->death, philo->time->to_die);
		display_action(philo->time->start, philo->name, "is eating\n");
		usleep(philo->time->to_eat);
		sem_post(philo->sem);
		sem_post(philo->sem);
		if (philo->laps_left > 0)
			philo->laps_left -= 1;
		display_action(philo->time->start, philo->name, "is sleeping\n");
    	usleep(philo->time->to_sleep);
    }
    return (NULL);
}

void start_semaphore(t_args *args)
{
	args->sem = sem_open("forks", O_CREAT, S_IRWXU, args->nb_philo);
}

void prepare_threads(t_args *args)
{
	int i;

    i = -1;
	while (++i < args->nb_philo)
	{
		memset(&args->philo[i], 0, sizeof(t_philo));
        args->philo[i].num = i;
        args->philo[i].name = ft_itoa(i + 1);
        args->philo[i].time = &args->time;
        args->philo[i].laps_left = args->nb_laps;
		args->philo[i].sem = args->sem;
	}
}

void monitor_death_clocks(t_args args)
{
	gettimeofday(args.time->start);
}

int main(int ac, char **av)
{
    t_args  args;

    get_arguments(ac, av, &args);
    start_semaphore(&args);
	prepare_threads(&args);
    start_threads(&args);
	monitor_death_clocks(args);
	return (0);
}