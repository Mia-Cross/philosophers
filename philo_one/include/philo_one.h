/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_one.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lemarabe <lemarabe@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/08/27 18:53:21 by lemarabe          #+#    #+#             */
/*   Updated: 2020/08/31 19:31:19 by lemarabe         ###   ########.fr       */
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
}				t_time;

typedef struct  s_philo
{
    int         num;
    t_time      *time;
    t_timeval   death;
    pthread_mutex_t *fork_left;
    pthread_mutex_t *fork_right;
//	int 		*display[4];
}               t_philo;

typedef struct s_args
{
	int             nb_philo;
	t_time	        time;
    int             nb_laps;
    pthread_t       *thread_tab;
    pthread_mutex_t *fork_tab; 
    t_philo         *philo;
}              t_args;

int ft_strlen(char *str);
void ft_putunsigned_long(time_t nbr);
unsigned long ft_atoi_ulong(char *str);
char			*ft_itoa(unsigned long nbr);

int clean_and_exit(t_args *args, int to_free, char *str);
void update_death_clock(t_timeval *death, time_t to_die);
void display_action(t_timeval start, int *num, char *action);
//void display_action(int **disp, t_timeval start, char *action);
//void display_action(t_timeval start, int philo, char *action);
time_t get_time_since_start(t_timeval start);
void philosopher_sleeps(t_philo *philo);
void philosopher_eats(t_philo *philo);
void philosopher_thinks(t_philo *philo);
int check_death_clock(t_timeval death_time);

#endif