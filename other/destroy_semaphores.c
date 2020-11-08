#include "include/philo_two.h"

int ft_strlen(char *str)
{
	int i;

	i = 0;
	while (str[i])
		i++;
	return (i);
}

char *semaphore_name(char *number)
{
    char *sem_name;
    int i;

    if (!(sem_name = malloc(sizeof(char) * (ft_strlen(number) + 1) + 1)))
        return (NULL);
    sem_name[0] = '/';
    i = -1;
    while (number[++i] && i < 8)
        sem_name[i + 1] = number[i];
    sem_name[i + 1] = '\0';
    free(number);
    return (sem_name);
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


void destroy_semaphores(t_args *args)
{
    int i;
    (void)args;
    char *lol;

    errno = 0;
    sem_unlink("/forks");
    perror(strerror(errno));
	errno = 0;
    sem_unlink("/channel");
    perror(strerror(errno));
    i = -1;
    while (++i < args->nb_philo)
    {
        lol = semaphore_name(ft_itoa(i + 1));
        errno = 0;
        sem_unlink(lol);
        perror(strerror(errno));
        free(lol);
    }
}

int main(int ac, char **av)
{
    t_args args;

    if (ac != 2)
    {
        write(1, "args bitch\n", 11);
        return (0);
    }
    args.nb_philo = atoi(av[1]);
    destroy_semaphores(&args);
}