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

typedef struct s_time
{
    time_t  	to_die;
    time_t  	to_eat;
    time_t  	to_sleep;
	t_timeval	start;
	t_timeval	*death;
}				t_time;

typedef struct s_args
{
	int nb_philo;
	t_time	time;
    int     philo_num;
    int     nb_laps;
	pthread_mutex_t *fork;
}              t_args;

int ft_strlen(char *str);
int parse_error(char *str);
void ft_putunsigned_long(time_t nbr);
unsigned long ft_atoi_ulong(char *str);

void update_death_clock(t_time *time, int philo_num);
void display_action(t_timeval start, int philo, char *action);
time_t get_time_since_start(t_timeval start);
int philosopher_sleeps(t_args *args);
int philosopher_eats(t_args *args);
void philosopher_thinks(t_args *args);
int check_death_clock(t_timeval death_time);
//void philosopher_eats(t_timeval exec_time, time_t time_to_eat, int philo_num);
//void philosopher_sleeps(t_timeval exec_time, time_t time_to_sleep, int philo_num);
//void philosopher_thinks(t_timeval exec_time, time_t time_to_die, int philo_num);

#endif