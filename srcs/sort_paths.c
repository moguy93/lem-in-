/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sort_paths.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gedemais <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/09/14 01:28:41 by gedemais          #+#    #+#             */
/*   Updated: 2019/09/18 04:25:21 by gedemais         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "main.h"

static inline void	swap_paths(t_path *a, t_path *b)
{
	t_path	tmp;

	tmp.path = a->path;
	a->path = b->path;
	b->path = tmp.path;
	tmp.len = a->len;
	a->len = b->len;
	b->len = tmp.len;
}

static inline bool	spec_cases(t_env *env)
{
	if (env->nb_paths == 1)
		return (true);
	if (env->nb_paths == 2)
	{
		if (env->paths[0].len > env->paths[1].len)
			swap_paths(&env->paths[0], &env->paths[1]);
		return (true);
	}
	return (false);
}

int					sort_paths(t_env *env)
{
	int				i;
	unsigned int	j;
	unsigned int	best;
	unsigned int	b_index;

	i = -1;
	if (spec_cases(env))
		return (0);
	while (++i < (int)env->nb_paths - 1)
	{
		j = (unsigned int)i;
		b_index = j;
		best = env->paths[j].len;
		while (j < env->nb_paths)
		{
			if (best >= env->paths[j].len)
			{
				best = env->paths[j].len;
				b_index = j;
			}
			j++;
		}
		swap_paths(&env->paths[i], &env->paths[b_index]);
	}
	return (0);
}
