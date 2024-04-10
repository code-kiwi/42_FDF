/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   calibration.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mhotting <mhotting@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/09 16:29:11 by mhotting          #+#    #+#             */
/*   Updated: 2024/04/10 02:09:16 by mhotting         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

void	calibrate(t_fdf_data *data)
{
	if (data == NULL)
		return ;
	z_multiply(data, -1.0f * Z_CALIBRATE_FACTOR);
	data->z_max = f_max(f_max(data->nb_lines, data->nb_line_elts), data->z_max);
	data->camera.position.z = data->z_max + 10;
	camera_matrix_calc(&(data->camera));
	rotate_map(data, -1.0f * PI / 3, 'x');
	rotate_map(data, -1.0f * PI / 6, 'y');
}
