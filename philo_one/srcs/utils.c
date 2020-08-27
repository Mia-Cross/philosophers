/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lemarabe <lemarabe@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/08/27 18:54:24 by lemarabe          #+#    #+#             */
/*   Updated: 2020/08/27 21:59:59 by lemarabe         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo_one.h"

int ft_strlen(char *str)
{
    int i;

    i = 0;
    while (str[i])
        i++;
    return (i);
}

unsigned long ft_atoi_ulong(char *str)
{
    unsigned long out;
    int i;
    
    i = 0;
    out = 0;
    while (str[i] && str[i] <= '9' && str[i] >= '0')
        out = out * 10 + str[i++] - '0';
    return (out);
}

int parse_error(char *str)
{
    write(2, str, ft_strlen(str));
    exit(1);
}