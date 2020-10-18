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
	pthread_t       thread;
	pthread_mutex_t *channel;
}               t_philo;

typedef struct s_args
{
	int             nb_philo;
	t_time	        time;
    int             nb_laps;
    pthread_t       clock;
    pthread_mutex_t *forks;
	pthread_mutex_t channel; 
    t_philo         *philo;
}              t_args;

#endif