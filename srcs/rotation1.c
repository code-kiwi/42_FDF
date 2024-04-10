/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rotation1.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mhotting <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/04 15:10:19 by mhotting          #+#    #+#             */
/*   Updated: 2024/04/10 01:46:05 by mhotting         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

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

void	rotation_apply_x(t_fdf_data *data, float rot_matrix[4][4], float angle)
{
	rot_x_eval_matrix(rot_matrix, angle);
	rotation_apply_matrix(data, rot_matrix);
	if (data->projection_type == PROJ_ISO)
	{
		rot_y_eval_matrix(rot_matrix, -1.0f * angle);
		rotation_apply_matrix(data, rot_matrix);
	}
}

void	rotation_apply_y(t_fdf_data *data, float rot_matrix[4][4], float angle)
{
	rot_y_eval_matrix(rot_matrix, angle);
	rotation_apply_matrix(data, rot_matrix);
	if (data->projection_type == PROJ_ISO)
	{
		rot_x_eval_matrix(rot_matrix, angle);
		rotation_apply_matrix(data, rot_matrix);
	}
}

void	rotation_apply_z(t_fdf_data *data, float rot_matrix[4][4], float angle)
{
	rot_z_eval_matrix(rot_matrix, angle);
	rotation_apply_matrix(data, rot_matrix);
}

void	rotation_apply(t_fdf_data *data)
{
	float	rot_matrix[4][4];

	if (data == NULL)
		return ;
	if (data->rot_x)
		rotation_apply_x(data, rot_matrix, ROT_ANGLE);
	if (data->rot_y)
		rotation_apply_y(data, rot_matrix, ROT_ANGLE);
	if (data->rot_z)
		rotation_apply_z(data, rot_matrix, ROT_ANGLE);
}		
