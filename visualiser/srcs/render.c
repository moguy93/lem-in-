/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   render.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gedemais <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/09/09 07:36:27 by gedemais          #+#    #+#             */
/*   Updated: 2019/09/10 07:39:46 by gedemais         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/main.h"

void			background(t_mlx *env)
{
	unsigned int	i;
	unsigned int	j;

	i = 0;
	while (i < HGT)
	{
		j = 0;
		while (j < WDT)
		{
			ft_fill_pixel(env->img_data, j, i, 0x441100);
			j++;
		}
		i++;
	}
}

void			draw_rooms(t_mlx *env)
{
	t_point			pos;
	unsigned int	i;
	float			center;
	int				color;

	i = 0;
	center = env->room_size - (env->room_size / 8);
	while (env->graph[i].name)
	{
		pos.x = env->graph[i].x;
		pos.y = env->graph[i].y;
		draw_circle(env, pos, env->room_size, (env->graph[i].type == 'e')
				? 0x00cc00 : 0xffffff);
		color = (env->graph[i].type == 's') ? 0x5962ca : 0xc8c800;
		color = (env->graph[i].type == 'e') ? 0x00cc00 : color;
		draw_circle(env, pos, center, color);
		i++;
	}
}

void			draw_ants(t_mlx *env)
{
	unsigned int	i;

	i = 0;
	while (i < env->nb_ants)
	{
		draw_circle(env, env->ants[i].pos, 10, (i % 2 == 0)
				? 0x0000ff : 0x00ff00);
		i++;
	}
}

int				render(t_mlx *env)
{
	background(env);
	draw_pipes(env);
	draw_rooms(env);
	draw_ants(env);
	mlx_put_image_to_window(env, env->mlx_win, env->img_ptr, 0, 0);
	hud(env);
	return (0);
}
