/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   t_image_utils.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mhotting <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/13 13:17:53 by mhotting          #+#    #+#             */
/*   Updated: 2024/04/11 11:12:15 by mhotting         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

/*
 *	Clears the given image by setting all its pixels to 0
 */
void	img_clear(t_image *img)
{
	int			x;
	int			y;
	t_point2d	point;

	if (img == NULL)
		return ;
	point.color.value = 0;
	x = -IMG_WIDTH / 2;
	while (x <= IMG_WIDTH / 2)
	{
		y = -IMG_HEIGHT / 2;
		while (y <= IMG_HEIGHT / 2)
		{
			point.coords.x = x;
			point.coords.y = y;
			draw_pixel(img, &point);
			y++;
		}
		x++;
	}
}

/*
 *	Allocates a new t_image structure and sets its parameters
 *	In case of ERROR, returns NULL
 */
t_image	*img_init(void *mlx_ptr)
{
	t_image	*img;

	if (mlx_ptr == NULL)
		return (NULL);
	img = (t_image *) malloc(sizeof(t_image));
	if (img == NULL)
		return (NULL);
	img->ptr = mlx_new_image(mlx_ptr, IMG_WIDTH, IMG_HEIGHT);
	if (img->ptr == NULL)
	{
		free(img);
		return (NULL);
	}
	img->addr = mlx_get_data_addr(\
			img->ptr, &img->bpp, &img->line_len, &img->endian);
	if (img->addr == NULL)
	{
		mlx_destroy_image(mlx_ptr, img->ptr);
		free(img);
		return (NULL);
	}
	return (img);
}

/*
 *	Frees the memory allocated to the given t_image element
 *	Destroys its mlx pointer and frees the pointer's memory
 */
void	img_destroy(void *mlx_ptr, t_image *img)
{
	if (mlx_ptr == NULL || img == NULL || img->ptr == NULL)
		return ;
	mlx_destroy_image(mlx_ptr, img->ptr);
	free(img);
}
