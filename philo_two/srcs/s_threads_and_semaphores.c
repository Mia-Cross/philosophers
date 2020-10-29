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
        //usleep(200);
		pthread_create(&args->philo[i].thread, NULL, &philo_life, &args->philo[i]);
	}
}

void start_semaphores(t_args *args)
{
    int i;

    args->forks = sem_open("forks", 0x0008, 0x0080, args->nb_philo);
    args->channel = sem_open("channel", 0x0008, 0x0080, 1);
    i = -1;
    while (++i < args->nb_philo)
        args->philo[i].state = sem_open("state", 0x0008, 0x0080, 1);
}

void destroy_semaphores(t_args *args)
{
    (void)args;
    sem_unlink("forks");
    sem_unlink("channel");
    sem_unlink("state");
}

int clean_and_exit(t_args *args, int to_free, char *str)
{
	if (to_free)
        destroy_semaphores(args);
    write(2, str, ft_strlen(str));
    write(2, "\n", 1);
    exit(0);
}