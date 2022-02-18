/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   store_paths.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gedemais <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/09/18 23:23:19 by gedemais          #+#    #+#             */
/*   Updated: 2019/09/18 23:25:02 by gedemais         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "main.h"

static inline int	get_path_max(t_env *env)
{
	unsigned int	i;
	int				ret_s;
	int				ret_e;

	i = 0;
	ret_s = 0;
	ret_e = 0;
	while (i < env->nb_rooms)
	{
		if (env->matrix[env->start][i] == 1)
			ret_s++;
		if (env->matrix[env->end][i] == 1)
			ret_e++;
		i++;
	}
	return (ret_s > ret_e ? ret_e : ret_s);
}

t_path				*allocate_paths(t_env *env)
{
	int				path_max;
	unsigned int	i;

	i = 0;
	path_max = get_path_max(env);
	if (!(env->paths = (t_path*)malloc(sizeof(t_path) * (unsigned long)
		(path_max + 1))))
		return (NULL);
	while (i < (unsigned int)path_max)
	{
		if (!(env->paths[i].path = (int*)malloc(sizeof(int)
			* (env->nb_rooms + 1))))
			return (NULL);
		if (!(env->paths[i].ants = (int*)malloc(sizeof(int)
			* (env->nb_rooms + 1))))
			return (NULL);
		env->paths[i].ammos = 0;
		ft_memset(env->paths[i].path, -1, sizeof(int) * env->nb_rooms);
		ft_memset(env->paths[i].ants, -1, sizeof(int) * env->nb_rooms);
		i++;
	}
	env->paths[i].path = NULL;
	return (env->paths);
}
