/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fdf.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mhotting <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/04 09:48:10 by mhotting          #+#    #+#             */
/*   Updated: 2024/03/20 14:12:46 by mhotting         ###   ########.fr       */
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
	if (!open_project_window(&data))
		handle_error(&data, ERROR_MSG_INIT);
	add_event_handlers(&data);

	// Testing pixel put
	t_vector2	pt1;
	t_vector2	pt2;

	pt1.color.value = 0x99A233;
	pt2.color.value = 0xAADDFF;
	pt1.x = 0;
	pt1.y = 0;
	pt2.x = 600;
	pt2.y = 0;
	for (int i = 0; i < 10; i++)
	{
		draw_line(data.img1, &pt1, &pt2);
		pt1.y++;
		pt2.y++;
	}
	mlx_put_image_to_window(data.mlx_ptr, data.mlx_win, data.img1->ptr, 0, 0);

	mlx_loop(data.mlx_ptr);
	clean_remove(&data);
	return (0);
}
