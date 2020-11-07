/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: user42 <user42@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/07 02:25:24 by user42            #+#    #+#             */
/*   Updated: 2020/11/07 02:51:13 by user42           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo_one.h"

int				ft_strlen(char *str)
{
	int	i;

	i = 0;
	while (str && str[i])
		i++;
	return (i);
}

unsigned long	ft_atoi_ulong(char *str)
{
	unsigned long	out;
	int				i;

	i = 0;
	out = 0;
	while (str[i] && str[i] <= '9' && str[i] >= '0')
		out = out * 10 + str[i++] - '0';
	return (out);
}

void			update_death_clock(t_timeval *death, time_t to_die)
{
	gettimeofday(death, NULL);
	death->tv_usec += to_die;
	if (death->tv_usec > 999999)
	{
		death->tv_sec += 1;
		death->tv_usec -= 1000000;
	}
}

time_t			get_time_since_start(t_timeval start)
{
	t_timeval	now;
	time_t		diff;
	time_t		time_since;

	gettimeofday(&now, NULL);
	diff = now.tv_sec - start.tv_sec;
	time_since = now.tv_usec - start.tv_usec + (1000000 * diff);
	return (time_since / 1000);
}

int				check_death_clock(t_timeval death_time)
{
	t_timeval	now;

	gettimeofday(&now, NULL);
	if (now.tv_sec > death_time.tv_sec)
		return (0);
	if (now.tv_sec == death_time.tv_sec && now.tv_usec >= death_time.tv_usec)
		return (0);
	return (1);
}
