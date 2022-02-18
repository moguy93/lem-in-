/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   read_fd_zero.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gedemais <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/07/23 06:33:13 by gedemais          #+#    #+#             */
/*   Updated: 2019/10/01 15:03:33 by gedemais         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "main.h"

static inline char	*strrealloc(char *s, unsigned int size)
{
	char	*new;

	if (!(new = ft_strnew(size)))
	{
		free(s);
		return (NULL);
	}
	new = ft_strcpy(new, s);
	free(s);
	return (new);
}

static inline char	*buffer_join(char *dst, const char *src, unsigned int start)
{
	unsigned int	i;

	i = 0;
	while (src[i])
	{
		dst[i + start] = src[i];
		i++;
	}
	dst[i + start] = '\0';
	return (dst);
}

char				*read_fd_zero(int *len)
{
	char			buff[BUFF_READ + 1];
	char			*dest;
	int				ret;
	unsigned int	size[2];

	size[0] = BUFF_READ;
	size[1] = 0;
	if (!(dest = ft_strnew(BUFF_READ)))
		return (NULL);
	while ((ret = (int)read(0, buff, BUFF_READ)) > 0)
	{
		size[1] += (unsigned int)ret;
		buff[ret] = '\0';
		if (size[1] >= size[0] && (size[0] *= 2) > 0
			&& !(dest = strrealloc(dest, size[0])))
			return (NULL);
		dest = buffer_join(dest, buff, size[1] - (unsigned int)ret);
	}
	if (ret == -1)
	{
		free(dest);
		return (NULL);
	}
	*len = (int)size[1];
	return (dest);
}
