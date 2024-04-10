/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   projection.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mhotting <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/21 12:09:38 by mhotting          #+#    #+#             */
/*   Updated: 2024/04/09 21:46:07 by mhotting         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

void	projection_iso_calculate(t_fdf_data *data)
{
	size_t		i;
	size_t		j;
	t_point3d	**map;
	t_point2d	**proj;
	t_vector3	temp;

	if (data == NULL || data->map == NULL || data->projection == NULL)
		return ;
	map = data->map;
	proj = data->projection;
	i = 0;
	while (i < data->nb_lines)
	{
		j = 0;
		while (j < data->nb_line_elts)
		{
			temp = matrix_applied_to_point(data->camera.matrix, \
					map[i][j].coords);
			proj[i][j].coords.x = data->projection_size * \
				sqrtf(3.0f) / 2.0f * (temp.x - temp.y);
			proj[i][j].coords.y = data->projection_size * \
				sqrtf(3.0f) / (2.0f * sqrtf(2.0f)) * ((temp.x + temp.y));
			j++;
		}
		i++;
	}
}

void	projection_orth_calculate(t_fdf_data *data)
{
	size_t		i;
	size_t		j;
	t_point3d	**map;
	t_point2d	**proj;
	t_vector3	temp;

	if (data == NULL || data->map == NULL || data->projection == NULL)
		return ;
	map = data->map;
	proj = data->projection;
	i = 0;
	while (i < data->nb_lines)
	{
		j = 0;
		while (j < data->nb_line_elts)
		{
			temp = matrix_applied_to_point(data->camera.matrix, \
					map[i][j].coords);
			proj[i][j].coords.x = data->projection_size * temp.x / temp.z;
			proj[i][j].coords.y = data->projection_size * temp.y / temp.z;
			j++;
		}
		i++;
	}
}
