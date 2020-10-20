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