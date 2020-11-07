/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_one.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: user42 <user42@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/08/27 18:53:21 by lemarabe          #+#    #+#             */
/*   Updated: 2020/11/07 02:56:15 by user42           ###   ########.fr       */
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

typedef struct timeval	t_timeval;

typedef struct			s_time
{
	time_t				to_die;
	time_t				to_eat;
	time_t				to_sleep;
	t_timeval			start;
}						t_time;

typedef struct			s_philo
{
	char				*name;
	t_time				*time;
	t_timeval			death;
	int					laps_left;
	int					*quit;
	pthread_t			thread;
	pthread_t			control;
	pthread_mutex_t		state;
	pthread_mutex_t		*channel;
	pthread_mutex_t		*fork_left;
	pthread_mutex_t		*fork_right;
}						t_philo;

typedef struct			s_args
{
	int					nb_philo;
	t_time				time;
	int					nb_laps;
	int					quit;
	t_philo				*philo;
	pthread_mutex_t		*forks;
	pthread_mutex_t		channel;
}						t_args;

void					get_arguments(int ac, char **av, t_args *args);
void					set_philosophers(t_args *args);
void					start_mutexes(t_args *args);
void					start_threads(t_args *args);
void					*philo_life(void *arg);
void					*simulation_control(void *arg);
void					wait_for_all_threads(t_args *args);
int						check_death_clock(t_timeval death_time);
void					update_death_clock(t_timeval *death, time_t to_die);
time_t					get_time_since_start(t_timeval start);
int						ft_strlen(char *str);
unsigned long			ft_atoi_ulong(char *str);
char					*ft_itoa(unsigned long nbr);
void					destroy_mutexes(t_args *args);
int						clean_and_exit(t_args *args, int to_free, char *str);

#endif
