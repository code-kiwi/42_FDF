/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser_parse_line.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mhotting <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/20 11:45:35 by mhotting          #+#    #+#             */
/*   Updated: 2024/04/11 10:40:37 by mhotting         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf_parsing.h"

/*
 *	Counts the elements on a given line
 */
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

/*
 *	Parses all the lines from the given file descriptor in order to get
 *	map dimensions: info->nb_lines and info->nb_line_elts
 *	When an error is encountered, the error flag of the info given structure
 *	is set to true
 *	NB: A map has to be a rectangle and contain at list one line of one element
 */
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

/*
 *	Converts the line characters at the given position into an integer
 *	The line pointer is moved to the end of the parsed integer
 *	When an error is encountered, the error flag of the info given structure
 *	is set to true
 *	Returns the parsed integer
 */
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

/*
 *	Converts the given string to a RGB color value
 *	A valid string has this structure: "^0x[0-9A-F]{6}"
 */
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

/*
 *	Parses a the given line in order to store its information into the map of
 *	the given t_parser_info pointer
 *	When an error is encountered, the info error flag is set to true and the
 *	parsing stops
 */
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
