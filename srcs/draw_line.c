/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw_line.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mhotting <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/13 16:55:14 by mhotting          #+#    #+#             */
/*   Updated: 2024/03/21 11:03:32 by mhotting         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

static void	draw_line_low_init(t_point2d *a, t_point2d *b, int dxy[2], int *yi)
{
	if (a == NULL || b == NULL || dxy == NULL || yi == NULL)
		return ;
	dxy[0] = b->coords.x - a->coords.x;
	dxy[1] = b->coords.y - a->coords.y;
	*yi = 1;
	if (dxy[1] < 0)
	{
		*yi = -1;
		dxy[1] = -dxy[1];
	}
}

static void	draw_line_low(t_image *img, t_point2d *a, t_point2d *b)
{
	t_point2d	pt;
	int			dxy[2];
	int			yi;
	int			d;

	draw_line_low_init(a, b, dxy, &yi);
	pt.coords.x = a->coords.x;
	pt.coords.y = a->coords.y;
	pt.color.value = a->color.value;
	d = 2 * dxy[1] - dxy[0];
	while (pt.coords.x <= b->coords.x)
	{
		pt.color.value = get_color_value(\
				&(a->color), &(b->color), (pt.coords.x - a->coords.x), dxy[0]);
		draw_pixel(img, &pt);
		if (d > 0)
		{
			pt.coords.y = pt.coords.y + yi;
			d = d + (2 * (dxy[1] - dxy[0]));
		}
		else
			d = d + 2 * dxy[1];
		pt.coords.x += 1;
	}
}

static void	draw_line_high_init(t_point2d *a, t_point2d *b, int dxy[2], int *xi)
{
	if (a == NULL || b == NULL || dxy == NULL || xi == NULL)
		return ;
	dxy[0] = b->coords.x - a->coords.x;
	dxy[1] = b->coords.y - a->coords.y;
	*xi = 1;
	if (dxy[0] < 0)
	{
		*xi = -1;
		dxy[0] = -dxy[0];
	}
}

static void	draw_line_high(t_image *img, t_point2d *a, t_point2d *b)
{
	t_point2d	pt;
	int			dxy[2];
	int			xi;
	int			d;

	draw_line_high_init(a, b, dxy, &xi);
	pt.coords.x = a->coords.x;
	pt.coords.y = a->coords.y;
	pt.color.value = a->color.value;
	d = 2 * dxy[0] - dxy[1];
	while (pt.coords.y <= b->coords.y)
	{
		pt.color.value = get_color_value(\
				&a->color, &b->color, (pt.coords.y - a->coords.y), dxy[1]);
		draw_pixel(img, &pt);
		if (d > 0)
		{
			pt.coords.x = pt.coords.x + xi;
			d = d + (2 * (dxy[0] - dxy[1]));
		}
		else
			d = d + 2 * dxy[0];
		pt.coords.y += 1;
	}
}

void	draw_line(t_image *img, t_point2d *a, t_point2d *b)
{
	if (img == NULL || a == NULL || b == NULL)
		return ;
	if (abs(b->coords.y - a->coords.y) < abs(b->coords.x - a->coords.x))
	{
		if (a->coords.x < b->coords.x)
			draw_line_low(img, a, b);
		else
			draw_line_low(img, b, a);
	}
	else
	{
		if (a->coords.y < b->coords.y)
			draw_line_high(img, a, b);
		else
			draw_line_high(img, b, a);
	}
}
