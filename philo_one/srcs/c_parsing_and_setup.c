/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing_and_exit.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lemarabe <lemarabe@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/09/08 20:16:50 by lemarabe          #+#    #+#             */
/*   Updated: 2020/09/08 20:48:44 by lemarabe         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo_one.h"

char *check_args(char **av, t_args *args)
{
    if (ft_atoi_ulong(av[1]) < 2)
        return ("You should have more than 1 philosopher !");
    args->nb_philo = ft_atoi_ulong(av[1]);
    if (ft_atoi_ulong(av[2]) <= 0)
        return ("Time to die must be a strictly positive number !");
    args->time.to_die = 1000 * ft_atoi_ulong(av[2]);
    if (ft_atoi_ulong(av[3]) <= 0)
        return ("Time to eat must be a strictly positive number !");
    args->time.to_eat = 1000 * ft_atoi_ulong(av[3]);
    if (ft_atoi_ulong(av[4]) <= 0)
        return ("Time to sleep must be a strictly positive number !");
    args->time.to_sleep = 1000 * ft_atoi_ulong(av[4]);
    if (av[5])
    {
        if (ft_atoi_ulong(av[5]) <= 0)
            return ("Number of rounds must be a strictly positive number !");
        args->nb_laps = ft_atoi_ulong(av[5]);
    }
    else
        args->nb_laps = -1;
    return (NULL);
}

void get_arguments(int ac, char **av, t_args *args)
{
    char    *err;
    
    if (!(ac == 5 || ac == 6))
        clean_and_exit(args, 0, "Wrong number of parameters !");
    memset(args, 0, sizeof(t_args));
	if ((err = check_args(av, args)) && err)
		clean_and_exit(args, 0, err);
	if (!(args->forks = malloc(sizeof(pthread_mutex_t) * args->nb_philo)))
		clean_and_exit(args, 0, "Malloc in forks_tab failed...");
	if (!(args->states = malloc(sizeof(pthread_t) * args->nb_philo)))
		clean_and_exit(args, 1, "Malloc in states failed...");
    if (!(args->philo = malloc(sizeof(t_philo) * args->nb_philo)))
		clean_and_exit(args, 2, "Malloc in philo_tab failed...");
}

void display_action(pthread_mutex_t *channel, t_timeval start, char *philo, char *action)
{
    char *time;

//	(void)philo;
//	(void)action;
/*	(void)channel;
    char *msg;
    int i;
	int j; */

    time = ft_itoa(get_time_since_start(start));
 //   if (!(msg = malloc(sizeof(char) * (ft_strlen(time) + ft_strlen(philo) + ft_strlen(action) + 8))))
 //       return;
	pthread_mutex_lock(channel);
	write(1, time, ft_strlen(time));
	write(1, " ", 1);
	write(1, philo, ft_strlen(philo));
	write(1, " ", 1);
	write(1, action, ft_strlen(action)); 
	pthread_mutex_unlock(channel);
/*    i = 0;
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
    free(msg);*/
	free(time);
}

static int		convert_to_str(long unsigned int n, char *buff, int start)
{
	int			i;
	int			ret;

	i = start;
	while (n || (!i && !n))
	{
		buff[i++] = n % 10 + 48;
		n = n / 10;
	}
	buff[i] = '\0';
	ret = i - start;
	i--;
	while (start < i)
	{
		buff[start] ^= buff[i];
		buff[i] ^= buff[start];
		buff[start] ^= buff[i];
		start++;
		i--;
	}
	return (ret);
}

static int		insert_status(char *buff, char *status, int i)
{
	buff = buff + i;
	while (status)
	{
		(*((unsigned int *)buff)) = (*((unsigned int *)status));
		if (status[0] && status[1] && status[2] && status[3])
			status += sizeof(unsigned int);
		else
		{
			while (*status)
			{
				*buff = *status;
				buff++;
				status++;
				i++;
			}
			break ;
		}
		buff += sizeof(unsigned int);
		i += sizeof(unsigned int);
	}
	*buff = '\0';
	return (i);
}

void			display(pthread_mutex_t *speaking,
	long unsigned int time, int id, char *status)
{
	char		tab[50];
	int 		ret;

	ret = convert_to_str(time, tab, 0);
	tab[ret] = ' ';
	ret += convert_to_str((long unsigned int)id, tab, ret + 1);
	tab[ret + 1] = ' ';
	ret = insert_status(tab, status, ret + 2);
	pthread_mutex_lock(speaking);
	write(1, tab, ret);
	if (ft_strlen(status) != 5)
		pthread_mutex_unlock(speaking);
}