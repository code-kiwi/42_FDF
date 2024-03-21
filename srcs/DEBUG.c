/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   DEBUG.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mhotting <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/21 12:30:06 by mhotting          #+#    #+#             */
/*   Updated: 2024/03/21 12:31:08 by mhotting         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

#include <stdio.h>
void	DEBUG(t_fdf_data *data)
{
	size_t	i;
	size_t	j;
	t_point3d **map;
	t_point2d **proj;

	i = 0;
	map = data->map;
	proj = data->projection;
	while (i < data->nb_lines)
	{
		j = 0;
		while (j < data->nb_line_elts)
		{
			printf("(%.2f, %.2f, %.2f) - COL: %d\n", map[i][j].coords.x, map[i][j].coords.y, map[i][j].coords.z, map[i][j].color.value);
			printf("(%d, %d) - COL: %d\n", proj[i][j].coords.x, proj[i][j].coords.y, proj[i][j].color.value);
			while (getchar() != '\n');
			j++;
		}
		i++;
	}
}
