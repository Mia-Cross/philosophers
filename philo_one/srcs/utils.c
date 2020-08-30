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


void ft_putunsigned_long(time_t nbr)
{
	char c;

	if (nbr > 9)
		ft_putunsigned_long((nbr / 10));
	c = nbr % 10 + '0';
	write(1, &c, 1);
}

void display_action(t_timeval ref, int philo, char *action)
{
    t_timeval now;
    time_t time_since_exec;

    gettimeofday(&now, NULL);
    if (now.tv_sec == ref.tv_sec)
        time_since_exec = now.tv_usec - ref.tv_usec;
    else
        time_since_exec = 1000000 + now.tv_usec - ref.tv_usec;
//    printf("Now-time is : %ld and %d\n", now.tv_sec, now.tv_usec);
//    printf("Ref-time is : %ld and %d\n", ref.tv_sec, ref.tv_usec);
//    printf("Time since exec is : %ld\n", time_since_exec);
    ft_putunsigned_long(time_since_exec);
    write(1, "ms -> ", 6);
    ft_putunsigned_long((unsigned long)philo);
    write(1, " ", 1);
    write(1, action, ft_strlen(action));
}

t_timeval get_new_death_time(t_timeval ref, time_t time_to_die)
{
    t_timeval death_time;

    death_time.tv_sec = ref.tv_sec;
    death_time.tv_usec = ref.tv_usec + time_to_die;
    if (death_time.tv_usec > 999999)
    {
        death_time.tv_sec += 1;
        death_time.tv_usec -= 1000000;
    }
    return(death_time);
}

int is_alive(t_timeval death_time)
{
    t_timeval ref;

    gettimeofday(&ref, NULL);
    if (ref.tv_sec > death_time.tv_sec)
        return (0);
    if (ref.tv_usec >= death_time.tv_usec)
        return (0);
    return(1);
}

void philosopher_eats(t_timeval exec_time, time_t time_to_eat, int philo_num)
{
    display_action(exec_time, philo_num, "is eating\n");
    usleep(time_to_eat);
}

void philosopher_sleeps(t_timeval exec_time, time_t time_to_sleep, int philo_num)
{
    display_action(exec_time, philo_num, "is sleeping\n");
    usleep(time_to_sleep);
}

void philosopher_thinks(t_timeval exec_time, time_t time_to_die, int philo_num)
{
    (void)time_to_die;
    
    display_action(exec_time, philo_num, "is thinking\n");
//    while (fork_is_not_available)
        usleep(1);
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