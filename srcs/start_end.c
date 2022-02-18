/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   start_end.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gedemais <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/09/26 20:00:14 by gedemais          #+#    #+#             */
/*   Updated: 2019/09/26 20:10:17 by gedemais         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "main.h"

int		start_end(t_env *env)
{
	char			*tmp;
	int				i;

	i = 1;
	env->file[env->file_len] = '\n';
	write(1, env->file, (size_t)(env->file_len + 1));
	while (i <= env->nb_ants)
	{
		if (!(tmp = ft_itoa(i)))
			return (-1);
		ft_putchar('L');
		ft_putstr(tmp);
		ft_putchar('-');
		ft_putstr(env->graph[env->end].name);
		if (i + 1 <= env->nb_ants)
			ft_putchar(' ');
		free(tmp);
		i++;
	}
	ft_putchar('\n');
	free_env(env);
	return (0);
}
