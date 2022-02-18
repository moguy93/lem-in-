/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gedemais <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/09/18 23:19:27 by gedemais          #+#    #+#             */
/*   Updated: 2019/10/02 19:42:44 by demaisonc        ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "main.h"

static inline bool	check_nb_ant(t_env *env, char *file, unsigned int *index)
{
	unsigned int	i;

	i = 0;
	if (file[0] == '\0')
		return (true);
	while (file[i] && file[i] != '\n')
	{
		if (ft_isdigit(file[i]) == 0)
			return (true);
		i++;
	}
	env->nb_ants = ft_atoi(file);
	if (i > 10 || env->nb_ants <= 0 || env->nb_ants > INT_MAX)
		return (true);
	*index = i + 1;
	return (false);
}

static inline bool	find_start_end(t_env *env)
{
	int	i;

	i = -1;
	env->start = -1;
	env->end = -1;
	while (++i < (int)env->nb_rooms)
		if (env->graph[i].type == 's')
		{
			if (env->start != -1)
				return (true);
			env->start = (int)i;
		}
		else if (env->graph[i].type == 'e')
		{
			if (env->end != -1)
				return (true);
			env->end = (int)i;
		}
	if (env->start == -1 || env->end == -1)
		return (true);
	return (false);
}

t_room				*parsing(t_env *env)
{
	unsigned int	i;

	i = 0;
	if (!env->file || check_nb_ant(env, env->file, &i))
		return (NULL);
	if ((env->nb_rooms = count_rooms(env->file, &i)) < 2)
		return (NULL);
	if (!(env->graph = make_graph(env))
		|| find_start_end(env)
		|| make_matrix(env, i) == -1
		|| room_err_cases(env))
	{
		env->graph = free_graph(env);
		return (NULL);
	}
	return (env->graph);
}
