#include "philo_two.h"

char *semaphore_name(char *number)
{
    char *sem_name;
    int i;

    if (!(sem_name = malloc(sizeof(char) * (ft_strlen(number) + 1) + 1)))
        return (NULL);
    sem_name[0] = '/';
    i = -1;
    while (number[++i] && i < 8)
        sem_name[i + 1] = number[i];
    sem_name[i + 1] = '\0';
    free(number);
    return (sem_name);
}


sem_t *open_new_semaphore(char *name, int value)
{
    sem_t *sem;

    if (!name)
        return (NULL);
    if (!(sem = sem_open(name, O_CREAT | O_EXCL, 0600, value)))
        return (NULL);
    return (sem);
}

void set_philosophers(t_args *args)
{
    int i;

    i = -1;
	gettimeofday(&args->time.start, NULL);
	while (++i < args->nb_philo)
	{
        args->philo[i].time = &args->time;
        args->philo[i].laps_left = args->nb_laps;
		args->philo[i].quit = &args->quit;
        args->philo[i].forks = args->forks;
		args->philo[i].channel = args->channel;
	}
}


void destroy_semaphores(t_args *args, int nb_philo)
{
    int i;

    sem_unlink("/forks");
    sem_close(args->forks);
    if (nb_philo)
    {
        sem_unlink("/channel");
        sem_close(args->channel);
        if (nb_philo > 1)
        {
            i = -1;
            while (++i < nb_philo)
            {
                sem_unlink(args->philo[i].name);
                sem_close(args->philo[i].state);
            }
        }
    }
}

void unlink_previous_semaphores(t_args *args)
{
    int i;

    sem_unlink("/forks");
    sem_unlink("/channel");
    i = -1;
    while (++i < args->nb_philo)
        sem_unlink(args->philo[i].name);
}


void start_semaphores(t_args *args)
{
    int i;

    args->forks = open_new_semaphore("/forks", args->nb_philo);
    if (!args->forks)
        clean_and_exit(args, 1, "Failed to open semaphore : forks");
    args->channel = open_new_semaphore("/channel", 1);
    if (!args->channel)
        clean_and_exit(args, 2, "Failed to open semaphore : channel");
    i = -1;
    while (++i < args->nb_philo)
    {
        args->philo[i].state = open_new_semaphore(args->philo[i].name, 1);
        if (!args->philo[i].state)
            clean_and_exit(args, (i + 3), "Failed to open semaphore : state");
    }
}

int clean_and_exit(t_args *args, int to_free, char *str)
{
	if (to_free)
    {
        if (to_free == 1)
            destroy_semaphores(args, 0);
        else if (to_free == 2)
            destroy_semaphores(args, 1);
        if (to_free > 2)
            destroy_semaphores(args, (to_free - 3));        
        free(args->philo);
    }
    write(2, str, ft_strlen(str));
    write(2, "\n", 1);
    exit(0);
}