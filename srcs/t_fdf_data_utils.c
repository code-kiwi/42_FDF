/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   t_fdf_data_utils.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mhotting <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/11 09:24:14 by mhotting          #+#    #+#             */
/*   Updated: 2024/03/21 11:10:40 by mhotting         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

bool	open_project_window(t_fdf_data *data)
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
	data->img1 = init_img(data->mlx_ptr);
	if (data->img1 == NULL)
	{
		mlx_destroy_window(data->mlx_ptr, data->mlx_win);
		mlx_destroy_display(data->mlx_ptr);
		return (false);
	}
	return (true);
}

void	init_data_project(t_fdf_data *data)
{
	data->mlx_ptr = NULL;
	data->mlx_win = NULL;
	data->img1 = NULL;
	data->map = NULL;
	data->nb_lines = 0;
	data->nb_line_elts = 0;
	camera_init(&data->camera);
}

void	clean_remove(t_fdf_data *data)
{
	size_t		i;
	t_point3d	**map;

	if (data == NULL)
		return ;
	if (data->mlx_ptr != NULL && data->mlx_win != NULL)
		mlx_destroy_window(data->mlx_ptr, data->mlx_win);
	map = data->map;
	if (map != NULL)
	{
		i = 0;
		while (i < data->nb_lines)
			free(map[i++]);
		free(map);
	}
	if (data->mlx_ptr != NULL && data->img1 != NULL)
		destroy_img(data->mlx_ptr, data->img1);
	if (data->mlx_ptr != NULL)
		mlx_destroy_display(data->mlx_ptr);
	free(data->mlx_ptr);
}
