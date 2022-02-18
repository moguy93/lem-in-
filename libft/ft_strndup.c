/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strndup.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gedemais <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/12/13 12:51:50 by gedemais          #+#    #+#             */
/*   Updated: 2019/09/21 17:14:53 by gedemais         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strndup(char *str, int size)
{
	char			*dest;
	unsigned int	i;

	i = 0;
	while (str[i] && (int)i < size)
		i++;
	if (!(dest = (char*)malloc(sizeof(char) * (i + 1))))
		return (NULL);
	i = 0;
	while (str[i] && (int)i < size)
	{
		dest[i] = str[i];
		i++;
	}
	dest[i] = '\0';
	return (dest);
}
