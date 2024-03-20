/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mhotting <mhotting@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/19 16:27:52 by mhotting          #+#    #+#             */
/*   Updated: 2024/03/20 14:15:18 by mhotting         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf_parsing.h"

static void	parser_get_map(t_parser_info *info, int fd)
{
	size_t	line_index;
	char	*line;

	if (
		info == NULL || fd < 0
		|| info->nb_lines == 0 || info->nb_line_elts == 0
	)
		return ;
	parser_info_init_map(info);
	if (info->error || info->map == NULL)
		return ;
	line_index = 0;
	while (!info->error)
	{
		line = get_next_line(fd);
		if (line == NULL)
			break ;
		parse_line(info, line, line_index);
		line_index++;
		free(line);
	}
	get_next_line(-1);
}

bool	parser_is_valid_filename(char *filename)
{
	char	*str;

	if (filename == NULL)
		return (false);
	str = ft_strstr(filename, FDF_FILE_EXTENSION);
	if (str == NULL || ft_strlen(str) != FDF_FILE_EXTENSION_LEN)
		return (false);
	return (true);
}

bool	parse_input_file(t_fdf_data *data, char *filename)
{
	int				fd;
	t_parser_info	info;

	if (data == NULL || filename == NULL || !parser_is_valid_filename(filename))
		return (false);
	fd = open(filename, O_RDONLY);
	if (fd == -1)
		return (false);
	parser_info_init(&info);
	parser_get_counts(&info, fd);
	if (close(fd) == -1 || info.error)
		return (false);
	fd = open(filename, O_RDONLY);
	if (fd == -1)
		return (false);
	parser_get_map(&info, fd);
	if (close(fd) == -1 || info.error)
	{
		parser_info_map_free(info.map, info.nb_lines);
		return (false);
	}
	data->nb_lines = info.nb_lines;
	data->nb_line_elts = info.nb_line_elts;
	data->map = info.map;
	return (true);
}
