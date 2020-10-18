/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_one.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lemarabe <lemarabe@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/08/27 18:53:21 by lemarabe          #+#    #+#             */
/*   Updated: 2020/09/08 20:57:28 by lemarabe         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_ONE_H
# define PHILO_ONE_H

# include <unistd.h>
# include <string.h>
# include <stdlib.h>
# include <sys/time.h>
# include <pthread.h>

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
	int         alive;
	pthread_t       thread;
	pthread_mutex_t state;
	pthread_mutex_t *channel;
    pthread_mutex_t *fork_left;
    pthread_mutex_t *fork_right;
}               t_philo;

typedef struct s_args
{
	int             nb_philo;
	t_time	        time;
    int             nb_laps;
    pthread_t       clock;
    pthread_mutex_t *forks;
	pthread_t 		*states;
	pthread_mutex_t channel; 
    t_philo         *philo;
}              t_args;

void get_arguments(int ac, char **av, t_args *args);
char *check_args(char **av, t_args *args);
void start_mutexes(t_args *args);
void start_philo_threads(t_args *args);
void *philo_life(void *arg);
//void join_threads(t_args *args);
//void *monitor_death_clocks(void *arg);
int check_death_clock(t_timeval death_time);
void update_death_clock(t_timeval *death, time_t to_die);
void display_action(pthread_mutex_t *channel, t_timeval start, char *philo, char *action);
time_t get_time_since_start(t_timeval start);
int clean_and_exit(t_args *args, int to_free, char *str);
void destroy_mutexes(t_args *args);
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