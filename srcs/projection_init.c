/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   projection_init.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mhotting <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/21 11:35:00 by mhotting          #+#    #+#             */
/*   Updated: 2024/04/11 10:53:27 by mhotting         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

/*
 *	Frees the projection two dimension array
 */
static void	projection_init_error_free(t_point2d **proj, size_t nb_lines)
{
	size_t	i;

	if (proj == NULL)
		return ;
	i = 0;
	while (i < nb_lines && proj[i] != NULL)
	{
		free(proj[i]);
		i++;
	}
	free(proj);
}

/*
 *	Sets all the 2d projection point colors to their corresponding 3d projection
 *	point colors
 */
static void	projection_init_colors(
	t_point3d **map, t_point2d **proj, size_t nb_row, size_t nb_col
)
{
	size_t	i;
	size_t	j;

	if (map == NULL || proj == NULL)
		return ;
	i = 0;
	while (i < nb_row)
	{
		j = 0;
		if (map[i] == NULL || proj[i] == NULL)
		{
			i++;
			continue ;
		}
		while (j < nb_col)
		{
			proj[i][j].color.value = map[i][j].color.value;
			j++;
		}
		i++;
	}
}

/*
 *	Creates data->projection map (two dimensions array of t_point2d elements)
 *	corresponding to the data->map (two dimensions array of t_point3d elements)
 *	The 2d point colors are the same than the 3d ones.
 *	When the map is initialized, the 2d points coordinates are calculated
 *	depending on the activated projection type
 *	Returns true on SUCCESS, false on ERROR
 */
bool	projection_init(t_fdf_data *data)
{
	t_point2d	**proj;
	size_t		i;

	if (data == NULL || data->map == NULL)
		return (false);
	proj = (t_point2d **) ft_calloc(data->nb_lines, sizeof(t_point2d *));
	if (proj == NULL)
		return (false);
	i = -1;
	while (++i < data->nb_lines)
	{
		proj[i] = (t_point2d *)ft_calloc(data->nb_line_elts, sizeof(t_point2d));
		if (proj[i] == NULL)
		{
			projection_init_error_free(proj, data->nb_lines);
			return (false);
		}
	}
	data->projection = proj;
	projection_init_colors(data->map, proj, data->nb_lines, data->nb_line_elts);
	if (data->projection_type == PROJ_ISO)
		projection_iso_calculate(data);
	else
		projection_persp_calculate(data);
	return (true);
}
