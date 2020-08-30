#include "philo_one.h"

void update_death_clock(t_time *time, int philo_num)
{
	gettimeofday(&time->death[philo_num], NULL);
	time->death[philo_num].tv_usec += time->to_die;
	if (time->death[philo_num].tv_usec > 999999)
	{
		time->death[philo_num].tv_sec += 1;
		time->death[philo_num].tv_usec -= 1000000;
	}
}

time_t get_time_since_start(t_timeval start)
{
	t_timeval now;
	time_t	diff;
	time_t time_since;

	gettimeofday(&now, NULL);
	diff = now.tv_sec - start.tv_sec;
    time_since = now.tv_usec - start.tv_usec + (1000000 * diff);
//    printf("Now-time is : %ld and %d\n", now.tv_sec, now.tv_usec);
//    printf("start-time is : %ld and %d\n", start.tv_sec, start.tv_usec);
//    printf("Time since exec is : %ld\n", time_since_exec);
	return (time_since);
}


int check_death_clock(t_timeval death_time)
{
	t_timeval now;

    gettimeofday(&now, NULL);
    if (now.tv_sec > death_time.tv_sec)
        return (1);
    if (now.tv_usec >= death_time.tv_usec)
        return (1);
    return(0);
}
