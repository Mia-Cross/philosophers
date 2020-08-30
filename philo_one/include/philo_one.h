/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_one.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lemarabe <lemarabe@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/08/27 18:53:21 by lemarabe          #+#    #+#             */
/*   Updated: 2020/08/30 20:48:00 by lemarabe         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_ONE_H
# define PHILO_ONE_H

# include <unistd.h>
# include <string.h>
# include <stdlib.h>
# include <sys/time.h>
# include <pthread.h>

# include <stdio.h>

typedef struct timeval t_timeval;

typedef struct s_args
{
    int     philo_num;
    time_t  to_die;
    time_t  to_eat;
    time_t  to_sleep;
    int     nb_laps;
}              t_args;

int ft_strlen(char *str);
int parse_error(char *str);
void ft_putunsigned_long(time_t nbr);
unsigned long ft_atoi_ulong(char *str);

t_timeval get_new_death_time(t_timeval ref, time_t time_to_die);
void display_action(t_timeval ref, int philo, char *action);
t_timeval get_new_death_time(t_timeval ref, time_t time_to_die);
int is_alive(t_timeval death_time);
void philosopher_eats(t_timeval exec_time, time_t time_to_eat, int philo_num);
void philosopher_sleeps(t_timeval exec_time, time_t time_to_sleep, int philo_num);
void philosopher_thinks(t_timeval exec_time, time_t time_to_die, int philo_num);

#endif