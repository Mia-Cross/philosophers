/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_two.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: user42 <user42@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/07 03:02:00 by user42            #+#    #+#             */
/*   Updated: 2020/11/08 20:25:51 by user42           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_TWO_H
# define PHILO_TWO_H

# include <unistd.h>
# include <string.h>
# include <stdlib.h>
# include <fcntl.h>
# include <sys/time.h>
# include <pthread.h>
# include <semaphore.h>

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
	sem_t				*forks;
	sem_t				*channel;
	sem_t				*state;
}						t_philo;

typedef struct			s_args
{
	int					nb_philo;
	t_time				time;
	int					nb_laps;
	int					quit;
	t_philo				*philo;
	sem_t				*forks;
	sem_t				*channel;
}						t_args;

void					get_arguments(int ac, char **av, t_args *args);
char					*semaphore_name(char *name);
void					unlink_previous_semaphores(t_args *args);
sem_t					*open_new_semaphore(char *name, int value);
void					start_semaphores(t_args *args);
void					set_philosophers(t_args *args);
void					start_threads(t_args *args);
void					*philo_life(void *arg);
void					*philo_control(void *arg);
void					update_death_clock(t_timeval *death, time_t to_die);
int						check_death_clock(t_timeval death_time);
time_t					get_time_since_start(t_timeval start);
void					display_action(t_philo *philo, char *action);
void					wait_for_all_threads(t_args *args);
int						clean_and_exit(t_args *args, int to_free, char *str);
int						ft_strlen(char *str);
unsigned long			ft_atoi_ulong(char *str);
char					*ft_itoa(unsigned long nbr);

#endif