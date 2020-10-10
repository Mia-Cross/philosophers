/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_two.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lemarabe <lemarabe@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/08/27 18:53:21 by lemarabe          #+#    #+#             */
/*   Updated: 2020/09/08 20:57:28 by lemarabe         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_TWO_H
# define PHILO_TWO_H

# include <unistd.h>
# include <string.h>
# include <stdlib.h>
# include <sys/time.h>
# include <pthread.h>
# include <semaphore.h>

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
    char        *name;
    t_time      *time;
    t_timeval   death;
    int         laps_left;
	sem_t 			*sem;
}               t_philo;

typedef struct s_args
{
	int             nb_philo;
	t_time	        time;
    int             nb_laps;
    pthread_t       *thread_tab;
	sem_t 			*sem;
    t_philo         *philo;
}              t_args;

void get_arguments(int ac, char **av, t_args *args);
char *check_args(char **av, t_args *args);
void start_semaphore(t_args *args);
void prepare_threads(t_args *args);
void start_threads(t_args *args);
void *philo_routine(void *arg);
void monitor_death_clocks(t_args args);
int check_death_clock(t_timeval death_time);
void update_death_clock(t_timeval *death, time_t to_die);
void display_action(t_timeval start, char *philo, char *action);
time_t get_time_since_start(t_timeval start);
int clean_and_exit(t_args *args, int to_free, char *str);
int ft_strlen(char *str);
unsigned long ft_atoi_ulong(char *str);
char	*ft_itoa(unsigned long nbr);

//void ft_putunsigned_long(time_t nbr);
//void ft_putchar(char c);
//void print_timeval(t_timeval time, char *name);
//void ft_putstr(char *str);
//void philosopher_sleeps(t_philo *philo);
//void philosopher_eats(t_philo *philo);
//void philosopher_thinks(t_philo *philo);

#endif