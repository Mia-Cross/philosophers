/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_one.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lemarabe <lemarabe@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/08/27 18:53:21 by lemarabe          #+#    #+#             */
/*   Updated: 2020/09/01 19:04:45 by lemarabe         ###   ########.fr       */
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
    char        *name;
    t_time      *time;
    t_timeval   death;
    int         laps_left;    
    pthread_mutex_t *fork_left;
    pthread_mutex_t *fork_right;
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
void ft_putchar(char c);
void print_timeval(t_timeval time, char *name);
void ft_putstr(char *str);

int clean_and_exit(t_args *args, int to_free, char *str);
void update_death_clock(t_timeval *death, time_t to_die);
void display_action(t_timeval start, char *philo, char *action);
time_t get_time_since_start(t_timeval start);
int philosopher_sleeps(t_philo *philo);
int philosopher_eats(t_philo *philo);
int philosopher_thinks(t_philo *philo);
int check_death_clock(t_timeval death_time);
void monitor_death_clocks(t_args args);

#endif