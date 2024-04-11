/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   event_handlers2.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mhotting <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/15 14:54:11 by mhotting          #+#    #+#             */
/*   Updated: 2024/04/11 11:55:44 by mhotting         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

/*
 *	Handles the rotation event
 *	When a rotation key is pressed, the corresponding flag is inverted
 *	When a flag is set to true, the roation is activated
 *	NB: rotation is disabled for isometric projection
 */
void	rotation_handler(t_fdf_data *data, int key)
{
	if (
		data == NULL || (key != KEY_X && key != KEY_Y && key != KEY_Z)
		|| data->projection_type == PROJ_ISO
	)
		return ;
	if (key == KEY_X)
		data->rot_x = !(data->rot_x);
	else if (key == KEY_Y)
		data->rot_y = !(data->rot_y);
	else if (key == KEY_Z)
		data->rot_z = !(data->rot_z);
}

/*
 *	Handles the camera move event
 *	When an arrow is pressed, the camera is moved of CAMERA_VARIATION along
 *	x or y axis
 */
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

/*
 *	Handles the projection switching event
 *	The projection is then set to perspective projection and for the moment, we
 *	cannot switch back to isometric one
 *	When switching, the parameters of the perspective projection are set
 */
void	switch_projection_handler(t_fdf_data *data)
{
	if (data == NULL)
		return ;
	if (data->projection_type == PROJ_ISO)
	{
		data->projection_type = PROJ_PERSP;
		data->projection_size = PROJECTION_PERSP_SIZE;
		data->projection_size_delta = PROJECTION_PERSP_SIZE_DELTA;
		data->projection_size_min = PROJECTION_PERSP_SIZE_MIN;
		data->projection_size_max = PROJECTION_PERSP_SIZE_MAX;
		rotate_map(data, PI / 6, 'z');
	}
}
