/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   t_fdf_data_utils.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mhotting <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/11 09:24:14 by mhotting          #+#    #+#             */
/*   Updated: 2024/03/21 15:34:24 by mhotting         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

static bool	init_project_images(t_fdf_data *data)
{
	if (data == NULL || data->mlx_ptr == NULL)
		return (false);
	data->img1 = img_init(data->mlx_ptr);
	if (data->img1 == NULL)
		return (false);
	data->img2 = img_init(data->mlx_ptr);
	if (data->img2 == NULL)
	{
		img_destroy(data->mlx_ptr, data->img1);
		data->img1 = NULL;
		return (false);
	}
	return (true);
}

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
	if (!init_project_images(data))
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
	data->img2 = NULL;
	data->img_active = NULL;
	data->map = NULL;
	data->projection = NULL;
	data->nb_lines = 0;
	data->nb_line_elts = 0;
	data->event_loop_counter = 0;
	camera_init(&data->camera);
}

static void	clean_map_proj(t_point3d **map, t_point2d **proj, size_t nb_lines)
{
	size_t	i;

	if (map != NULL)
	{
		i = 0;
		while (i < nb_lines)
			free(map[i++]);
		free(map);
	}
	if (proj != NULL)
	{
		i = 0;
		while (i < nb_lines)
			free(proj[i++]);
		free(proj);
	}
}

void	clean_remove(t_fdf_data *data)
{
	t_point3d	**map;
	t_point2d	**projection;

	if (data == NULL)
		return ;
	if (data->mlx_ptr != NULL && data->mlx_win != NULL)
		mlx_destroy_window(data->mlx_ptr, data->mlx_win);
	map = data->map;
	projection = data->projection;
	clean_map_proj(map, projection, data->nb_lines);
	if (data->mlx_ptr != NULL && data->img1 != NULL)
		img_destroy(data->mlx_ptr, data->img1);
	if (data->mlx_ptr != NULL && data->img2 != NULL)
		img_destroy(data->mlx_ptr, data->img2);
	if (data->mlx_ptr != NULL)
		mlx_destroy_display(data->mlx_ptr);
	free(data->mlx_ptr);
}
