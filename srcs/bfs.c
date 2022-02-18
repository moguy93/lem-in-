/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   bfs.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gedemais <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/08/17 01:19:43 by gedemais          #+#    #+#             */
/*   Updated: 2019/09/18 05:02:26 by gedemais         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "main.h"

bool				breadth_first_search(t_env *env, int s, int e, bool up)
{
	t_queue		*queue;
	int			u;
	int			v;

	if (!(queue = lm_lstnew(s)))
		return (false);
	env->visited[s] = true;
	while (queue)
	{
		u = (int)queue->index;
		lm_lst_pop(&queue);
		v = up ? -1 : (int)env->nb_rooms;
		while ((up && ++v < (int)env->nb_rooms) || (!up && --v >= 0))
			if (env->visited[v] == false && env->matrix[u][v] > 0)
			{
				if (lm_lst_push(&queue, v) != 0)
					return (false);
				env->parent[v] = u;
				env->visited[v] = true;
				if (v == e && lm_lstdel(queue) == 0)
					return (true);
			}
	}
	lm_lstdel(queue);
	return (false);
}
