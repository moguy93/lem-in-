/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gedemais <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/05/20 18:43:03 by gedemais          #+#    #+#             */
/*   Updated: 2019/09/19 04:14:55 by gedemais         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/main.h"

int		ft_set_env(t_mlx *env)
{
	srand(time(0));
	env->room_size = 25;
	env->nb_pipes = 1;
	env->speed = 1;
	if (!(env->mlx_ptr = mlx_init()))
		return (-1);
	if (!(env->mlx_win = mlx_new_window(env->mlx_ptr, WDT, HGT,
		"Lem_in visualiser")))
		return (-1);
	if (!(env->img_ptr = mlx_new_image(env->mlx_ptr, WDT, HGT)))
		return (-1);
	if (!(env->img_data = mlx_get_data_addr(env->img_ptr, &env->bpp,
					&env->s_l, &env->endian)))
		return (-1);
	return (0);
}

int		toultemps(void *param)
{
	t_mlx			*env;
	static int		step = -1;
	char			**line;
	int				i;

	i = -1;
	env = ((t_mlx*)param);
	if (step == -1 || arrived(env))
	{
		step++;
		if (!env->moves[step])
			exit(EXIT_SUCCESS);
		if (!(line = ft_strsplit(env->moves[step], " ")))
			return (1);
		while (line[++i])
			env->ants = handle_move(env, line[i]);
	}
	i = -1;
	while (++i < (int)env->nb_ants)
		if (fabs(env->ants[i].pos.x - env->ants[i].goal.x) > 1
			|| fabs(env->ants[i].pos.y - env->ants[i].goal.y) > 1)
			cross_ant(env, env->ants[i].goal.x, env->ants[i].goal.y, i);
	render(env);
	return (0);
}

int		visualiser(void)
{
	t_mlx			env;
	int				i;

	i = 0;
	if (ft_set_env(&env) == -1)
		return (-1);
	if (!(env.input = read_fd_zero(&env.file_size))
		|| ((env.nb_ants = (unsigned int)ft_atoi(env.input)) == 0)
		|| !(env.graph = make_graph(&env, &i))
		|| !(env.pipes = make_pipes(&env, &i))
		|| !(env.ants = make_ants(&env)))
		return (-1);
	i = 0;
	while (env.input[i] && !(env.input[i] == 'L' && env.input[i - 1] == '\n'))
		i++;
	if (!(env.moves = ft_strsplit(&env.input[i], "\n")))
		return (-1);
	mlx_loop_hook(env.mlx_ptr, &toultemps, &env);
	mlx_hook(env.mlx_win, KEY_PRESS, KEY_PRESS_MASK, deal_key, &env);
	mlx_hook(env.mlx_win, 17, (1L << 17), ft_exit, &env);
	mlx_loop(env.mlx_ptr);
	return (0);
}

int		main(void)
{
	if (visualiser() == -1)
	{
		ft_putstr_fd("Error\n", 2);
		return (1);
	}
	return (0);
}
