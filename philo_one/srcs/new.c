void *monitor_clocks(void *arg)
{
	t_args *args;
	int i;
	
    args = (t_args *)arg;
	usleep(args->time.to_die - 10);
	while (args->quit)
	{
		usleep(10);
	//	write(1, "begin clock check\n", 18);
		i = -1;
		while (++i < args->nb_philo)
		{
			if (check_death_clock(args->philo[i].death))
			{
			//	write(1, "death toll\n", 11);
				pthread_mutex_unlock(&args->philo[i].state);
				args->philo[i].alive = 0;
				display_action(args->philo[i].channel, args->philo[i].time->start, args->philo[i].name, "died\n");
				args->quit = 0;
			}
		}
	}
	return (NULL);
}

void *monitor_laps(void *arg)
{
	t_args *args;
	int i;
	
    args = (t_args *)arg;
	usleep(args->time.to_die - 10);
	while (args->quit)
	{
		usleep(10);
		i = -1;
		while (++i < args->nb_philo)
		{
			if (!args->philo[i].laps_left)
			{
				args->philo[i].laps_left = -1;
				if (args->quit > 0)
					args->quit -= 1;
			}
		}
	}
	return (NULL);
}


void *monitor_clocks_and_laps(void *arg)
{
	int i;
	t_args *args;
	
    args = (t_args *)arg;
	args->quit = args->nb_philo;
	usleep(args->time.to_die - 10);
	while (args->quit)
	{
		usleep(10);
		i = -1;
		while (++i < args->nb_philo)
		{
			if (!args->philo[i].laps_left)
			{
				args->philo[i].laps_left = -1;
//				pthread_mutex_unlock(&args->philo[i].state);
				args->quit -= 1;
			}
			if (check_death_clock(args->philo[i].death))
			{
				display_action(args->philo[i].channel, args->philo[i].time->start, args->philo[i].name, "died\n");
				args->quit = 0;
//				args->philo[i].alive = 0;
//				pthread_mutex_unlock(&args->philo[i].state);
	//			return (NULL);
			}
		}
	}
	return (NULL);
}

void *death_reaper(void *arg)
{
	t_philo *philo;

	philo = (t_philo *)arg;
	usleep(philo->time->to_die - 100);
	pthread_mutex_lock(&philo->state);
	return (NULL);
}

void lock_alive_state(t_philo *philo, int nb_philo)
{
	int i;

	i = -1;
	while (++i < nb_philo)
		pthread_mutex_lock(&philo[i].state);
}