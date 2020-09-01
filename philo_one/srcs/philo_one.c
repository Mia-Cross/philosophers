/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_one.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lemarabe <lemarabe@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/08/27 18:30:38 by lemarabe          #+#    #+#             */
/*   Updated: 2020/09/01 19:47:44 by lemarabe         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo_one.h"

void *philo_routine(void *arg)
{
    t_philo *philo;

    philo = (t_philo *)arg;
	update_death_clock(&philo->death, philo->time->to_die);
    //print_timeval(philo->death, philo->name);
//    ft_putunsigned_long(philo->laps_left);
    while (philo->laps_left)
 //   while (1)
    {
		if (!philosopher_thinks(philo))
            return (NULL);
        if (!philosopher_eats(philo) || !philo->laps_left)
            return (NULL);
		if (!philosopher_sleeps(philo))
            return (NULL);
    }
    return (NULL);
}

char *check_args(char **av, t_args *args)
{
    if (ft_atoi_ulong(av[1]) < 2)
        return ("You should have more than 1 philosopher !");
    args->nb_philo = ft_atoi_ulong(av[1]);
    if (ft_atoi_ulong(av[2]) <= 0)
        return ("Time to die must be a strictly positive number !");
    args->time.to_die = 1000 * ft_atoi_ulong(av[2]);
    if (ft_atoi_ulong(av[3]) <= 0)
        return ("Time to eat must be a strictly positive number !");
    args->time.to_eat = 1000 * ft_atoi_ulong(av[3]);
    if (ft_atoi_ulong(av[4]) <= 0)
        return ("Time to sleep must be a strictly positive number !");
    args->time.to_sleep = 1000 * ft_atoi_ulong(av[4]);
    if (av[5])
    {
        if (ft_atoi_ulong(av[5]) <= 0)
            return ("Number of rounds must be a strictly positive number !");
        args->nb_laps = ft_atoi_ulong(av[5]);
    }
    else
        args->nb_laps = -1;
 //   printf("%ld %ld %ld %d\n", args->time.to_die, args->time.to_eat, args->time.to_sleep, args->time.nb_laps);
    return (NULL);
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
        args->philo[i].name = ft_itoa(i + 1);
        args->philo[i].time = &args->time;
        args->philo[i].laps_left = args->nb_laps;
        args->philo[i].fork_left = &args->fork_tab[i];
        args->philo[i].fork_right = &args->fork_tab[i + 1];
	}
	memset(&args->philo[i], 0, sizeof(t_philo));
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

void get_arguments(int ac, char **av, t_args *args)
{
    char    *err;
    
    if (!(ac == 5 || ac == 6))
        clean_and_exit(args, 0, "Wrong number of parameters !");
    memset(args, 0, sizeof(t_args));
	if ((err = check_args(av, args)) && err)
		clean_and_exit(args, 0, err);
	if (!(args->thread_tab = malloc(sizeof(pthread_t) * args->nb_philo)))
		clean_and_exit(args, 0, "Malloc in thread_tab failed...");
	if (!(args->fork_tab = malloc(sizeof(pthread_mutex_t) * args->nb_philo)))
		clean_and_exit(args, 1, "Malloc in forks_tab failed...");
    if (!(args->philo = malloc(sizeof(t_philo) * args->nb_philo)))
		clean_and_exit(args, 2, "Malloc in philo_tab failed...");
}

int main(int ac, char **av)
{
    t_args  args;
    int     i;
    void    *value_ptr;

    get_arguments(ac, av, &args);
    start_mutexes(&args);
	prepare_threads(&args);
    start_threads(&args);
	i = 0;
    value_ptr = (void *)666;
 //   while (i < args.nb_philo)
 //       pthread_detach(args.thread_tab[i++]);
    i = 0;
	while (value_ptr && i < args.nb_philo)  // a mon avis faut qu'il attende que le premier
        pthread_join(args.thread_tab[i++], &value_ptr);   //genre while ptr == NULL
 //   while (i < args.nb_philo)
 //       pthread_join(args.thread_tab[i++], NULL);
	clean_and_exit(&args, 3, "\nBYE\n");
	return (0);
}