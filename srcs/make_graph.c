/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   make_graph.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gedemais <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/09/18 23:03:41 by gedemais          #+#    #+#             */
/*   Updated: 2019/10/01 14:51:26 by gedemais         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "main.h"

char					get_line_state(char *line, bool flush)
{
	static bool	pipe = false;

	if (flush)
	{
		pipe = false;
		return (0);
	}
	if (!pipe)
	{
		if (is_cmd(line))
			if (ft_strncmp(line, START_CMD, 8) == 0)
				return ('s');
			else if (ft_strncmp(line, END_CMD, 6) == 0)
				return ('e');
			else
				return ('m');
		else if (is_room(line))
			return ('r');
	}
	if (is_pipe(line) && (pipe = true))
		return ('p');
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

static inline t_room	*check_reverse(t_room *graph)
{
	t_room			tmp;
	unsigned int	i;
	unsigned int	j;

	i = 0;
	j = 0;
	while (graph[i].name && graph[i].type != 's')
		i++;
	while (graph[j].name && graph[j].type != 'e')
		j++;
	if (i > j)
	{
		tmp = graph[i];
		graph[i] = graph[j];
		graph[j] = tmp;
	}
	return (graph);
}

t_room					*make_graph(t_env *env)
{
	unsigned int	i;
	int				room;
	char			s;
	int				ret;

	i = 0;
	room = 0;
	next_line(env->file, &i);
	if (!(env->graph = (t_room*)malloc(sizeof(t_room) * (env->nb_rooms + 1))))
		return (NULL);
	ft_memset(env->graph, 0, sizeof(t_room) * (env->nb_rooms + 1));
	while (env->file[i] && (s = get_line_state(&env->file[i], false))
		&& room < (int)env->nb_rooms && s != 'p')
	{
		if ((ret = load_line(env, s, i, room)) != 0)
			return (ret == 1 ? free_graph(env) : env->graph);
		room += (s == 'r') ? 1 : 0;
		next_line(env->file, &i);
	}
	return (check_reverse(env->graph));
}
