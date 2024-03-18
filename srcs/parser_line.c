/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser_line.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mhotting <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/18 14:42:12 by mhotting          #+#    #+#             */
/*   Updated: 2024/03/18 16:07:24 by mhotting         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

size_t	parser_count_line_elts(char *line)
{
	size_t	count;

	if (line == NULL)
		return (0) ;
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

void	parse_first_line(t_parser_info *info, char *line)
{
	size_t	count;

	if (info == NULL || line == NULL)
		return ;
	count = parser_count_line_elts(line);
	if (count == 0)
		info->error = true;
	info->nb_line_elts = count;
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
	if (i != 6)
		return (COLOR_DEFAULT);
	color = ft_atoi_base(str, UPPER_HEX_BASE);
	return (color);
}

void	parse_line(t_parser_info *info, char *line)
{
	int	z_read;
	int	color_read;
	
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
		{
			info->error = true;
			break ;
		}
		parser_info_add(info, z_read, color_read);
		while (*line != '\0' && !ft_isspace(*line))
			line++;
	}
}
