/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   make_matrix.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gedemais <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/09/18 23:05:52 by gedemais          #+#    #+#             */
/*   Updated: 2019/10/03 16:40:31 by gedemais         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "main.h"

static inline char	**clear_matrix(char **matrix, unsigned int n)
{
	unsigned int	i;

	i = 0;
	while (i < n)
	{
		ft_memset(matrix[i], 0, sizeof(char) * n);
		i++;
	}
	return (matrix);
}

static inline char	**allocate_matrix(char **matrix, unsigned int n)
{
	unsigned int	i;

	i = 0;
	if (!(matrix = (char**)malloc(sizeof(char*) * (n + 1))))
		return (NULL);
	while (i < n)
	{
		if (!(matrix[i] = (char*)malloc(sizeof(char) * (n + 1))))
			return (NULL);
		ft_memset(matrix[i], 0, sizeof(char) * n);
		i++;
	}
	return (matrix);
}

static inline int	write_pipe(t_env *env, char *line)
{
	int				from;
	int				to;

	if ((from = find_from(env, line)) == -1
		|| (to = find_to(env, line)) == -1)
		return (-1);
	if (from == to)
		return (-1);
	env->matrix[from][to] = 1;
	env->matrix[to][from] = 1;
	return (0);
}

int					make_matrix(t_env *env, unsigned int i)
{
	char	s;

	env->pipes_start = i;
	if (!env->matrix
		&& !(env->matrix = allocate_matrix(env->matrix, env->nb_rooms)))
		return (-1);
	else
		env->matrix = clear_matrix(env->matrix, env->nb_rooms);
	while (env->file[i] && (s = get_line_state(&env->file[i], false)))
	{
		if (s == 'p')
		{
			if (write_pipe(env, &env->file[i]) == -1)
				return (-1);
		}
		else if (s != 'm' && s != 'c')
			return (-1);
		next_line(env->file, &i);
	}
	return (0);
}
