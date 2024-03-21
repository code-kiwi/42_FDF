/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   render.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mhotting <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/21 13:59:43 by mhotting          #+#    #+#             */
/*   Updated: 2024/03/21 16:10:02 by mhotting         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

static void	render_draw_lines(t_fdf_data *data, t_image *img)
{
	size_t		r;
	size_t		c;
	t_point2d	**proj;

	if (data == NULL || data->projection == NULL || img == NULL)
		return ;
	proj = data->projection;
	r = 0;
	while (r < data->nb_lines)
	{
		c = 0;
		while (c < data->nb_line_elts)
		{
			if (r + 1 < data->nb_lines)
				draw_line(img, &(proj[r][c]), &(proj[r + 1][c]));
			if (c + 1 < data->nb_line_elts)
				draw_line(img, &(proj[r][c]), &(proj[r][c + 1]));
			c++;
		}
		r++;
	}
}

static void	render_process(t_fdf_data *data)
{
	t_image	*img;

	if (data == NULL)
		return ;
	if (data->img_active == NULL || data->img_active == data->img2)
		img = data->img1;
	else
		img = data->img2;
	img_clear(img);
	projection_calculate(data);
	render_draw_lines(data, img);
	mlx_put_image_to_window(data->mlx_ptr, data->mlx_win, \
			img->ptr, IMG_INITIAL_POSITION_X, IMG_INITIAL_POSITION_Y);
	data->img_active = img;
}

int	render(void *data_received)
{
	t_fdf_data	*data;

	if (data_received == NULL)
		return (0);
	data = (t_fdf_data *) data_received;
	data->event_loop_counter++;
	if (data->event_loop_counter > EVENT_LOOP_FRAME_TARGET)
	{
		render_process(data);
		data->event_loop_counter = 0;
	}
	return (0);
}
