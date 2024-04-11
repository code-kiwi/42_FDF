/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   calibration.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mhotting <mhotting@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/09 16:29:11 by mhotting          #+#    #+#             */
/*   Updated: 2024/04/11 11:46:27 by mhotting         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

/*
 *	Sets some parameters before first redenring:
 *		- z_max is calculated in order to set the right camera position
 *		- camera matrix is then evaluated
 *		- the map is submitted to a rotation
 */
void	calibrate(t_fdf_data *data)
{
	size_t	nb_points;

	if (data == NULL)
		return ;
	z_multiply(data, Z_CALIBRATE_FACTOR);
	data->z_max = f_max(f_max(data->nb_lines, data->nb_line_elts), data->z_max);
	data->camera.position.z = data->z_max + 10;
	camera_matrix_calc(&(data->camera));
	rotate_map(data, -1.0f * PI / 8, 'x');
	nb_points = data->nb_lines * data->nb_line_elts;
	if (nb_points < 1000)
		data->projection_size = 15.0f;
	else if (nb_points < 10000)
		data->projection_size = 8.0f;
	else if (nb_points < 40000)
		data->projection_size = 6.0f;
	else
		data->projection_size = 4.0f;
}
