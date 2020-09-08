/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_one.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lemarabe <lemarabe@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/08/27 18:30:38 by lemarabe          #+#    #+#             */
/*   Updated: 2020/09/08 20:53:23 by lemarabe         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo_one.h"

void *philo_routine(void *arg)
{
    t_philo *philo;

    philo = (t_philo *)arg;
	update_death_clock(&philo->death, philo->time->to_die);
    while (philo->laps_left)
    {
	/*	if (!philosopher_thinks(philo))
            return (NULL);
        if (!philosopher_eats(philo))
            return (NULL); */
        philosopher_thinks(philo);
        philosopher_eats(philo);
		philosopher_sleeps(philo);
    }
    return (philo);
}


void start_mutexes(t_args *args)
{
    int i;

    i = 0;
    while (i < args->nb_philo)
        pthread_mutex_init(&args->fork_tab[i++], NULL);
}


void prepare_threads(t_args *args)
{
	int i;

    i = -1;
	while (++i < args->nb_philo - 1)
	{
		memset(&args->philo[i], 0, sizeof(t_philo));
        args->philo[i].num = i;
        args->philo[i].name = ft_itoa(i + 1);
        args->philo[i].time = &args->time;
        args->philo[i].laps_left = args->nb_laps;
        args->philo[i].fork_left = &args->fork_tab[i];
        args->philo[i].fork_right = &args->fork_tab[i + 1];
	}
	memset(&args->philo[i], 0, sizeof(t_philo));
    args->philo[i].num = i;
    args->philo[i].name = ft_itoa(i + 1);
    args->philo[i].time = &args->time;
    args->philo[i].laps_left = args->nb_laps;
    args->philo[i].fork_left = &args->fork_tab[i];
    args->philo[i].fork_right = &args->fork_tab[0];
}

void start_threads(t_args *args)
{
    int i;

    i = -1;
	gettimeofday(&args->time.start, NULL);
	while (++i < args->nb_philo)
		pthread_create(&args->thread_tab[i], NULL, &philo_routine, &args->philo[i]);
}

t_philo *join_threads(t_args *args)
{
    int i;
    void *ptr;

    i = -1;
    if (!(ptr = malloc(sizeof(t_philo))))
        return (NULL);                         //exit ?
	while (++i < args->nb_philo)
		pthread_join(&args->thread_tab[i], ptr);
    return ((t_philo *)ptr);
}

int main(int ac, char **av)
{
    t_args  args;

    get_arguments(ac, av, &args);
    start_mutexes(&args);
	prepare_threads(&args);
    start_threads(&args);
	monitor_death_clocks(args);
	return (0);
}