/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fdf.h                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mhotting <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/04 09:47:42 by mhotting          #+#    #+#             */
/*   Updated: 2024/03/15 14:40:55 by mhotting         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FDF_H
# define FDF_H

# include "libft.h"
# include "mlx.h"
# include <math.h>

# define ERROR_MSG_USAGE "Usage: fdf infile\n"
# define ERROR_MSG_INIT "Error - Impossible to init mlx data\n"

# define WIN_TITLE "FDF - Computer Graphics Project"
# define WIN_WIDTH 1280
# define WIN_HEIGHT 720
# define IMG_WIDTH 1280
# define IMG_HEIGHT 720

# define KEY_ESC 65307

typedef union u_argb_color
{
	unsigned char	components[3];
	int				value;
}	t_argb_color;

typedef struct s_image
{
	void	*ptr;
	char	*addr;
	int		bpp;
	int		line_len;
	int		endian;
}	t_image;

typedef struct s_fdf_data
{
	void				*mlx_ptr;
	void				*mlx_win;
	t_image				*img1;
	struct s_vector3	**map;
	size_t				nb_lines;
	size_t				line_size;
}	t_fdf_data;

typedef struct s_vector3
{
	float			x;
	float			y;
	float			z;
	t_argb_color	color;
}	t_vector3;

typedef struct s_vector2
{
	int				x;
	int				y;
	t_argb_color	color;
}	t_vector2;

// t_fdf_data functions
bool	init_data_project(t_fdf_data *data);
void	clean_remove(t_fdf_data *data);

// t_color functions
int		get_color_value(t_argb_color *col_a, \
				t_argb_color *col_b, int num, int denom);

// t_image functions
t_image	*init_img(void *mlx_ptr);
void	destroy_img(void *mlx_ptr, t_image *img);

// Draw functions
void	draw_pixel(t_image *img, t_vector2 *pt);
void	draw_line(t_image *img, t_vector2 *a, t_vector2 *b);

// Utils
void	handle_error(t_fdf_data *data, char *error_message);

#endif
