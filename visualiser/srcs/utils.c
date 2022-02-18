/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gedemais <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/06/04 18:28:38 by gedemais          #+#    #+#             */
/*   Updated: 2019/09/15 05:35:23 by gedemais         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/main.h"

int				ft_exit(void)
{
	exit(EXIT_SUCCESS);
}

char			*ft_clear_image(void *param, char *img_data)
{
	ft_memset(((t_mlx*)param)->img_data, 0, HGT * WDT * 4);
	mlx_put_image_to_window((t_mlx*)param, ((t_mlx*)param)->mlx_win,
			((t_mlx*)param)->img_ptr, 0, 0);
	return (img_data);
}

int				nb_len(int nb)
{
	int	ret;

	ret = 0;
	while (nb > 10)
	{
		nb = nb / 10;
		ret++;
	}
	return (ret);
}

bool			arrived(t_mlx *env)
{
	unsigned int	i;

	i = 1;
	while (i < env->nb_ants)
	{
		if (fabs(env->ants[i].pos.x - env->ants[i].goal.x) > 1
				|| fabs(env->ants[i].pos.y - env->ants[i].goal.y) > 1)
			return (false);
		i++;
	}
	return (true);
}

unsigned int	find_room(t_mlx *env, char *name)
{
	unsigned int	i;

	i = 0;
	while (env->graph[i].name)
	{
		if (env->graph[i].name[0] == name[0])
			if (ft_strcmp(env->graph[i].name, name) == 0)
				return (i);
		i++;
	}
	return (0);
}
