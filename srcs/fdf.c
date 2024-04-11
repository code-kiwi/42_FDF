/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fdf.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mhotting <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/04 09:48:10 by mhotting          #+#    #+#             */
/*   Updated: 2024/04/11 10:20:41 by mhotting         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"
#include "fdf_parsing.h"

/*
 *	Program's entry point
 *	Steps:
 *		- Argument check
 *		- File parsing
 *		- Calibration
 *		- Projection initialization
 *		- Window opening
 *		- Event handlers addition
 *		- Main loop launch
 */
int	main(int argc, char **argv)
{
	t_fdf_data	data;

	if (argc != 2 || argv == NULL)
		handle_error(NULL, ERROR_MSG_USAGE);
	init_data_project(&data);
	if (!parse_input_file(&data, argv[1]) || data.map == NULL)
		handle_error(&data, ERROR_MSG_INFILE);
	calibrate(&data);
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
