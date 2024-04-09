/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   event_handlers.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mhotting <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/15 14:54:11 by mhotting          #+#    #+#             */
/*   Updated: 2024/04/09 16:13:37 by mhotting         ###   ########.fr       */
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
	return (0);
}

void	add_event_handlers(t_fdf_data *data)
{
	mlx_hook(data->mlx_win, MLX_ON_DESTROY, (1L << 3), handle_destroy, data);
	mlx_key_hook(data->mlx_win, keyboard_handler, data);
	return ;
}

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
