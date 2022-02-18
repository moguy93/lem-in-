/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gedemais <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/09/18 22:55:02 by gedemais          #+#    #+#             */
/*   Updated: 2019/10/01 18:22:37 by gedemais         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "main.h"

t_room					*free_graph(t_env *env)
{
	unsigned int	i;

	i = 0;
	while (i < env->nb_rooms)
	{
		if (env->graph[i].name)
			free(env->graph[i].name);
		i++;
	}
	free(env->graph);
	env->graph = NULL;
	return (env->graph);
}

char					**free_matrix(char **matrix, unsigned int n)
{
	unsigned int	i;

	i = 0;
	while (i < n)
	{
		free(matrix[i]);
		i++;
	}
	free(matrix);
	matrix = NULL;
	return (NULL);
}

static inline t_path	*free_paths(t_path *paths)
{
	unsigned int	i;

	i = 0;
	while (paths[i].path)
	{
		free(paths[i].path);
		free(paths[i].ants);
		i++;
	}
	free(paths);
	return (paths);
}

t_env					*free_env(t_env *env)
{
	if (env->graph)
		env->graph = free_graph(env);
	if (env->file)
		free(env->file);
	if (env->matrix)
		env->matrix = free_matrix(env->matrix, env->nb_rooms);
	if (env->paths)
		env->paths = free_paths(env->paths);
	if (env->visited)
		free(env->visited);
	if (env->arriveds)
		free(env->arriveds);
	if (env->parent)
		free(env->parent);
	return (env);
}
