/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rotation1.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mhotting <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/04 15:10:19 by mhotting          #+#    #+#             */
/*   Updated: 2024/04/09 16:49:45 by mhotting         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

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

void	rotation_apply_matrix(t_fdf_data *data, float rot_matrix[4][4])
{
	t_vector3	temp;
	size_t		i;
	size_t		j;
	t_point3d	**map;

	if (data == NULL)
		return ;
	map = data->map;
	i = 0;
	while (i < data->nb_lines)
	{
		j = 0;
		while (j < data->nb_line_elts)
		{
			temp = matrix_applied_to_point(rot_matrix, map[i][j].coords);
			map[i][j].coords.x = temp.x;
			map[i][j].coords.y = temp.y;
			map[i][j].coords.z = temp.z;
			j++;
		}
		i++;
	}
}

void	rotation_apply(t_fdf_data *data)
{
	float	rot_matrix[4][4];

	if (data == NULL)
		return ;
	if (data->rot_x)
	{
		rot_x_eval_matrix(rot_matrix, ROT_ANGLE);
		rotation_apply_matrix(data, rot_matrix);
	}
	if (data->rot_y)
	{
		rot_y_eval_matrix(rot_matrix, ROT_ANGLE);
		rotation_apply_matrix(data, rot_matrix);
	}
	if (data->rot_z)
	{
		rot_z_eval_matrix(rot_matrix, ROT_ANGLE);
		rotation_apply_matrix(data, rot_matrix);
	}
}
