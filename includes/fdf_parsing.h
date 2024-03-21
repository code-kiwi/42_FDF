/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fdf_parsing.h                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mhotting <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/20 14:08:38 by mhotting          #+#    #+#             */
/*   Updated: 2024/03/21 11:08:49 by mhotting         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FDF_PARSING_H
# define FDF_PARSING_H

# include "fdf.h"

typedef struct s_parser_info
{
	size_t		nb_lines;
	size_t		nb_line_elts;
	t_point3d	**map;
	bool		error;
}	t_parser_info;

// Parsing functions
bool	parse_input_file(t_fdf_data *data, char *filename);
void	parser_info_init(t_parser_info *info);
void	parser_info_map_free(t_point3d **map, size_t nb_lines);
void	parser_info_init_map(t_parser_info *info);
void	parser_info_add_coords(t_parser_info *info, size_t l, size_t c, int z);
void	parser_info_add_color(t_parser_info *info, size_t l, size_t c, int col);
void	parser_get_counts(t_parser_info *info, int fd);
void	parse_line(t_parser_info *info, char *line, size_t line_index);

#endif
