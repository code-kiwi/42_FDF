/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   t_camera_utils.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mhotting <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/20 16:14:14 by mhotting          #+#    #+#             */
/*   Updated: 2024/03/25 12:12:39 by mhotting         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

static void	camera_matrix_calc(t_camera *camera)
{
	if (camera == NULL)
		return ;
	(camera->matrix)[0][0] = camera->x_direction.x;
	(camera->matrix)[0][1] = camera->x_direction.y;
	(camera->matrix)[0][2] = camera->x_direction.z;
	(camera->matrix)[0][3] = -1.0f * camera->position.x;
	(camera->matrix)[1][0] = camera->y_direction.x;
	(camera->matrix)[1][1] = camera->y_direction.y;
	(camera->matrix)[1][2] = -1.0f * camera->y_direction.z;
	(camera->matrix)[1][3] = camera->position.y;
	(camera->matrix)[2][0] = camera->z_direction.x;
	(camera->matrix)[2][1] = camera->z_direction.y;
	(camera->matrix)[2][2] = camera->z_direction.z;
	(camera->matrix)[2][3] = -1.0f * camera->position.z;
	(camera->matrix)[3][0] = 0.0f;
	(camera->matrix)[3][1] = 0.0f;
	(camera->matrix)[3][2] = 0.0f;
	(camera->matrix)[3][3] = 1.0f;
}

void	camera_init(t_camera *camera)
{
	if (camera == NULL)
		return ;
	camera->position.x = CAMERA_INITIAL_POSITION_X;
	camera->position.y = CAMERA_INITIAL_POSITION_Y;
	camera->position.z = CAMERA_INITIAL_POSITION_Z;
	camera->x_direction.x = CAMERA_INITIAL_X_DIRECTION_X;
	camera->x_direction.y = CAMERA_INITIAL_X_DIRECTION_Y;
	camera->x_direction.z = CAMERA_INITIAL_X_DIRECTION_Z;
	camera->y_direction.x = CAMERA_INITIAL_Y_DIRECTION_X;
	camera->y_direction.y = CAMERA_INITIAL_Y_DIRECTION_Y;
	camera->y_direction.z = CAMERA_INITIAL_Y_DIRECTION_Z;
	camera->z_direction.x = CAMERA_INITIAL_Z_DIRECTION_X;
	camera->z_direction.y = CAMERA_INITIAL_Z_DIRECTION_Y;
	camera->z_direction.z = CAMERA_INITIAL_Z_DIRECTION_Z;
	camera->fov = CAMERA_INITIAL_FOV;
	camera_matrix_calc(camera);
}
