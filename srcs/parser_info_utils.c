/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser_info_utils.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mhotting <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/15 17:26:44 by mhotting          #+#    #+#             */
/*   Updated: 2024/03/15 17:53:33 by mhotting         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

void	parser_info_init(t_parser_info *info)
{
	if (info == NULL)
		return ;
	info->points = NULL;
	info->nb_lines = 0;
	info->nb_line_elts = 0;
}

t_parser_info_content *new_parser_info_content(int z, char *color)
{
	t_parser_info_content	*content;

	if (color == NULL)
		return (NULL);
	content = (t_parser_info_content *) malloc(sizeof(t_parser_info_content));
	if (content == NULL)
		return (NULL);
	content->z_value = z;
	content->color_value = 0xFFFFFF;
	return (content);
}

void	parser_info_clear(t_parser_info *info)
{
	if (info == NULL)
		return ;
	ft_lstclear(&info->points, free);
}
