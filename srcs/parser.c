/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mhotting <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/15 16:12:12 by mhotting          #+#    #+#             */
/*   Updated: 2024/03/15 17:53:41 by mhotting         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

t_vector3	**parse_input_file(char *filename)
{
	t_vector3		**map;
	t_parser_info	*parser_info;
	int			fd;

	if (filename == NULL)
		return (NULL);
	fd = open(filename, O_RDONLY);
	if (fd == -1)
		return (NULL);
	parser_info_init(&parser_info);
	get_file_info(&parser_info, fd);
	map = parser_info_to_map(&parser_info);
	parser_info_clear(&parser_info);
	return (map);
}
