/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   event_handlers1.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mhotting <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/15 14:54:11 by mhotting          #+#    #+#             */
/*   Updated: 2024/04/09 18:57:01 by mhotting         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

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
	return (0);
}

int	mouse_handler(int button, int x, int y, void *data_received)
{
	t_fdf_data	*data;

	if (data_received == NULL)
		handle_error(NULL, ERROR_MSG_UNKNOWN);
	data = (t_fdf_data *) data_received;
	if (button == MOUSE_SCROLL_UP)
		data->projection_size = f_min(PROJECTION_SIZE_MAX, \
			data->projection_size + PROJECTION_SIZE_DELTA);
	if (button == MOUSE_SCROLL_DOWN)
		data->projection_size = f_max(PROJECTION_SIZE_MIN, \
				data->projection_size - PROJECTION_SIZE_DELTA);
	(void) x;
	(void) y;
	data = (t_fdf_data *) data_received;
	return (0);
}

void	add_event_handlers(t_fdf_data *data)
{
	mlx_hook(data->mlx_win, MLX_ON_DESTROY, (1L << 3), handle_destroy, data);
	mlx_key_hook(data->mlx_win, keyboard_handler, data);
	mlx_mouse_hook(data->mlx_win, mouse_handler, data);
	return ;
}
