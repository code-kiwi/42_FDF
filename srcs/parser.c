/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mhotting <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/15 16:12:12 by mhotting          #+#    #+#             */
/*   Updated: 2024/03/18 16:07:30 by mhotting         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

bool	get_file_info(t_parser_info *info, int fd)
{
	char	*line;

	if (fd == -1 || info == NULL)
		return (false);
	while (!info->error)
	{
		line = get_next_line(fd);
		if (line == NULL)
			break ;
		info->nb_lines++;
		if (!info->first_line_parsed)
			parse_first_line(info, line);
		parse_line(info, line);
		free(line);
	}
	if (
		info->error
		|| ft_lstsize(info->points) != info->nb_lines * info->nb_line_elts
	)
		return (false);
	return (true);
}

t_vector3	**parse_input_file(char *filename)
{
	t_vector3		**map;
	t_parser_info	info;
	int				fd;

	if (filename == NULL)
		return (NULL);
	fd = open(filename, O_RDONLY);
	if (fd == -1)
		return (NULL);
	parser_info_init(&info);
	if (!get_file_info(&info, fd))
	{
		printf("MAP ERROR\n");
		parser_info_clear(&info);
		return (NULL);
	}
	t_list	*lst;
	lst = info.points;
	size_t	i = 0;
	t_parser_info_content *content;
	while (lst!= NULL)
	{
		content = (t_parser_info_content *)lst->content;
		printf("POINT: %zu / %d - %d\n", i++, content->z_value, content->color_value);
		lst = lst->next;
	}
	map = NULL;
	//map = parser_info_to_map(&parser_info);
	parser_info_clear(&info);
	return (map);
}
