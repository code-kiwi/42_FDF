/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw_line.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mhotting <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/13 16:55:14 by mhotting          #+#    #+#             */
/*   Updated: 2024/03/15 14:41:09 by mhotting         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

static void	draw_line_low_init(t_vector2 *a, t_vector2 *b, int dxy[2], int *yi)
{
	if (a == NULL || b == NULL || dxy == NULL || yi == NULL)
		return ;
	dxy[0] = b->x - a->x;
	dxy[1] = b->y - a->y;
	*yi = 1;
	if (dxy[1] < 0)
	{
		*yi = -1;
		dxy[1] = -dxy[1];
	}
}

static void	draw_line_low(t_image *img, t_vector2 *a, t_vector2 *b)
{
	t_vector2	pt;
	int			dxy[2];
	int			yi;
	int			d;

	draw_line_low_init(a, b, dxy, &yi);
	pt.x = a->x;
	pt.y = a->y;
	pt.color.value = a->color.value;
	d = 2 * dxy[1] - dxy[0];
	while (pt.x <= b->x)
	{
		pt.color.value = get_color_value(\
				&(a->color), &(b->color), (pt.x - a->x), dxy[0]);
		draw_pixel(img, &pt);
		if (d > 0)
		{
			pt.y = pt.y + yi;
			d = d + (2 * (dxy[1] - dxy[0]));
		}
		else
			d = d + 2 * dxy[1];
		pt.x += 1;
	}
}

static void	draw_line_high_init(t_vector2 *a, t_vector2 *b, int dxy[2], int *xi)
{
	if (a == NULL || b == NULL || dxy == NULL || xi == NULL)
		return ;
	dxy[0] = b->x - a->x;
	dxy[1] = b->y - a->y;
	*xi = 1;
	if (dxy[0] < 0)
	{
		*xi = -1;
		dxy[0] = -dxy[0];
	}
}

static void	draw_line_high(t_image *img, t_vector2 *a, t_vector2 *b)
{
	t_vector2	pt;
	int			dxy[2];
	int			xi;
	int			d;

	draw_line_high_init(a, b, dxy, &xi);
	pt.x = a->x;
	pt.y = a->y;
	pt.color.value = a->color.value;
	d = 2 * dxy[0] - dxy[1];
	while (pt.y <= b->y)
	{
		pt.color.value = get_color_value(\
				&a->color, &b->color, (pt.y - a->y), dxy[1]);
		draw_pixel(img, &pt);
		if (d > 0)
		{
			pt.x = pt.x + xi;
			d = d + (2 * (dxy[0] - dxy[1]));
		}
		else
			d = d + 2 * dxy[0];
		pt.y += 1;
	}
}

void	draw_line(t_image *img, t_vector2 *a, t_vector2 *b)
{
	if (img == NULL || a == NULL || b == NULL)
		return ;
	if (abs(b->y - a->y) < abs(b->x - a->x))
	{
		if (a->x < b->x)
			draw_line_low(img, a, b);
		else
			draw_line_low(img, b, a);
	}
	else
	{
		if (a->y < b->y)
			draw_line_high(img, a, b);
		else
			draw_line_high(img, b, a);
	}
}
