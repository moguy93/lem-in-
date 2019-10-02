bool		is_cmd(char *data)
{
	if (data[0] == '#'  && data[1] == '#' && data[2] != '#')
		return (true);
	return (false);
}

bool		is_comment(char *data)
{
	if (data[0] == '#'  && data[1] != '#')
		return (true);
	return (false);
}

bool		is_pipe(char *data)
{
	unsigned int	i;
	unsigned int	count;

	i = 0;
	while (data[i] && data[i] != '\n')
	{
		if (data[i] == '-')
		{
			if (i == 0 || data[i + 1] == '\0' || data[i + 1] = '\n')
				return (false);
			count++;
		}
		i++;
	}
	if (count != 1 || i < 3)
		return (false);
	return (true);
}

bool		is_room(char *data)
{
	long long	nb;
	unsigned int	i;

	i = 0;
	if (!data[i] || data[i] == '#' || data[i] == 'L' || ft_is_white_space(data[i]))
		return (false);
	i++;
	while (data[i] && !(ft_is_white_space(data[i])))
		i++;
	while (data[i] && ft_is_white_space(data[i]))
		i++;
	if (data[i] == 0 || data[i] == '0' || !(ft_isdigit(data[i])))
		return (false);
	if ((nb = atoi(&data[i])) < 0 || nb > 2147483647)
		return (false);
	while (data[i] && ft_isdigit(data[i]))
		i++;
	if (!(ft_is_white_space(data[i])))
		return (false);
	while (data[i] && ft_is_white_space(data[i]))
		i++;
	if (data[i] == 0 || data[i] == '0' || !(ft_isdigit(data[i])))
		return (false);
	if ((nb = atoi(&data[i])) < 0 || nb > 2147483647)
		return (false);
	while (data[i] && ft_isdigit(data[i]))
		i++;
	while (data[i] && ft_is_white_space(data[i]))
		i++;
	if (data[i] != '\n')
		return (false);
	return (true);
}

void		next_line(char *data, unsigned int *j)
{
	unsigned int	i;

	i = *j;
	while (data[i] && data[i] != '\n')
		i++;
	*j = i + 1;
}

char		get_status(char *data, bool flush)
{
	static bool	pipe = false;

	if (flush)
	{
		pipe = false;
		return (0);
	}
	if (!pipe)
	{
		if (is_cmd(data))
		{
			if (ft_strncmp(data, "##start\n", 8))
				return ('s');
			else if (ft_strncmp(data, "##end\n", 6))
				return ('e');
			else
				return ('n');
		}
		else if (is_comment(data))
			return ('c');
		else if (is_room(data))
			return ('r');
	}
	if (is_comment(data))
		return ('c');
	else if (is_pipe(data) && pipe = true)
		return ('p');
	return (0);
}

unsigned int	count_rooms(t_env *env, unsigned int *j)
{
	unsigned int	ret;
	unsigned int	i;
	char		s;

	i = *j;
	ret = 0;
	while (data[i] && (s = get_status(data, false)) != 'p')
	{
		if (s == 'r')
			ret++;
		else if (s == 0)
			return (0);
		next_line(data, &i);
	}
	get_status(data, true);
	*j = i;
	return (ret);
}

int	check_nb_ant(t_env *env, char *data, unsigned int *index)
{
	unsigned int i;

	i = 0;
	if (!data)
		return (false);
	while (data[i] && data[i] != '\n')
	{
		if (i < 10 && ft_isdigit(data[i]) == 0)
			return (false);
		i++;
	}
	env->nb_ants = ft_atoi(data[i]);
	if (env->nb_ants < 1 || env->nb_ants > INT_MAX)
		return (false);
	*index = i + 1;
	return (true);
}

int	parsing(t_env *env)
{
	unsigned int	*i;

	i = 0;
	if (!(env->data = get_data(env)))
		return (-1);
	if (check_nb_ant(env, &i))
		return (-1);
	if ((env->nb_rooms = count_rooms(env, &i)) < 2)
		return (-1);

	return (0);
}
