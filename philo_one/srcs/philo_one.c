/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_one.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lemarabe <lemarabe@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/08/27 18:30:38 by lemarabe          #+#    #+#             */
/*   Updated: 2020/08/27 21:03:05 by lemarabe         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo_one.h"

int parse_error(char *str)
{
    write(2, str, ft_strlen(str));
    exit(1);
}

char *check_args(char **av, t_time *time)
{
    if (av[1] < 2)
        return ("You should have more than 1 philosopher !");
    time->nb_philo = av[1];
    if (av[2] <= 0)
        return ("Time to die must be a strictly positive number !");
    time->to_die = av[2];
    if (av[3] <= 0)
        return ("Time to eat must be a strictly positive number !");
    time->to_eat = av[3];
    if (av[4] <= 0)
        return ("Time to sleep must be a strictly positive number !");
    time->to_sleep = av[4];
    if (av[5])
    {
        if (av[5] <= 0)
            return ("Number of rounds must be a strictly positive number !");
        time->laps = av[5];
    }
    return (NULL);
}

int main(int ac, char **av)
{
    t_time time;
    char *err;
    
    if ((err = check_args(av, &time)) && err)
        return (parse_error(err));
    
}