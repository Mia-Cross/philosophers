#include "philo_two.h"

void start_philo_threads(t_args *args)
{
    int i;

    i = -1;
	gettimeofday(&args->time.start, NULL);
	while (++i < args->nb_philo)
	{
		memset(&args->philo[i], 0, sizeof(t_philo));
        args->philo[i].name = ft_itoa(i + 1);
        args->philo[i].time = &args->time;
        args->philo[i].laps_left = args->nb_laps;
		args->philo[i].quit = &args->quit;
        args->philo[i].forks = args->forks;
		args->philo[i].channel = args->channel;
        errno = 0;
        args->states[i] = sem_open(args->philo[i].name, O_CREAT, 0777, 1);
        perror(strerror(errno));
        args->philo[i].state = args->states[i];
        //usleep(200);
		pthread_create(&args->philo[i].thread, NULL, &philo_life, &args->philo[i]);
	}
}

void destroy_semaphores(t_args *args)
{
    int i;
    (void)args;

    errno = 0;
    sem_unlink("forks");
    perror(strerror(errno));
    errno = 0;
    sem_unlink("channel");
    perror(strerror(errno));
    i = -1;
    while (++i < args->nb_philo)
    {
        errno = 0;
        sem_unlink(args->philo[i].name);
        perror(strerror(errno));
    }
}

void start_semaphores(t_args *args)
{
 //   destroy_semaphores(args);
    errno = 0;
    args->forks = sem_open("forks", O_CREAT, 0777, args->nb_philo);
    perror(strerror(errno));
    errno = 0;
    args->channel = sem_open("channel", O_CREAT, 0777, 1);
    perror(strerror(errno));
}

int clean_and_exit(t_args *args, int to_free, char *str)
{
    int i;

	if (to_free)
    {
	    if (to_free > 1)
        {
            usleep(100);
            destroy_semaphores(args);
            i = -1;
            while (++i < args->nb_philo)
                free(args->philo[i].name);
            free(args->states);
        }
        free(args->philo);
    }
    write(2, str, ft_strlen(str));
    write(2, "\n", 1);
    exit(0);
}