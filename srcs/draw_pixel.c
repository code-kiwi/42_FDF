/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw_pixel.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mhotting <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/13 17:12:04 by mhotting          #+#    #+#             */
/*   Updated: 2024/03/21 11:00:08 by mhotting         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

void	draw_pixel(t_image *img, t_point2d *pt)
{
	char	*dest;
	int		bpp;
	int		line_len;
	int		img_x;
	int		img_y;

	if (
		img == NULL || img->ptr == NULL
		|| img->addr == NULL || pt == NULL
		|| pt->coords.x <= -IMG_WIDTH / 2 || pt->coords.x >= IMG_WIDTH / 2
		|| pt->coords.y <= -IMG_HEIGHT / 2 || pt->coords.y >= IMG_HEIGHT / 2
	)
		return ;
	img_x = pt->coords.x + IMG_WIDTH / 2;
	img_y = -pt->coords.y + IMG_HEIGHT / 2;
	bpp = img->bpp;
	line_len = img->line_len;
	dest = img->addr + (img_y * line_len + img_x * bpp / 8);
	*(unsigned int *) dest = pt->color.value;
}
