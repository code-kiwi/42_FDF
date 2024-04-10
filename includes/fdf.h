/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fdf.h                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mhotting <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/04 09:47:42 by mhotting          #+#    #+#             */
/*   Updated: 2024/04/10 02:02:47 by mhotting         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FDF_H
# define FDF_H

# include "libft.h"
# include "mlx.h"
# include <fcntl.h>
# include <math.h>


# include <stdio.h>

# define ERROR_MSG_USAGE "Usage: fdf infile"
# define ERROR_MSG_INIT "Error - Impossible to init mlx data"
# define ERROR_MSG_UNKNOWN "Error - Unknown error occured"
# define ERROR_MSG_INFILE "Error - Input file is invalid or cannot be parsed"

# define WIN_TITLE "FDF - Computer Graphics Project"
# define WIN_WIDTH 1280
# define WIN_HEIGHT 720
# define IMG_WIDTH 1280
# define IMG_HEIGHT 720
# define IMG_INITIAL_POSITION_X 0
# define IMG_INITIAL_POSITION_Y 0

# define EVENT_LOOP_FRAME_TARGET 1000

# define KEY_ESC 65307
# define KEY_X 120
# define KEY_Y 121
# define KEY_Z 122
# define KEY_P 112
# define KEY_PLUS_NUM 65451
# define KEY_MINUS_NUM 65453
# define KEY_UP 65362
# define KEY_DOWN 65364
# define KEY_LEFT 65361
# define KEY_RIGHT 65363
# define MOUSE_SCROLL_UP 4
# define MOUSE_SCROLL_DOWN 5

# define COLOR_SEPARATOR ','
# define COLOR_DEFAULT 0xFFFFFF
# define UPPER_HEX_BASE "0123456789ABCDEF"

# define PROJECTION_ORTH_SIZE 400.0f
# define PROJECTION_ORTH_SIZE_DELTA 10.0f
# define PROJECTION_ORTH_SIZE_MIN 10.0f
# define PROJECTION_ORTH_SIZE_MAX 2000.0f

# define PROJECTION_ISO_SIZE 10.0f
# define PROJECTION_ISO_SIZE_DELTA 1.0f
# define PROJECTION_ISO_SIZE_MIN 0.2f
# define PROJECTION_ISO_SIZE_MAX 50.0f

# define Z_CALIBRATE_FACTOR 0.5f

# define FDF_FILE_EXTENSION ".fdf"
# define FDF_FILE_EXTENSION_LEN 4

# define CAMERA_INITIAL_POSITION_X 0.0f
# define CAMERA_INITIAL_POSITION_Y 0.0f
# define CAMERA_INITIAL_POSITION_Z 30.0f
# define CAMERA_INITIAL_X_DIRECTION_X 1.0f
# define CAMERA_INITIAL_X_DIRECTION_Y 0.0f
# define CAMERA_INITIAL_X_DIRECTION_Z 0.0f
# define CAMERA_INITIAL_Y_DIRECTION_X 0.0f
# define CAMERA_INITIAL_Y_DIRECTION_Y 1.0f
# define CAMERA_INITIAL_Y_DIRECTION_Z 0.0f
# define CAMERA_INITIAL_Z_DIRECTION_X 0.0f
# define CAMERA_INITIAL_Z_DIRECTION_Y 0.0f
# define CAMERA_INITIAL_Z_DIRECTION_Z -1.0f
# define CAMERA_INITIAL_FOV 0.7854f
# define CAMERA_VARIATION 1.0f

# define PI 3.14159f
# define ROT_ANGLE 0.049087344f

enum e_mlx_event
{
	MLX_ON_KEYDOWN = 2,
	MLX_ON_KEYUP = 3,
	MLX_ON_MOUSEDOWN = 4,
	MLX_ON_MOUSEUP = 5,
	MLX_ON_MOUSEMOVE = 6,
	MLX_ON_EXPOSE = 12,
	MLX_ON_DESTROY = 17
};

typedef enum e_projection_type
{
	PROJ_ISO,
	PROJ_ORTH
}	t_projection_type;

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

typedef struct s_vector3
{
	float	x;
	float	y;
	float	z;
	float	w;
}	t_vector3;

typedef struct s_vector2
{
	int	x;
	int	y;
}	t_vector2;

typedef struct s_point_3d
{
	t_vector3		coords;
	t_argb_color	color;
}	t_point3d;

typedef struct s_point_2d
{
	t_vector2		coords;
	t_argb_color	color;
}	t_point2d;

typedef struct s_camera
{
	t_vector3	position;
	t_vector3	x_direction;
	t_vector3	y_direction;
	t_vector3	z_direction;
	float		fov;
	float		matrix[4][4];
}	t_camera;

typedef struct s_fdf_data
{
	void				*mlx_ptr;
	void				*mlx_win;
	t_image				*img1;
	t_image				*img2;
	t_image				*img_active;
	t_point3d			**map;
	t_point2d			**projection;
	size_t				nb_lines;
	size_t				nb_line_elts;
	t_camera			camera;
	size_t				event_loop_counter;
	bool				rot_x;
	bool				rot_y;
	bool				rot_z;
	float				z_max;
	float				projection_size;
	float				projection_size_delta;
	float				projection_size_min;
	float				projection_size_max;
	t_projection_type	projection_type;
}	t_fdf_data;

// t_fdf_data functions
void		init_data_project(t_fdf_data *data);
bool		open_project_window(t_fdf_data *data);
void		clean_remove(t_fdf_data *data);

// t_color functions
int			get_color_value(t_argb_color *col_a, \
					t_argb_color *col_b, int num, int denom);

// t_image functions
t_image		*img_init(void *mlx_ptr);
void		img_destroy(void *mlx_ptr, t_image *img);
void		img_clear(t_image *img);

// t_camera functions
void		camera_init(t_camera *camera);
void		camera_matrix_calc(t_camera *camera);

// Draw functions
void		draw_pixel(t_image *img, t_point2d *pt);
void		draw_line(t_image *img, t_point2d *a, t_point2d *b);

// Projection functions
bool		projection_init(t_fdf_data *data);
void		projection_iso_calculate(t_fdf_data *data);
void		projection_orth_calculate(t_fdf_data *data);

// Rotation functions
void		rotation_apply(t_fdf_data *data);
void		rotation_apply_matrix(t_fdf_data *data, float rot_matrix[4][4]);
void		rotate_map(t_fdf_data *data, float angle, char axe);
void		rotation_apply_x(t_fdf_data *data, float rot_m[4][4], float angle);
void		rotation_apply_y(t_fdf_data *data, float rot_m[4][4], float angle);
void		rotation_apply_z(t_fdf_data *data, float rot_m[4][4], float angle);
void		rot_x_eval_matrix(float rot_matrix[4][4], float angle);
void		rot_y_eval_matrix(float rot_matrix[4][4], float angle);
void		rot_z_eval_matrix(float rot_matrix[4][4], float angle);

// Height modifying function
void		z_multiply(t_fdf_data *data, float factor);
void		z_add(t_fdf_data *data, float nb);

// Matrix functions
t_vector3	matrix_applied_to_point(float m[4][4], t_vector3 p);
void		matrix_product(float m[4][4], float n[4][4]);
void		matrix_copy(float dest[4][4], float src[4][4]);
void		matrix_transpose(float m[4][4]);
void		matrix_init_identity(float m[4][4]);

// Render function
int			render(void *data_received);

// Calibration function
void		calibrate(t_fdf_data *data);

// Event handling
void		add_event_handlers(t_fdf_data *data);
void		rotation_handler(t_fdf_data *data, int key);
void		camera_move_handler(t_camera *camera, int key);
void		z_evolution_handler(t_fdf_data *data, int key);
void		switch_projection_handler(t_fdf_data *data);

// Utils
float		f_max(float a, float b);
float		f_min(float a, float b);
void		handle_error(t_fdf_data *data, char *error_message);

#endif
