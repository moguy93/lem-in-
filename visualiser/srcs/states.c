/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   states.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gedemais <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/09/09 07:36:32 by gedemais          #+#    #+#             */
/*   Updated: 2019/09/10 07:40:49 by gedemais         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/main.h"

static inline bool	is_coords(char *line, unsigned int *j)
{
	unsigned int	i;

	i = *j;
	while (ft_is_whitespace(line[i]) && i > 0)
		i--;
	if (i == 0 || ft_isdigit(line[i]) == 0)
		return (false);
	while (ft_isdigit(line[i]) && i > 0)
		i--;
	if (i == 0 || ft_is_whitespace(line[i]) == 0)
		return (false);
	while (ft_is_whitespace(line[i]) && i > 0)
		i--;
	if (i == 0 || ft_isdigit(line[i]) == 0)
		return (false);
	while (ft_isdigit(line[i]) && i > 0)
		i--;
	if (i == 0 || ft_is_whitespace(line[i]) == 0)
		return (false);
	i = *j;
	return (true);
}

bool				is_room(char *line)
{
	unsigned int	i;

	i = 0;
	while (line[i] && line[i] != '\n')
		i++;
	if (i < 5)
		return (false);
	i--;
	if (!is_coords(line, &i))
		return (false);
	if (line[0] == '#' || line[0] == 'L')
		return (false);
	return (true);
}

bool				is_pipe(char *line)
{
	unsigned int	i;
	unsigned int	dash;

	i = 0;
	dash = 0;
	while (line[i] && line[i] != '\n')
	{
		if (line[i] == '-')
		{
			if (i == 0 || line[i + 1] == 0 || line[i + 1] == '\n')
				return (false);
			dash++;
		}
		i++;
	}
	if (dash != 1 || i < 3)
		return (false);
	return (true);
}

bool				is_comment(char *line)
{
	if (line[0] == '#')
		return (true);
	return (false);
}
