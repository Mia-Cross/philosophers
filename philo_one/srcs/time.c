/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   time.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lemarabe <lemarabe@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/09/01 19:50:12 by lemarabe          #+#    #+#             */
/*   Updated: 2020/09/01 19:51:56 by lemarabe         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo_one.h"

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


int check_death_clock(t_timeval death_time)
{
	t_timeval now;

    gettimeofday(&now, NULL);
//	print_timeval(now, "|");
//	print_timeval(death_time, "_");
    if (now.tv_sec > death_time.tv_sec)
        return (1);
    if (now.tv_sec == death_time.tv_sec && now.tv_usec >= death_time.tv_usec)
        return (1);
    return(0);
}

void monitor_death_clocks(t_args args)
{
	int i;
//	int j;

	usleep(100 * args.nb_philo);
	while (1)
	{
		i = -1;
		while (++i < args.nb_philo)
		{
			if (check_death_clock(args.philo[i].death))
			{
				display_action(args.philo[i].time->start, args.philo[i].name, "died\n");
	//			j = -1;
	//			while (++j < args.nb_philo)  // a mon avis faut qu'il attende que le premier
	//				pthread_join(args.thread_tab[j], NULL);   //genre while ptr == NULL
				clean_and_exit(&args, 3, "\nBYE\n");
			}
		}
		usleep(10);
	}
}
