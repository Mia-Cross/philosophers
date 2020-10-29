#ifndef PHILO_ONE_H
# define PHILO_ONE_H

# include <unistd.h>
# include <string.h>
# include <stdlib.h>
# include <sys/time.h>
# include <pthread.h>
# include <semaphore.h>

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
    int         *quit;
	pthread_t   thread;
    sem_t       *forks;
    sem_t       *channel;
    sem_t       *state;
}               t_philo;

typedef struct s_args
{
	int         nb_philo;
	t_time	    time;
    int         nb_laps;
    int         quit;
    t_philo     *philo;
    pthread_t   control;
    sem_t       *forks;
    sem_t       *channel;
}              t_args;

void start_philo_threads(t_args *args);
void get_arguments(int ac, char **av, t_args *args);
void start_semaphores(t_args *args);
void *philo_life(void *arg);
int check_death_clock(t_timeval death_time);
void update_death_clock(t_timeval *death, time_t to_die);
void display_action(t_philo *philo, char *action);
time_t get_time_since_start(t_timeval start);
int clean_and_exit(t_args *args, int to_free, char *str);
void destroy_mutexes(t_args *args);
int ft_strlen(char *str);
unsigned long ft_atoi_ulong(char *str);
char	*ft_itoa(unsigned long nbr);

#endif