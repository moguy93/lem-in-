/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   is_disjoint.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gedemais <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/09/18 22:56:17 by gedemais          #+#    #+#             */
/*   Updated: 2019/09/18 22:56:30 by gedemais         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "main.h"

static inline bool	is_joint(t_path a, t_path b, int end)
{
	unsigned int	i;
	unsigned int	j;

	i = 1;
	while (a.path[i] != end)
	{
		j = 1;
		while (b.path[j] != end)
		{
			if (a.path[i] == b.path[j])
				return (true);
			j++;
		}
		i++;
	}
	return (false);
}

bool				is_disjoint(t_env *env)
{
	unsigned int	i;
	unsigned int	j;

	i = 0;
	while (i < env->nb_paths)
	{
		j = 0;
		while (j < env->nb_paths)
		{
			if (i != j && is_joint(env->paths[i], env->paths[j], (int)env->end))
				return (true);
			j++;
		}
		i++;
	}
	return (false);
}
