#include "philo_one.h"

void display_action(t_timeval start, char *philo, char *action)
{
    char *time;
    char *msg;
    int i;

    time = ft_itoa(get_time_since_start(start));
    if (!(msg = malloc(sizeof(char) * (ft_strlen(time) + ft_strlen(philo) + ft_strlen(action) + 8))))
        return;
    i = 0;
    while (*time != '\0')
        msg[i++] = *time++;
    msg[i++] = ' ';
    while (*philo != '\0')
        msg[i++] = *philo++;
    msg[i++] = ' ';
    while (*action != '\0')
        msg[i++] = *action++;
    msg[i++] = '\0';
    write(1, msg, ft_strlen(msg));
  //  free(time);
  //  free(philo_name);
    free(msg);
}

int philosopher_eats(t_philo *philo)
{
    if (philo->laps_left > 0)
        philo->laps_left -= 1;
	display_action(philo->time->start, philo->name, "is eating\n");
    //print_timeval(philo->death, philo->name);
    update_death_clock(&philo->death, philo->time->to_die);
    //print_timeval(philo->death, philo->name);
	usleep(philo->time->to_eat);
	pthread_mutex_unlock(philo->fork_left);
	pthread_mutex_unlock(philo->fork_right);
	if (check_death_clock(philo->death))
	{
    	display_action(philo->time->start, philo->name, "died E\n");
        //print_timeval(philo->death, philo->name);
        return (0);
    }
    return (1);
}

int philosopher_sleeps(t_philo *philo)
{
    display_action(philo->time->start, philo->name, "is sleeping\n");
    usleep(philo->time->to_sleep);
	if (check_death_clock(philo->death))
	{
    	display_action(philo->time->start, philo->name, "died S\n");
        //print_timeval(philo->death, philo->name);
        return (0);
    }
    return (1);
}

int philosopher_thinks(t_philo *philo)
{
    display_action(philo->time->start, philo->name, "is thinking\n");
	pthread_mutex_lock(philo->fork_left);
	if (check_death_clock(philo->death))
	{
    	display_action(philo->time->start, philo->name, "died F1\n");
    //    print_timeval(philo->death, philo->name);
        return (0);
    }
	display_action(philo->time->start, philo->name, "has taken a fork\n");
	pthread_mutex_lock(philo->fork_right);
	if (check_death_clock(philo->death))
	{
    	display_action(philo->time->start, philo->name, "died F2\n");
        //print_timeval(philo->death, philo->name);
        return (0);
    }
	display_action(philo->time->start, philo->name, "has taken a fork\n");
    return (1);
}