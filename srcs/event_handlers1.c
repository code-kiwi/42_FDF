/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   event_handlers1.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mhotting <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/15 14:54:11 by mhotting          #+#    #+#             */
/*   Updated: 2024/04/11 10:12:30 by mhotting         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

/*
 *	Clears project data and exits the program
 *	All allocated memory is freed
 */
int	handle_destroy(void *data_received)
{
	t_fdf_data	*data;

	if (data_received == NULL)
		handle_error(NULL, ERROR_MSG_UNKNOWN);
	data = (t_fdf_data *) data_received;
	clean_remove(data);
	exit(EXIT_SUCCESS);
	return (0);
}

/*
 *	Handles keyboard event for the project
 *	The received data is the project main structure's pointer
 *	Different handlers are called depending on the key pressed
 *	Events:
 *		- x, y and z for rotation
 *		- escape for exiting the program
 *		- arrows for moving the camera
 */
int	keyboard_handler(int key, void *data_received)
{
	t_fdf_data	*data;

	if (data_received == NULL)
		handle_error(NULL, ERROR_MSG_UNKNOWN);
	data = (t_fdf_data *) data_received;
	if (key == KEY_ESC)
	{
		clean_remove(data);
		exit(EXIT_SUCCESS);
	}
	else if (key == KEY_X || key == KEY_Y || key == KEY_Z)
		rotation_handler(data, key);
	else if (
		key == KEY_UP || key == KEY_DOWN
		|| key == KEY_LEFT || key == KEY_RIGHT
	)
		camera_move_handler(&(data->camera), key);
	else if (key == KEY_P)
		switch_projection_handler(data);
	return (0);
}

/*
 *	Handles mouse events for the project
 *	The received data is the project main structure's pointer
 *	Different handlers are called depending on the button pressed
 *	Events:
 *		- mouse wheel: zoom onto the map
 */
int	mouse_handler(int button, int x, int y, void *data_received)
{
	t_fdf_data	*data;

	if (data_received == NULL)
		handle_error(NULL, ERROR_MSG_UNKNOWN);
	data = (t_fdf_data *) data_received;
	if (button == MOUSE_SCROLL_UP)
		data->projection_size = f_min(data->projection_size_max, \
				data->projection_size + data->projection_size_delta);
	if (button == MOUSE_SCROLL_DOWN)
		data->projection_size = f_max(data->projection_size_min, \
				data->projection_size - data->projection_size_delta);
	(void) x;
	(void) y;
	return (0);
}

/*
 *	Adds the event handlers to the project
 *	Adds a hook for keyboard events, mouse events and for a click onto the
 *	closing button
 */
void	add_event_handlers(t_fdf_data *data)
{
	mlx_hook(data->mlx_win, MLX_ON_DESTROY, (1L << 3), handle_destroy, data);
	mlx_key_hook(data->mlx_win, keyboard_handler, data);
	mlx_mouse_hook(data->mlx_win, mouse_handler, data);
	return ;
}
