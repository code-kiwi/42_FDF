/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   render.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mhotting <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/21 13:59:43 by mhotting          #+#    #+#             */
/*   Updated: 2024/04/11 10:58:42 by mhotting         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

/*
 *	Draws the lines which link the data->projection points onto the given image
 */
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

/*
 *	Rendering process
 *	Steps:
 *		- the inactive image is selected in order to be the one we draw on
 *		- the image is cleared
 *		- The projected points are drawn on the inactive image, and the lines
 *		which links them are drawn
 *		- The images are switched and the active image pointer of given data is
 *		updated
 */
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
	rotation_apply(data);
	if (data->projection_type == PROJ_ISO)
		projection_iso_calculate(data);
	else
		projection_persp_calculate(data);
	render_draw_lines(data, img);
	mlx_put_image_to_window(data->mlx_ptr, data->mlx_win, \
			img->ptr, IMG_INITIAL_POSITION_X, IMG_INITIAL_POSITION_Y);
	data->img_active = img;
}

/*
 *	Handles rendering process
 *	This function is associated to the mlx loop hook
 *	The received data is casted into t_fdf_data pointer
 *	In order to stabilize the animation frame rate, the loop process is launched
 *	only when the loop counter reaches EVENT_LOOP_FRAME_TARGET
 */
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
