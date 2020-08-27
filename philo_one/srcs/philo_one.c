/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_one.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lemarabe <lemarabe@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/08/27 18:30:38 by lemarabe          #+#    #+#             */
/*   Updated: 2020/08/27 22:45:29 by lemarabe         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo_one.h"

void *philo_routine(void *arg)
{
    struct timeval *tp;
    
    if (!(tp = malloc(sizeof(struct timeval))))
        return (NULL);
    write(1, "yo\n", 3);
    gettimeofday(tp, NULL);
    printf("my arg is %d characters long\n", ft_strlen(arg));
    printf("the time is : %ld and %d\n", tp->tv_sec, tp->tv_usec);
    return (tp);
}

char *check_args(int ac, char **av, t_philo *philo)
{
    if (!(ac == 5 || ac == 6))
        return ("Wrong number of parameters !");
    if (ft_atoi_ulong(av[1]) < 2)
        return ("You should have more than 1 philosopher !");
    philo->nb_philo = ft_atoi_ulong(av[1]);
    if (ft_atoi_ulong(av[2]) <= 0)
        return ("Time to die must be a strictly positive number !");
    philo->to_die = ft_atoi_ulong(av[2]);
    if (ft_atoi_ulong(av[3]) <= 0)
        return ("Time to eat must be a strictly positive number !");
    philo->to_eat = ft_atoi_ulong(av[3]);
    if (ft_atoi_ulong(av[4]) <= 0)
        return ("Time to sleep must be a strictly positive number !");
    philo->to_sleep = ft_atoi_ulong(av[4]);
    if (av[5])
    {
        if (ft_atoi_ulong(av[5]) <= 0)
            return ("Number of rounds must be a strictly positive number !");
        philo->nb_laps = ft_atoi_ulong(av[5]);
    }
    return (NULL);
}

int main(int ac, char **av)
{
    t_philo philo;
    char    *err;
    pthread_t thread;
//    struct timeval    *tp = NULL;
    void *ptr;
    
    if ((err = check_args(ac, av, &philo)) && err)
        return (parse_error(err));
    printf("hi thread\n");
    pthread_create(&thread, NULL, &philo_routine, "test arguments");
    pthread_detach(thread);
    pthread_join(thread, &ptr);
    printf("bye thread\n");
    return (0);
}