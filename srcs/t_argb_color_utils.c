/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   t_argb_color_utils.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mhotting <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/14 14:19:39 by mhotting          #+#    #+#             */
/*   Updated: 2024/03/15 14:35:39 by mhotting         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

int	get_color_value(t_argb_color *col_a, t_argb_color *col_b, int num, int den)
{
	t_argb_color	res;
	int				delta;

	if (col_a == NULL || col_b == NULL)
		return (0xFFFFFF);
	if (col_a->value == col_b->value)
		return (col_a->value);
	delta = (int)(col_a->components[0]) - (int)(col_b->components[0]);
	res.components[0] = col_a->components[0] - (delta * num / den);
	delta = col_a->components[1] - col_b->components[1];
	res.components[1] = col_a->components[1] - (delta * num / den);
	delta = col_a->components[2] - col_b->components[2];
	res.components[2] = col_a->components[2] - (delta * num / den);
	return (res.value);
}
