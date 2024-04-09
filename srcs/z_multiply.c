/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   z_multiply.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mhotting <mhotting@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/09 18:44:33 by mhotting          #+#    #+#             */
/*   Updated: 2024/04/09 18:59:03 by mhotting         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

void	z_multiply(t_fdf_data *data, float factor)
{
	size_t		i;
	size_t		j;
	t_point3d	**map;

	if (data == NULL)
		return ;
	map = data->map;
	i = 0;
	while (i < data->nb_lines)
	{
		j = 0;
		while (j < data->nb_line_elts)
		{
			map[i][j].coords.z *= factor;
			j++;
		}
		i++;
	}
	data->z_max *= factor;
}
