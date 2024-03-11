/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   t_fdf_data_utils.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mhotting <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/11 09:24:14 by mhotting          #+#    #+#             */
/*   Updated: 2024/03/11 13:41:24 by mhotting         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

bool	init_data_project(t_fdf_data *data)
{
	data->mlx_ptr = mlx_init();
	if (data->mlx_ptr == NULL)
		return (false);
	data->mlx_win = \
		mlx_new_window(data->mlx_ptr, WIN_WIDTH, WIN_HEIGHT, WIN_TITLE);
	if (data->mlx_win == NULL)
	{
		mlx_destroy_display(data->mlx_ptr);
		return (false);
	}
	data->map = NULL;
	data->nb_lines = 0;
	data->line_size = 0;
	return (true);
}

void	clean_remove(t_fdf_data *data)
{
	size_t	i;

	if (data == NULL || data->mlx_ptr == NULL)
		return ;
	if (data->mlx_win != NULL)
		mlx_destroy_window(data->mlx_ptr, data->mlx_win);
	mlx_destroy_display(data->mlx_ptr);
	if (data->map != NULL)
	{
		i = 0;
		while (i < data->nb_lines)
			free((data->map)[i++]);
		free(data->map);
	}
}
