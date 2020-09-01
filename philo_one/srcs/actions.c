#include "philo_one.h"

/*void display_action(t_timeval start, int philo, char *action)
{
//    time_t exec_time;
    char *philo_name;
    char *time;
    char *msg;
    int i;

//    exec_time = get_time_since_start(start);
    time = ft_itoa(get_time_since_start(start));
    philo_name = ft_itoa(philo);
    if (!(msg = malloc(sizeof(char) * (ft_strlen(time) + ft_strlen(philo_name) + ft_strlen(action) + 8))))
        return;
    i = 0;
    while (*time != '\0')
        msg[i++] = *time++;
    msg[i++] = ' ';
    while (*philo_name != '\0')
        msg[i++] = *philo_name++;
    msg[i++] = ' ';
    while (*action != '\0')
        msg[i++] = *action++;
    msg[i++] = '\0';
    write(1, msg, ft_strlen(msg));
  //  free(time);
  //  free(philo_name);
    free(msg);
} */

/*void display_action(int **disp, t_timeval start, char *action)
{
	(void)start;
//	*disp[0] = get_time_since_start(start);
	write(1, &disp[0], 1);
	write(1, (char *)&disp[1], 1);
	write(1, (char *)&disp[2], 1);
	write(1, &disp[3], 1);
	write(1, (time_t)(disp[0]), 1);
	write(1, (char)disp[1], 1);
	write(1, (int)disp[2], 1);
	write(1, (char)disp[3], 1); 
	write(1, action, ft_strlen(action));
} */

void display_action(t_timeval start, int *num, char *action)
{
	time_t	*exec_time;

	exec_time = NULL;
	exec_time = (time_t *)get_time_since_start(start);
	write(1, (time_t *)&exec_time, 1);
	write(1, " ", 1);
	write(1, (int *)&num, 1);
	write(1, " ", 1);
	write(1, action, ft_strlen(action));
}

void philosopher_eats(t_philo *philo)
{
	display_action(philo->time->start, &philo->num, "is eating\n");
    update_death_clock(&philo->death, philo->time->to_die);
	usleep(philo->time->to_eat);
	pthread_mutex_unlock(philo->fork_left);
	pthread_mutex_unlock(philo->fork_right);
	if (check_death_clock(philo->death))
	{
    	display_action(philo->time->start, &philo->num, "died E\n");
        exit(0);
    }
}

void philosopher_sleeps(t_philo *philo)
{
    display_action(philo->time->start, &philo->num, "is sleeping\n");
    usleep(philo->time->to_sleep);
	if (check_death_clock(philo->death))
	{
    	display_action(philo->time->start, &philo->num, "died S\n");
        exit(0);
    }
}

void philosopher_thinks(t_philo *philo)
{
    display_action(philo->time->start, &philo->num, "is thinking\n");
	pthread_mutex_lock(philo->fork_left);
	if (check_death_clock(philo->death))
	{
    	display_action(philo->time->start, &philo->num, "died F1\n");
        exit(0);
    }
	display_action(philo->time->start, &philo->num, "has taken a fork\n");
	pthread_mutex_lock(philo->fork_right);
	if (check_death_clock(philo->death))
	{
    	display_action(philo->time->start, &philo->num, "died F2\n");
        exit(0);
    }
	display_action(philo->time->start, &philo->num, "has taken a fork\n");
}