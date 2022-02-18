/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   make_graph.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gedemais <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/09/09 07:36:02 by gedemais          #+#    #+#             */
/*   Updated: 2019/09/14 01:19:34 by gedemais         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/main.h"

char					get_line_state(char *line, bool flush)
{
	static bool	pipe = false;

	if (flush)
		pipe = false;
	if (!pipe)
	{
		if (ft_strncmp(line, "##start\n", 8) == 0)
			return ('s');
		else if (ft_strncmp(line, "##end\n", 6) == 0)
			return ('e');
		else if (is_room(line))
			return ('r');
	}
	if (is_pipe(line))
	{
		pipe = true;
		return ('p');
	}
	else if (is_comment(line))
		return ('c');
	return (0);
}

void					next_line(char *file, unsigned int *i)
{
	unsigned int	j;

	j = *i;
	while (file[j] && file[j] != '\n')
		j++;
	*i = j + 1;
}

static inline t_room	*rectify_positions(t_room *graph)
{
	unsigned int	i;
	bool			do_it;

	i = 0;
	while (graph[i].name)
	{
		if (graph[i].x == 0 || graph[i].y == 0)
		{
			do_it = true;
			break ;
		}
		i++;
	}
	if (do_it)
	{
		i = 0;
		while (graph[i].name)
		{
			graph[i].x++;
			graph[i].y++;
			i++;
		}
	}
	return (graph);
}

static inline t_room	*scale_rooms(t_room *graph)
{
	unsigned int	i;
	float			delta[2];
	int				maxs[2];
	int				mins[2];

	i = -1;
	ft_memset(&maxs[0], INT_MIN, sizeof(int) * 2);
	ft_memset(&mins[0], INT_MAX, sizeof(int) * 2);
	graph = rectify_positions(graph);
	while (graph[++i].name)
	{
		maxs[0] = (maxs[0] < graph[i].x) ? graph[i].x : maxs[0];
		maxs[1] = (maxs[1] < graph[i].y) ? graph[i].y : maxs[1];
		mins[0] = (mins[0] > graph[i].x) ? graph[i].x : mins[0];
		mins[1] = (mins[1] > graph[i].y) ? graph[i].y : mins[1];
	}
	delta[0] = (WDT / (maxs[0] - mins[0]));
	delta[1] = (HGT / (maxs[1] - mins[1]));
	i = -1;
	while (graph[++i].name)
	{
		graph[i].x *= delta[0];
		graph[i].y *= delta[1];
	}
	return (graph);
}

t_room					*make_graph(t_mlx *env, int *j)
{
	unsigned int	i;
	int				room;
	char			s;

	i = 0;
	room = 0;
	next_line(env->input, &i);
	env->nb_rooms = count_rooms(env->input, &i);
	i = 0;
	next_line(env->input, &i);
	if (!(env->graph = (t_room*)malloc(sizeof(t_room) * (env->nb_rooms + 1))))
		return (NULL);
	env->graph = ft_memset(env->graph, 0, sizeof(t_room) * (env->nb_rooms + 1));
	while (env->input[i] && (s = get_line_state(&env->input[i], false))
		&& room < (int)env->nb_rooms && s != 'p')
	{
		if (load_line(env, s, i, room))
			return (env->graph);
		room += (s == 'r') ? 1 : 0;
		next_line(env->input, &i);
	}
	*j = i;
	return (scale_rooms(env->graph));
}
