/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lemarabe <lemarabe@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/08/27 18:54:24 by lemarabe          #+#    #+#             */
/*   Updated: 2020/08/30 20:45:44 by lemarabe         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo_one.h"

void display_action(t_timeval start, int philo, char *action)
{
    ft_putunsigned_long(get_time_since_start(start));
    write(1, "ms -> ", 6);
    ft_putunsigned_long(philo);
    write(1, " ", 1);
    write(1, action, ft_strlen(action));
}

int philosopher_eats(t_args *args)
{
	if (check_death_clock(args->time.death[args->philo_num]))
	{
    	display_action(args->time.start, args->philo_num, "died before eating\n");
        return (0);
    }
	pthread_mutex_lock(&args->fork[args->philo_num]);
	display_action(args->time.start, args->philo_num, "has taken a fork\n");
	pthread_mutex_lock(&args->fork[(args->philo_num) + 1]);
	display_action(args->time.start, args->philo_num, "has taken a fork\n");
    update_death_clock(&args->time, args->philo_num);
	display_action(args->time.start, args->philo_num, "is eating\n");
	usleep(args->time.to_eat);
	pthread_mutex_unlock(&args->fork[args->philo_num]);
	pthread_mutex_unlock(&args->fork[(args->philo_num) + 1]);
	if (check_death_clock(args->time.death[args->philo_num]))
	{
    	display_action(args->time.start, args->philo_num, "died after eating\n");
        return (0);
    }
	return (1);
}

int philosopher_sleeps(t_args *args)
{
    display_action(args->time.start, args->philo_num, "is sleeping\n");
    usleep(args->time.to_sleep);
	if (check_death_clock(args->time.death[args->philo_num]))
	{
    	display_action(args->time.start, args->philo_num, "died after sleeping\n");
        return (0);
    }
	return (1);
}

void philosopher_thinks(t_args *args)
{
    display_action(args->time.start, args->philo_num, "is thinking\n");
//    while (fork_is_not_available)
//        usleep(1);
}


int ft_strlen(char *str)
{
    int i;

    i = 0;
    while (str[i])
        i++;
    return (i);
}

unsigned long ft_atoi_ulong(char *str)
{
    unsigned long out;
    int i;
    
    i = 0;
    out = 0;
    while (str[i] && str[i] <= '9' && str[i] >= '0')
        out = out * 10 + str[i++] - '0';
    return (out);
}

int parse_error(char *str)
{
    write(2, str, ft_strlen(str));
    write(2, "\n", 1);
    exit(1);
}

void ft_putunsigned_long(time_t nbr)
{
	char c;

	if (nbr > 9)
		ft_putunsigned_long((nbr / 10));
	c = nbr % 10 + '0';
	write(1, &c, 1);
}