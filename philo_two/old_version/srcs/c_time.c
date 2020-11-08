/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   time.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lemarabe <lemarabe@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/09/01 19:50:12 by lemarabe          #+#    #+#             */
/*   Updated: 2020/09/08 21:02:40 by lemarabe         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo_two.h"

void update_death_clock(t_timeval *death, time_t to_die)
{
	gettimeofday(death, NULL);
	death->tv_usec += to_die;
	if (death->tv_usec > 999999)
	{
		death->tv_sec += 1;
		death->tv_usec -= 1000000;
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
	return (time_since / 1000);
}


int check_death_clock(t_timeval death_time, sem_t *channel)
{
	t_timeval now;
	(void)channel;
//	char *usec;
//	char *sec;

    gettimeofday(&now, NULL);
/*	sec = ft_itoa(now.tv_sec);
	usec = ft_itoa(now.tv_usec);
	sem_wait(channel);
	write(1, sec, ft_strlen(sec));
	write(1, ",", 1);
	write(1, usec, ft_strlen(usec));
	sec = ft_itoa(death_time.tv_sec);
	usec = ft_itoa(death_time.tv_usec);
	write(1, ":", 1);
	write(1, sec, ft_strlen(sec));
	write(1, ",", 1);
	write(1, usec, ft_strlen(usec));
	write(1, "\n", 1);
	sem_post(channel);
	free(sec);
	free(usec); */
    if (now.tv_sec > death_time.tv_sec)
        return (0);
    if (now.tv_sec == death_time.tv_sec && now.tv_usec >= death_time.tv_usec)
        return (0);
    return(1);
}

