/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipes.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gedemais <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/09/09 07:36:18 by gedemais          #+#    #+#             */
/*   Updated: 2019/09/10 07:38:12 by gedemais         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/main.h"

static void		draw_line(t_mlx *env, t_point f, t_point s)
{
	t_point	delta;
	t_point	sign;
	t_point	cur;
	int		error[2];

	delta.x = fabs(s.x - f.x);
	delta.y = fabs(s.y - f.y);
	sign.x = f.x < s.x ? 1 : -1;
	sign.y = f.y < s.y ? 1 : -1;
	error[0] = delta.x - delta.y;
	cur = f;
	while (cur.x != s.x || cur.y != s.y)
	{
		ft_fill_pixel(env->img_data, cur.x, cur.y, 0xcccccc);
		if ((error[1] = error[0] * 2) > -delta.y)
		{
			error[0] -= delta.y;
			cur.x += sign.x;
		}
		if (error[1] < delta.x)
		{
			error[0] += delta.x;
			cur.y += sign.y;
		}
	}
}

void			draw_pipe(t_mlx *env, t_point start, t_point end)
{
	unsigned int	i;
	unsigned int	j;
	t_point			s;
	t_point			e;

	s = start;
	e = end;
	i = -1;
	start.x -= 3;
	start.y -= 3;
	end.x -= 3;
	end.y -= 3;
	while (++i < 7)
	{
		j = -1;
		while (++j < 7)
		{
			start.x = s.x + j - 1;
			start.y = s.y + i - 1;
			end.x = e.x + j - 1;
			end.y = e.y + i - 1;
			draw_line(env, start, end);
		}
	}
}

int				draw_pipes(t_mlx *env)
{
	t_point			start;
	t_point			end;
	unsigned int	i;

	i = 0;
	start.x = 0;
	start.y = 0;
	end.x = 100;
	end.y = 200;
	while (i < env->nb_pipes)
	{
		draw_pipe(env, env->pipes[i].start, env->pipes[i].end);
		i++;
	}
	return (0);
}

t_pipe			*write_pipe(t_mlx *env, char *line)
{
	unsigned int	i;
	int				from;
	int				to;

	i = 0;
	from = find_from(env, line);
	to = find_to(env, line);
	env->pipes[env->nb_pipes].start.x = env->graph[from].x;
	env->pipes[env->nb_pipes].start.y = env->graph[from].y;
	env->pipes[env->nb_pipes].end.x = env->graph[to].x;
	env->pipes[env->nb_pipes].end.y = env->graph[to].y;
	return (env->pipes);
}

t_pipe			*make_pipes(t_mlx *env, int *index)
{
	unsigned int	i;
	char			s;

	i = (int)(*index);
	if (!(env->pipes = (t_pipe*)malloc(sizeof(t_pipe) * MAX_PIPES)))
		return (NULL);
	while (env->input[i] && (s = get_line_state(&env->input[i], false)))
	{
		if (env->nb_pipes + 1 == MAX_PIPES)
		{
			ft_putstr_fd("Too many pipes to draw.\n", 2);
			exit(EXIT_FAILURE);
			break ;
		}
		if (s == 'p')
			env->pipes = write_pipe(env, &env->input[i]);
		next_line(env->input, &i);
		env->nb_pipes++;
	}
	return (env->pipes);
}
