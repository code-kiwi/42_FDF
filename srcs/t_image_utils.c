/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   t_image_utils.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mhotting <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/13 13:17:53 by mhotting          #+#    #+#             */
/*   Updated: 2024/03/15 14:35:57 by mhotting         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

t_image	*init_img(void *mlx_ptr)
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

void	destroy_img(void *mlx_ptr, t_image *img)
{
	if (mlx_ptr == NULL || img == NULL || img->ptr == NULL)
		return ;
	mlx_destroy_image(mlx_ptr, img->ptr);
	free(img);
}
