/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mhotting <mhotting@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/19 16:27:52 by mhotting          #+#    #+#             */
/*   Updated: 2024/03/19 17:51:07 by mhotting         ###   ########.fr       */
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

bool	parser_count_lines(t_parser_info *info, int fd)
{
	char	*line;
	bool	first_line_read;

	if (info == NULL || fd < 0)
		return (false);
	first_line_read = false;
	while (true)
	{
		line = get_next_line(fd);
		if (line == NULL)
		{
			get_next_line(-1);
			break ;
		}
		if (!first_line_read)
		{
			first_line_read = true;
			info->nb_line_elts = parser_count_line_elts(line);
		}
		free(line);
		info->nb_lines += 1;
	}
	if (info->nb_lines == 0 || info->nb_line_elts == 0)
		return (false);
	return (true);
}

void	parser_info_init(t_parser_info *info)
{
	if (info == NULL)
		return ;
	info->nb_lines = 0;
	info->nb_line_elts = 0;
	info->map = NULL;
}

t_vector3	**parse_input_file(char *filename)
{
	int				fd;
	t_parser_info	info;

	if (filename == NULL)
		return (NULL);
	fd = open(filename, O_RDONLY);
	if (fd == -1)
		return (NULL);
	parser_info_init(&info);
	parser_count_lines(&info, fd);
	if (close(fd) == -1)
		return (NULL);
	printf("NB_LINES: %zu\n", info.nb_lines);
	printf("NB_ELT_LINE: %zu\n", info.nb_line_elts);
	return (info.map);
}
