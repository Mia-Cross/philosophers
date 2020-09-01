/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lemarabe <lemarabe@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/08/27 18:54:24 by lemarabe          #+#    #+#             */
/*   Updated: 2020/08/31 20:36:37 by lemarabe         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo_one.h"

int clean_and_exit(t_args *args, int to_free, char *str)
{
    if (to_free)
    {
        free(args->thread_tab);
        if (to_free > 1)
        {
            free(args->fork_tab);
            if (to_free > 2)
                free(args->philo);
        }
    }
    write(2, str, ft_strlen(str));
    write(2, "\n", 1);
    exit(1);
}

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

/*void ft_putunsigned_long(time_t nbr)
{
	char c;

	if (nbr > 9)
		ft_putunsigned_long((nbr / 10));
	c = nbr % 10 + '0';
	write(1, &c, 1);
} */




static int		nbr_len(unsigned long p)
{
	int		i;

    if (p == 0)
		return (1);
	i = 0;
	while (p)
	{
		p = p / 10;
		i++;
	}
	return (i);
}

static char		*ft_strrev(char *str)
{
	int		i;
	int		j;
	char	c;

	i = 0;
	j = 0;
	while (str[i])
		i++;
	i--;
	while (i > j)
	{
		c = str[i];
		str[i] = str[j];
		str[j] = c;
		i--;
		j++;
	}
	return (str);
}

static char		*print_nbr(char *str, unsigned long p, int n_len)
{
	int		i;

	i = 0;
	while (p)
	{
		str[i] = p % 10 + '0';
		p = p / 10;
		i++;
	}
	str[n_len] = 0;
	return (str);
}

char			*ft_itoa(unsigned long nbr)
{
	char	*str;
	int		n_len;

	n_len = nbr_len(nbr);
	if (!(str = (char *)malloc(sizeof(char) * (n_len + 1))))
		return (NULL);
	else if (nbr == 0)
	{
		str[0] = '0';
		str[1] = '\0';
		return (str);
	}
	str = print_nbr(str, nbr, n_len);
	return (ft_strrev(str));
}