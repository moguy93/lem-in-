/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   deal_key.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gedemais <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/09/09 07:35:36 by gedemais          #+#    #+#             */
/*   Updated: 2019/09/15 05:35:54 by gedemais         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/main.h"

void		hud(t_mlx *env)
{
	char		speed[10];

	sprintf(&speed[0], "%.2f\n", env->speed);
	mlx_string_put(env->mlx_ptr, env->mlx_win, 10, 50, 0xFFFFFF, "Speed :");
	mlx_string_put(env->mlx_ptr, env->mlx_win, 100, 50, 0xFFFFFF, &speed[0]);
}

int			deal_key(int key, void *param)
{
	if (key == 69 && ((t_mlx*)param)->speed < 4.99)
		((t_mlx*)param)->speed += 0.01;
	else if (key == 78 && ((t_mlx*)param)->speed > 0.06)
		((t_mlx*)param)->speed -= 0.01;
	else if (key == 53)
		ft_exit();
	return (0);
}
