/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   t_parser_info_utils.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mhotting <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/20 10:52:30 by mhotting          #+#    #+#             */
/*   Updated: 2024/03/25 12:24:03 by mhotting         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf_parsing.h"

void	parser_info_add_coords(t_parser_info *info, size_t l, size_t c, int z)
{
	t_point3d	**map;

	if (info == NULL)
		return ;
	if (info->map == NULL || l >= info->nb_lines || c >= info->nb_line_elts)
	{
		info->error = true;
		return ;
	}
	map = info->map;
	map[l][c].coords.x = c * 100.0f;
	map[l][c].coords.y = -1.0f * l * 100.0f;
	map[l][c].coords.z = 1.0f * z;
	map[l][c].coords.w = 1.0f;
}

void	parser_info_add_color(t_parser_info *info, size_t l, size_t c, int col)
{
	t_point3d	**map;

	if (info == NULL)
		return ;
	if (info->map == NULL || l >= info->nb_lines || c >= info->nb_line_elts)
	{
		info->error = true;
		return ;
	}
	map = info->map;
	map[l][c].color.value = col;
}

void	parser_info_init(t_parser_info *info)
{
	if (info == NULL)
		return ;
	info->nb_lines = 0;
	info->nb_line_elts = 0;
	info->map = NULL;
	info->error = false;
}

void	parser_info_map_free(t_point3d **map, size_t nb_lines)
{
	size_t	i;

	if (map == NULL)
		return ;
	i = 0;
	while (i < nb_lines && map[i] != NULL)
	{
		free(map[i]);
		i++;
	}
	free(map);
}

void	parser_info_init_map(t_parser_info *info)
{
	size_t		i;
	t_point3d	**map;

	if (info == NULL || info->nb_lines == 0 || info->nb_line_elts == 0)
		return ;
	map = (t_point3d **) ft_calloc(info->nb_lines, sizeof(t_point3d *));
	if (map == NULL)
		return ;
	i = 0;
	while (i < info->nb_lines)
	{
		map[i] = (t_point3d *) ft_calloc(info->nb_line_elts, sizeof(t_point3d));
		if (map[i] == NULL)
		{
			info->error = true;
			parser_info_map_free(map, info->nb_lines);
			return ;
		}
		i++;
	}
	info->map = map;
}
