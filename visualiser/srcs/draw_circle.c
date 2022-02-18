/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw_circle.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gedemais <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/09/09 07:35:44 by gedemais          #+#    #+#             */
/*   Updated: 2019/09/09 07:44:11 by gedemais         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/main.h"

void		draw_circle(t_mlx *env, t_point point, float radius, int color)
{
	unsigned int	i;
	unsigned int	j;
	float			dx;
	float			dy;

	i = point.x - radius;
	while (i < point.x + radius)
	{
		j = point.y - radius;
		while (j < point.y + radius)
		{
			dx = (float)(i - point.x);
			dy = (float)(j - point.y);
			if (sqrt((dx * dx) + (dy * dy)) <= radius)
				ft_fill_pixel(env->img_data, i, j, color);
			j++;
		}
		i++;
	}
}
