/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fdf.h                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mhotting <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/04 09:47:42 by mhotting          #+#    #+#             */
/*   Updated: 2024/03/11 13:55:28 by mhotting         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FDF_H
# define FDF_H

# include "libft.h"
# include "mlx.h"

# define ERROR_MSG_USAGE "Usage: fdf infile\n"
# define ERROR_MSG_INIT "Error - Impossible to init mlx data\n"

# define WIN_TITLE "FDF - Computer Graphics Project"
# define WIN_WIDTH 1200
# define WIN_HEIGHT 900

typedef struct s_fdf_data
{
	void				*mlx_ptr;
	void				*mlx_win;
	struct s_vector3	**map;
	size_t				nb_lines;
	size_t				line_size;
}	t_fdf_data;

typedef struct s_vector3
{
	float	x;
	float	y;
	float	z;
	int		color;
}	t_vector3;

bool	init_data_project(t_fdf_data *data);
void	clean_remove(t_fdf_data *data);

void	handle_error(t_fdf_data *data, char *error_message);

#endif
