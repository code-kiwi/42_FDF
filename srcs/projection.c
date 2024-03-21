/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   projection.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mhotting <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/21 12:09:38 by mhotting          #+#    #+#             */
/*   Updated: 2024/03/21 12:26:25 by mhotting         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

void	projection_calculate(t_fdf_data *data)
{
	size_t		i;
	size_t		j;
	t_point3d	**map;
	t_point2d	**proj;

	if (data == NULL || data->map == NULL || data->projection == NULL)
		return ;
	map = data->map;
	proj = data->projection;
	i = 0;
	while (i < data->nb_lines)
	{
		j = 0;
		while (j < data->nb_line_elts)
		{
			proj[i][j].coords.x = map[i][j].coords.x;
			proj[i][j].coords.y = map[i][j].coords.y;
			j++;
		}
		i++;
	}
}
