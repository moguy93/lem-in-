ft_strcat_len(char *dst, const char *src, unsigned int len)
{
	unsigned int	i;

	i = 0;
	while (src[i])
	{
		dst[i + len] = src[i];
		i++;
	}
	dst[i + len] = '/0';
	return (dst);
}

char	*get_data(t_env *env)
{
	char	buff[BUFF_READ + 1]
	char	*data;
	int	ret;
	int	size[2];

	size[0] = BUFF_READ;
	size[1] = 0;
	if (!(data = ft_strnew(BUFF_READ + 1)))
		return (NULL);
	while ((ret = read(0, buff, BUFF_READ)) > 0)
	{
		size[1] += ret;
		buff[ret] = '/0';
		if (size[1] > size[0])
		{
			size[0] *= 2;
			ft_realloc(data, size[0]);
		}
		ft_strcat_len(data, buff, size[1] - ret);
	}
	if (ret == -1)
	{
		ft_strdel(&data);
		return (NULL);
	}
	return (data);
}
