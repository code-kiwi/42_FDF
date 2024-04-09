/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rotation2.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mhotting <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/04 15:10:19 by mhotting          #+#    #+#             */
/*   Updated: 2024/04/09 21:14:45 by mhotting         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

void	rotate_map(t_fdf_data *data, float angle, char axe)
{
	float	matrix[4][4];

	if (data == NULL || (axe != 'x' && axe != 'y' && axe != 'z'))
		return ;
	if (axe == 'x')
		rot_x_eval_matrix(matrix, angle);
	else if (axe == 'y')
		rot_y_eval_matrix(matrix, angle);
	else
		rot_z_eval_matrix(matrix, angle);
	rotation_apply_matrix(data, matrix);
}
