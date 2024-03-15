/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   event_handlers.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mhotting <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/15 14:54:11 by mhotting          #+#    #+#             */
/*   Updated: 2024/03/15 15:53:49 by mhotting         ###   ########.fr       */
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
	return (0);
}

void	add_event_handlers(t_fdf_data *data)
{
	mlx_hook(data->mlx_win, MLX_ON_DESTROY, (1L << 3), handle_destroy, data);
	mlx_key_hook(data->mlx_win, keyboard_handler, data);
	return ;
}
