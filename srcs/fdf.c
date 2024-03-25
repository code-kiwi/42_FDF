/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fdf.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mhotting <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/04 09:48:10 by mhotting          #+#    #+#             */
/*   Updated: 2024/03/25 12:02:17 by mhotting         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"
#include "fdf_parsing.h"

int	main(int argc, char **argv)
{
	t_fdf_data	data;

	if (argc != 2 || argv == NULL)
		handle_error(NULL, ERROR_MSG_USAGE);
	init_data_project(&data);
	if (!parse_input_file(&data, argv[1]) || data.map == NULL)
		handle_error(&data, ERROR_MSG_INFILE);
	
/*
	size_t		i;
	size_t		j;
	t_point3d	point;

	i = 0;
	while (i < data.nb_lines)
	{
		j = 0;
		while (j < data.nb_line_elts)
		{
			point = data.map[i][j];
			printf("POINT: (%0.2f, %0.2f, %0.2f, %0.2f)\n", point.coords.x, point.coords.y, point.coords.z, point.coords.w);
			while (getchar() != '\n');
			j++;
		}
		i++;
	}
	return (0);
*/

	if (!projection_init(&data) || data.projection == NULL)
		handle_error(&data, ERROR_MSG_UNKNOWN);

	if (!open_project_window(&data))
		handle_error(&data, ERROR_MSG_INIT);
	add_event_handlers(&data);
	mlx_loop_hook(data.mlx_ptr, render, &data);
	mlx_loop(data.mlx_ptr);
	clean_remove(&data);
	return (0);
}
