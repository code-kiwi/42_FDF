/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rotation2.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mhotting <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/04 15:10:19 by mhotting          #+#    #+#             */
/*   Updated: 2024/04/10 01:47:45 by mhotting         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

void	rotate_map(t_fdf_data *data, float angle, char axe)
{
	float	matrix[4][4];

	if (data == NULL || (axe != 'x' && axe != 'y' && axe != 'z'))
		return ;
	if (axe == 'x')
		rotation_apply_x(data, matrix, angle);
	else if (axe == 'y')
		rotation_apply_y(data, matrix, angle);
	else
		rotation_apply_z(data, matrix, angle);
	rotation_apply_matrix(data, matrix);
}

void	rot_x_eval_matrix(float rot_matrix[4][4], float angle)
{
	matrix_init_identity(rot_matrix);
	rot_matrix[1][1] = cos(angle);
	rot_matrix[1][2] = -1.0f * sin(angle);
	rot_matrix[2][1] = sin(angle);
	rot_matrix[2][2] = cos(angle);
}

void	rot_y_eval_matrix(float rot_matrix[4][4], float angle)
{
	matrix_init_identity(rot_matrix);
	rot_matrix[0][0] = cos(angle);
	rot_matrix[0][2] = sin(angle);
	rot_matrix[2][0] = -1.0f * sin(angle);
	rot_matrix[2][2] = cos(angle);
}

void	rot_z_eval_matrix(float rot_matrix[4][4], float angle)
{
	matrix_init_identity(rot_matrix);
	rot_matrix[0][0] = cos(angle);
	rot_matrix[0][1] = -1.0f * sin(angle);
	rot_matrix[1][0] = sin(angle);
	rot_matrix[1][1] = cos(angle);
}
