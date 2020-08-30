/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_one.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lemarabe <lemarabe@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/08/27 18:30:38 by lemarabe          #+#    #+#             */
/*   Updated: 2020/08/30 20:45:10 by lemarabe         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo_one.h"

void *philo_routine(void *arg)
{
    t_args *args;
    t_timeval exec_time;
    t_timeval ref_time;
    t_timeval death_time;

    args = (t_args *)arg;
    gettimeofday(&exec_time, NULL);
//    printf("Ref time is : %ld and %d\n", ref.tv_sec, ref.tv_usec);
    while (1)
    {
        gettimeofday(&ref_time, NULL);
        death_time = get_new_death_time(ref_time, args->to_die);
        philosopher_eats(exec_time, args->to_eat, args->philo_num);
        if (!is_alive(death_time))
        {
            display_action(exec_time, args->philo_num, "died\n");
            break;
        }
        philosopher_sleeps(exec_time, args->to_sleep, args->philo_num);
        if (!is_alive(death_time))
        {
            display_action(exec_time, args->philo_num, "died\n");
            break;
        }
        philosopher_thinks(exec_time, args->to_die, args->philo_num);
        if (!is_alive(death_time))
        {
            display_action(exec_time, args->philo_num, "died\n");
            break;
        }
       
    }
    return (NULL);
}

char *check_args(int ac, char **av, t_args *args, int *nb_philo)
{
    if (!(ac == 5 || ac == 6))
        return ("Wrong number of parameters !");
    if (ft_atoi_ulong(av[1]) < 2)
        return ("You should have more than 1 philosopher !");
    *nb_philo = ft_atoi_ulong(av[1]);
    if (ft_atoi_ulong(av[2]) <= 0)
        return ("Time to die must be a strictly positive number !");
    args->to_die = ft_atoi_ulong(av[2]);
    if (ft_atoi_ulong(av[3]) <= 0)
        return ("Time to eat must be a strictly positive number !");
    args->to_eat = ft_atoi_ulong(av[3]);
    if (ft_atoi_ulong(av[4]) <= 0)
        return ("Time to sleep must be a strictly positive number !");
    args->to_sleep = ft_atoi_ulong(av[4]);
    if (av[5])
    {
        if (ft_atoi_ulong(av[5]) <= 0)
            return ("Number of rounds must be a strictly positive number !");
        args->nb_laps = ft_atoi_ulong(av[5]);
    }
    return (NULL);
}

int main(int ac, char **av)
{
    pthread_t   *thread_tab;
    t_args      args;
    int         nb_philo;
    char        *err;
    int         i;
    
    if ((err = check_args(ac, av, &args, &nb_philo)) && err)
        return (parse_error(err));
    if (!(thread_tab = malloc(sizeof(pthread_t) * nb_philo)))
        return (parse_error("Malloc in thread_tab failed..."));
    i = 0;
    while (i < nb_philo)
    {
        args.philo_num = i + 1;
        pthread_create(&thread_tab[i], NULL, &philo_routine, &args);
        i++;
    }
    i = 0;
    while (i < nb_philo)
    {
        pthread_join(thread_tab[i], NULL);
        i++;
    }
    return (0);
}