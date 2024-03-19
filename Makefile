# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: mhotting <marvin@42.fr>                    +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2024/03/04 09:50:18 by mhotting          #+#    #+#              #
#    Updated: 2024/03/19 16:27:00 by mhotting         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

# GENERAL
NAME					=	fdf
CC						=	cc
ifndef NOFLAGS
	CFLAGS				=	-Wall -Werror -Wextra
endif
HFLAGS					=	-I$(HEADERS_DIR) -I$(LIBFT_HEADERS_DIR) -I$(MLX_HEADERS_DIR)
FSFLAGS					=	-fsanitize=address

# HEADERS
HEADERS_DIR				=	includes/
HEADERS_FILES			=	fdf.h
HEADERS					=	$(addprefix $(HEADERS_DIR), $(HEADERS_FILES))

# LIBFT
LIBFT_DIR				=	libft/
LIBFT_FILE				=	libft.a
LIBFT					=	$(addprefix $(LIBFT_DIR), $(LIBFT_FILE))
LIBFT_HEADERS_SUBDIR	=	includes/
LIBFT_HEADERS_DIR		=	$(addprefix $(LIBFT_DIR), $(LIBFT_HEADERS_SUBDIR))
LIBFT_HEADERS_FILE		=	libft.h
LIBFT_HEADERS			=	$(addprefix $(LIBFT_HEADERS_DIR), $(LIBFT_HEADERS_FILE))
LIBFT_FLAGS				=	-L$(LIBFT_DIR) -lft 

# MINILIBX
MLX_DIR					=	minilibx/
MLX_FILE				=	libmlx_Linux.a
MLX						=	$(addprefix $(MLX_DIR), $(MLX_FILE))
MLX_HEADERS_DIR			=	minilibx/
MLX_HEADERS_FILE		=	mlx.h
MLX_HEADERS				=	$(addprefix $(MLX_HEADERS_DIR), $(MLX_HEADER_FILE))
MLX_FLAGS				=	-L$(MLX_DIR) -lmlx_Linux -lXext -lX11

# SOURCES GENERAL
SRCS_MAIN_DIR			=	srcs/
SRCS_FILES				=	fdf.c					\
							parser.c				\
							t_fdf_data_utils.c		\
							t_argb_color_utils.c	\
							t_image_utils.c			\
							draw_pixel.c			\
							draw_line.c				\
							event_handlers.c		\
							utils.c
SRCS					=	$(addprefix $(SRCS_MAIN_DIR), $(SRCS_FILES))

# OBJECTS GENERAL
OBJS_MAIN_DIR			=	objs/
OBJS_FILES				=	$(SRCS_FILES:.c=.o)
OBJS					=	$(addprefix $(OBJS_MAIN_DIR), $(OBJS_FILES))

# DEPENDENCIES
DEPS_MAIN_DIR			=	deps/
DEPS_FILES				=	$(OBJS_FILES:.o=.d)
DEPS					=	$(addprefix $(DEPS_MAIN_DIR), $(DEPS_FILES))

#################################################

# RULES
all: $(NAME)

$(NAME): $(LIBFT) $(MLX) $(OBJS)
	$(CC) $(CFLAGS) $(HFLAGS) $(OBJS) $(LIBFT_FLAGS) $(MLX_FLAGS) -o $@

$(OBJS_MAIN_DIR)%.o: $(SRCS_MAIN_DIR)%.c $(HEADERS) $(LIBFT_HEADERS)
	@mkdir -p $(@D)
	@mkdir -p $(DEPS_MAIN_DIR)$(dir $*)
	$(CC) $(CFLAGS) $(HFLAGS) -MP -MMD -MF $(DEPS_MAIN_DIR)$*.d -c $< -o $@ 

$(LIBFT): FORCE
	make -sC $(LIBFT_DIR)

$(MLX): FORCE
	make -sC $(MLX_DIR) > /dev/null 2>&1

FORCE:

fsanitize: fclean $(LIBFT) $(OBJS)
	$(CC) $(CFLAGS) $(HFLAGS) $(FSFLAGS) $(OBJS) $(LIBFT_FLAGS) -o $(NAME)

-include $(DEPS)

clean:
	rm -rf $(OBJS_MAIN_DIR)
	rm -rf $(DEPS_MAIN_DIR)

clean-libft:
	make -sC $(LIBFT_DIR) clean

clean-mlx:
	make -sC $(MLX_DIR) clean > /dev/null 2>&1

fclean: clean
	rm -f $(NAME)

fclean-libft:
	make -sC $(LIBFT_DIR) fclean

fclean-mlx: clean-mlx

ffclean: fclean fclean-libft fclean-mlx

re: fclean all

rre: ffclean re

.PHONY: all clean fclean re clean-libft fclean-libft clean-mlx fclean-mlx ffclean rre FORCE fsanitize
