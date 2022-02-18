/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cross_ant.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gedemais <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/09/09 07:35:27 by gedemais          #+#    #+#             */
/*   Updated: 2019/09/09 07:43:16 by gedemais         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/main.h"

t_ant		*handle_move(t_mlx *env, char *line)
{
	unsigned int	ant;
	unsigned int	goal;

	ant = (unsigned int)ft_atoi(&line[1]);
	goal = find_room(env, &line[3 + nb_len(ant)]);
	env->ants[ant].goal.x = env->graph[goal].x;
	env->ants[ant].goal.y = env->graph[goal].y;
	env->ants[ant].id = ant;
	env->ants[ant].speed = 10;
	return (env->ants);
}

t_ant		*make_ants(t_mlx *env)
{
	unsigned int	i;
	unsigned int	start;

	i = 0;
	start = 0;
	if (!(env->ants = (t_ant*)malloc(sizeof(t_ant) * env->nb_ants)))
		return (NULL);
	while (start < env->nb_ants && env->graph[start].type != 's')
		start++;
	while (i < env->nb_ants)
	{
		env->ants[i].id = i;
		env->ants[i].pos.x = env->graph[start].x;
		env->ants[i].pos.y = env->graph[start].y;
		env->ants[i].goal = env->ants[i].pos;
		i++;
	}
	return (env->ants);
}

int			cross_ant(t_mlx *env, float x, float y, unsigned int ant)
{
	float			v[2];
	float			dist;

	env->ants[ant].goal.x = x;
	env->ants[ant].goal.y = y;
	v[0] = x - env->ants[ant].pos.x;
	v[1] = y - env->ants[ant].pos.y;
	dist = sqrt((v[0] * v[0]) + (v[1] * v[1]));
	v[0] /= dist;
	v[1] /= dist;
	env->ants[ant].pos.x += (v[0] * env->ants[ant].speed * (dist *
		(env->speed / 100)));
	env->ants[ant].pos.y += (v[1] * env->ants[ant].speed * (dist *
		(env->speed / 100)));
	return (0);
}
