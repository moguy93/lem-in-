/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   load_line.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gedemais <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/09/09 07:35:51 by gedemais          #+#    #+#             */
/*   Updated: 2019/09/19 04:15:05 by gedemais         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/main.h"

static inline int		walk_space(char *line, unsigned int *i, unsigned int j)
{
	while (ft_is_whitespace(line[(*i)]) && (*i) >= j)
		(*i)--;
	return (0);
}

static inline int		walk_digits(char *line, unsigned int *i, unsigned int j)
{
	while (ft_isdigit(line[(*i)]) && (*i) >= j)
		(*i)--;
	return (0);
}

static inline t_mlx		*load_room(t_mlx *e, unsigned int j, int room, char s)
{
	unsigned int	i;

	i = j;
	e->graph[room].type = s;
	while (e->input[i] && e->input[i] != '\n')
		i++;
	i--;
	if (walk_space(e->input, &i, j) || i == j || ft_isdigit(e->input[i]) == 0)
		return (NULL);
	if (walk_digits(e->input, &i, j) || i == j
		|| ft_is_whitespace(e->input[i]) == 0)
		return (NULL);
	e->graph[room].y = (int)ft_atoi(&e->input[i]);
	if (walk_space(e->input, &i, j) || i == j || ft_isdigit(e->input[i]) == 0)
		return (NULL);
	if (walk_digits(e->input, &i, j) || i == j
		|| ft_is_whitespace(e->input[i]) == 0)
		return (NULL);
	e->graph[room].x = (int)ft_atoi(&e->input[i]);
	if (walk_space(e->input, &i, j) || i < j ||
		!(e->graph[room].name = ft_strndup(&e->input[j], (int)(i - j + 1))))
		return (NULL);
	return (e);
}

int						load_line(t_mlx *env, char s, unsigned int i, int room)
{
	static bool	pipe = false;
	static bool	start = false;
	static bool	end = false;

	if (s == 's')
		start = true;
	if (s == 'e')
		end = true;
	if (s == 'p')
		pipe = true;
	if (!pipe && s == 'r')
	{
		if (start && (s = 's'))
			start = false;
		if (end && (s = 'e'))
			end = false;
		if (!(env = load_room(env, i, room, s)))
			return (1);
	}
	return (0);
}
