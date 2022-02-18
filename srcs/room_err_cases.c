/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   room_err_cases.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gedemais <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/09/18 23:20:32 by gedemais          #+#    #+#             */
/*   Updated: 2019/10/01 12:25:08 by gedemais         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "main.h"

static inline bool	check_same_rooms(t_env *env)
{
	unsigned int	i;
	unsigned int	j;

	i = 0;
	while (i < env->nb_rooms)
	{
		j = i + 1;
		while (j < env->nb_rooms)
		{
			if (env->graph[i].name[0] == env->graph[j].name[0])
				if (ft_strcmp(env->graph[i].name, env->graph[j].name) == 0)
					return (true);
			j++;
		}
		i++;
	}
	return (false);
}

bool				room_err_cases(t_env *env)
{
	if (check_same_rooms(env))
		return (true);
	return (false);
}
