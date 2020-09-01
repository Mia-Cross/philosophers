/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   debug.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lemarabe <lemarabe@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/09/01 19:50:01 by lemarabe          #+#    #+#             */
/*   Updated: 2020/09/01 19:50:02 by lemarabe         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo_one.h"

void print_timeval(t_timeval time, char *name)
{
	char *sec;
	char *usec;
    char *msg;
    int i;

    sec = ft_itoa(time.tv_sec);
	usec = ft_itoa(time.tv_usec);
    if (!(msg = malloc(sizeof(char) * (ft_strlen(sec) + ft_strlen(usec) + ft_strlen(name) + 8))))
        return;
    i = 0;
    while (*name != '\0')
        msg[i++] = *name++;
    msg[i++] = ':';
	msg[i++] = ' ';
    while (*sec != '\0')
        msg[i++] = *sec++;
    msg[i++] = ',';
    while (*usec != '\0')
        msg[i++] = *usec++;
	msg[i++] = '\n';
    msg[i++] = '\0';
    write(1, msg, ft_strlen(msg));
  //  free(time);
  //  free(philo_name);
    free(msg);
}

void ft_putchar(char c)
{
	write(1, &c, 1);
}

void ft_putstr(char *str)
{
	int i;

	i = 0;
	while (str[i])
		ft_putchar(str[i++]);
}

void ft_putunsigned_long(time_t nbr)
{
	char c;

	if (nbr > 9)
		ft_putunsigned_long((nbr / 10));
	c = nbr % 10 + '0';
	write(1, &c, 1);
}