/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   event_handlers2.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mhotting <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/15 14:54:11 by mhotting          #+#    #+#             */
/*   Updated: 2024/04/09 21:48:31 by mhotting         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

void	rotation_handler(t_fdf_data *data, int key)
{
	if (data == NULL || (key != KEY_X && key != KEY_Y && key != KEY_Z))
		return ;
	if (key == KEY_X)
		data->rot_x = !(data->rot_x);
	else if (key == KEY_Y)
		data->rot_y = !(data->rot_y);
	else if (key == KEY_Z)
		data->rot_z = !(data->rot_z);
}

void	camera_move_handler(t_camera *camera, int key)
{
	if (camera == NULL)
		return ;
	if (key == KEY_UP)
		camera->position.y += CAMERA_VARIATION;
	if (key == KEY_DOWN)
		camera->position.y -= CAMERA_VARIATION;
	if (key == KEY_LEFT)
		camera->position.x -= CAMERA_VARIATION;
	if (key == KEY_RIGHT)
		camera->position.x += CAMERA_VARIATION;
	camera_matrix_calc(camera);
}

void	switch_projection_handler(t_fdf_data *data)
{
	if (data == NULL)
		return ;
	if (data->projection_type == PROJ_ISO)
	{
		data->projection_type = PROJ_ORTH;
		data->projection_size = PROJECTION_ORTH_SIZE;
		data->projection_size_delta = PROJECTION_ORTH_SIZE_DELTA;
		data->projection_size_min = PROJECTION_ORTH_SIZE_MIN;
		data->projection_size_max = PROJECTION_ORTH_SIZE_MAX;
	}
	else
	{
		data->projection_type = PROJ_ISO;
		data->projection_size = PROJECTION_ISO_SIZE;
		data->projection_size_delta = PROJECTION_ISO_SIZE_DELTA;
		data->projection_size_min = PROJECTION_ISO_SIZE_MIN;
		data->projection_size_max = PROJECTION_ISO_SIZE_MAX;
	}
}
