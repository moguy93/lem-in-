/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mlx_fts_1.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gedemais <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/01/09 14:44:56 by gedemais          #+#    #+#             */
/*   Updated: 2019/06/08 15:51:46 by gedemais         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/main.h"

void	ft_fill_pixel(char *img_str, int x, int y, int color)
{
	int		pos;

	if (x >= WDT || x < 0 || y >= HGT || y < 0)
		return ;
	pos = ((y - 1) * WDT + x) * 4;
	img_str[pos] = color >> 16 & 255;
	img_str[pos + 1] = color >> 8 & 255;
	img_str[pos + 2] = color & 255;
}
