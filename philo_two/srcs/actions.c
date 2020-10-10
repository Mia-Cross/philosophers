/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   actions.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lemarabe <lemarabe@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/09/01 19:50:07 by lemarabe          #+#    #+#             */
/*   Updated: 2020/09/08 20:39:26 by lemarabe         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo_two.h"

void display_action(t_timeval start, char *philo, char *action)
{
    char *time;
    char *msg;
    int i;
	int j;

    time = ft_itoa(get_time_since_start(start));
    if (!(msg = malloc(sizeof(char) * (ft_strlen(time) + ft_strlen(philo) + ft_strlen(action) + 8))))
        return;
    i = 0;
	j = 0;
    while (time[j] != '\0')
        msg[i++] = time[j++];
    msg[i++] = ' ';
    while (*philo != '\0')
        msg[i++] = *philo++;
    msg[i++] = ' ';
    while (*action != '\0')
        msg[i++] = *action++;
    msg[i++] = '\0';
    write(1, msg, ft_strlen(msg));
	free(time);
    free(msg);
}

int clean_and_exit(t_args *args, int to_free, char *str)
{
	int i;
	
    if (to_free)
    {
        if (to_free > 1)
        {
            if (to_free > 2)
			{
				i = -1;
				while (++i < args->nb_philo)
					free(args->philo[i].name);
                free(args->philo);
			}
        }
        free(args->thread_tab);
    }
//	system("leaks philo_two");
    write(2, str, ft_strlen(str));
    write(2, "\n", 1);
    exit(0);
}