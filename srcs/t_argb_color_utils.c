/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   t_argb_color_utils.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mhotting <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/14 14:19:39 by mhotting          #+#    #+#             */
/*   Updated: 2024/04/11 11:03:11 by mhotting         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

/*
 *	Returns a RGB color value which is a gradient of color between
 *	col_a and col_b
 *	The gradient is calculated on each RGB component
 *	The gradient is calculatede thanks to num / den
 *	Integer numbers are used in order to avoid floating point numbers
 *	calculations
 *	NB: due to integer lack of precision, gieven den could be zero, that's why
 *	in this case, den is forced to be one
 */
int	get_color_value(t_argb_color *col_a, t_argb_color *col_b, int num, int den)
{
	t_argb_color	res;
	int				delta;

	if (col_a == NULL || col_b == NULL)
		return (0xFFFFFF);
	if (col_a->value == col_b->value)
		return (col_a->value);
	if (den == 0)
		den = 1;
	delta = (int)(col_a->components[0]) - (int)(col_b->components[0]);
	res.components[0] = col_a->components[0] - (delta * num / den);
	delta = col_a->components[1] - col_b->components[1];
	res.components[1] = col_a->components[1] - (delta * num / den);
	delta = col_a->components[2] - col_b->components[2];
	res.components[2] = col_a->components[2] - (delta * num / den);
	return (res.value);
}
