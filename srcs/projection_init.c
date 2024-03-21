/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   projection_init.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mhotting <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/21 11:35:00 by mhotting          #+#    #+#             */
/*   Updated: 2024/03/21 12:04:06 by mhotting         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

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

bool	projection_init(t_fdf_data *data)
{
	t_point2d	**proj;
	size_t		i;

	if (data == NULL || data->map == NULL)
		return (false);
	proj = (t_point2d **) ft_calloc(data->nb_lines, sizeof(t_point2d *));
	if (proj == NULL)
		return (false);
	i = 0;
	while (i < data->nb_lines)
	{
		proj[i] = (t_point2d *)ft_calloc(data->nb_line_elts, sizeof(t_point2d));
		if (proj[i] == NULL)
		{
			projection_init_error_free(proj, data->nb_lines);
			return (false);
		}
		i++;
	}
	data->projection = proj;
	projection_init_colors(data->map, proj, data->nb_lines, data->nb_line_elts);
	projection_calculate(data);
	return (true);
}
