/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   load_line.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gedemais <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/09/10 01:37:24 by gedemais          #+#    #+#             */
/*   Updated: 2019/10/01 14:37:09 by gedemais         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "main.h"

static inline int		walk_space(char *line, unsigned int *i, unsigned int j)
{
	while (ft_is_whitespace(line[(*i)]) && (*i) >= j)
		(*i)--;
	return (0);
}

static inline int		walk_digits(char *line, unsigned int *i, unsigned int j)
{
	unsigned int	mem;

	mem = *i;
	while (ft_isdigit(line[(*i)]) && (*i) >= j)
	{
		(*i)--;
		if (mem - *i > 10)
			return (1);
	}
	return (0);
}

static inline t_env		*load_room(t_env *env, unsigned int j, int room, char s)
{
	unsigned int	i;
	long long int	nb;

	i = j;
	env->graph[room].type = s;
	while (env->file[i] && env->file[i] != '\n')
		i++;
	i--;
	if (walk_space(env->file, &i, j) || i == j || ft_isdigit(env->file[i]) == 0)
		return (NULL);
	if (walk_digits(env->file, &i, j) || i == j
		|| ft_is_whitespace(env->file[i]) == 0)
		return (NULL);
	nb = ft_atoi(&env->file[i]);
	if (walk_space(env->file, &i, j) || i == j
		|| ft_isdigit(env->file[i]) == 0 || nb < 0 || nb > INT_MAX)
		return (NULL);
	if (walk_digits(env->file, &i, j) || i == j
		|| ft_is_whitespace(env->file[i]) == 0)
		return (NULL);
	nb = ft_atoi(&env->file[i]);
	if (walk_space(env->file, &i, j) || i < j || nb < 0 || nb > INT_MAX ||
		!(env->graph[room].name = ft_strndup(&env->file[j], (int)(i - j + 1))))
		return (NULL);
	return (env);
}

int						load_line(t_env *env, char s, unsigned int i, int r)
{
	static bool	pipe = false;
	static bool	start = false;
	static bool	end = false;

	if (s == 'c')
		return (0);
	else if (s == 's')
		start = true;
	else if (s == 'e')
		end = true;
	else if (s == 'p')
		pipe = true;
	else if (!pipe && s == 'r')
	{
		if (start && (s = 's'))
			start = false;
		if (end && (s = 'e'))
			end = false;
		if (!(env = load_room(env, i, r, s)))
			return (1);
	}
	else
		return (-1);
	return (0);
}
