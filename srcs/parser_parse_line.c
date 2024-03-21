/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser_parse_line.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mhotting <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/20 11:45:35 by mhotting          #+#    #+#             */
/*   Updated: 2024/03/21 15:11:56 by mhotting         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf_parsing.h"

static size_t	parser_count_line_elts(char *line)
{
	size_t	count;

	if (line == NULL)
		return (0);
	count = 0;
	while (*line != '\0' && *line != '\n')
	{
		while (ft_isspace(*line))
			line++;
		if (*line == '\0' || *line == '\n')
			break ;
		count++;
		while (*line != '\0' && !ft_isspace(*line))
			line++;
	}
	return (count);
}

void	parser_get_counts(t_parser_info *info, int fd)
{
	char	*line;
	size_t	nb_line_elts;

	if (info == NULL || fd < 0)
		info->error = true;
	while (!info->error)
	{
		line = get_next_line(fd);
		if (line == NULL)
			break ;
		nb_line_elts = parser_count_line_elts(line);
		if (info->nb_line_elts == 0)
			info->nb_line_elts = nb_line_elts;
		if (nb_line_elts == 0 || info->nb_line_elts != nb_line_elts)
			info->error = true;
		free(line);
		info->nb_lines += 1;
	}
	if (info->nb_lines == 0 || info->nb_line_elts == 0)
		info->error = true;
	get_next_line(-1);
}

static int	parse_line_z(t_parser_info *info, char **line)
{
	int		z;

	if (info == NULL || line == NULL || *line == NULL)
		return (0);
	if (**line != '+' && **line != '-' && !ft_isdigit(**line))
	{
		info->error = true;
		return (0);
	}
	z = ft_atoi(*line);
	if (**line == '-' || **line == '+')
		(*line)++;
	while (ft_isdigit(**line))
		(*line)++;
	return (z);
}

static int	parse_color(char *str)
{
	int		color;
	size_t	i;

	if (str == NULL || ft_strstr(str, "0x") != str)
		return (COLOR_DEFAULT);
	str += 2;
	i = 0;
	while (i < 6 && ft_strchr(UPPER_HEX_BASE, str[i]) != NULL)
		i++;
	color = ft_atoi_base(str, UPPER_HEX_BASE);
	return (color);
}

void	parse_line(t_parser_info *info, char *line, size_t line_index)
{
	int		z_read;
	int		color_read;
	size_t	col_index;

	col_index = 0;
	while (*line != '\0' && *line != '\n' && !info->error)
	{
		while (ft_isspace(*line))
			line++;
		if (*line == '\0' || *line == '\n')
			break ;
		z_read = parse_line_z(info, &line);
		if (info->error)
			break ;
		color_read = COLOR_DEFAULT;
		if (*line == COLOR_SEPARATOR)
			color_read = parse_color(++line);
		else if (*line != '\0' && !ft_isspace(*line))
			info->error = true;
		parser_info_add_coords(info, line_index, col_index, z_read);
		parser_info_add_color(info, line_index, col_index, color_read);
		while (*line != '\0' && !ft_isspace(*line))
			line++;
		col_index++;
	}
}
