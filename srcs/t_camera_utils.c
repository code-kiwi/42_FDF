/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   t_camera_utils.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mhotting <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/20 16:14:14 by mhotting          #+#    #+#             */
/*   Updated: 2024/03/20 16:24:20 by mhotting         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

void	camera_init(t_camera *camera)
{
	if (camera == NULL)
		return ;
	camera->position.x = CAMERA_INITIAL_POSITION_X;
	camera->position.y = CAMERA_INITIAL_POSITION_Y;
	camera->position.z = CAMERA_INITIAL_POSITION_Z;
	camera->direction.x = CAMERA_INITIAL_DIRECTION_X;
	camera->direction.y = CAMERA_INITIAL_DIRECTION_Y;
	camera->direction.z = CAMERA_INITIAL_DIRECTION_Z;
	camera->fov = CAMERA_INITIAL_FOV;
}
