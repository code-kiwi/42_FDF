/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   t_image_utils.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mhotting <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/13 13:17:53 by mhotting          #+#    #+#             */
/*   Updated: 2024/03/21 15:53:42 by mhotting         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

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

void	img_destroy(void *mlx_ptr, t_image *img)
{
	if (mlx_ptr == NULL || img == NULL || img->ptr == NULL)
		return ;
	mlx_destroy_image(mlx_ptr, img->ptr);
	free(img);
}
