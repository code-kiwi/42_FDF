/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser_info_utils.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mhotting <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/15 17:26:44 by mhotting          #+#    #+#             */
/*   Updated: 2024/03/18 11:41:46 by mhotting         ###   ########.fr       */
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
	info->first_line_parsed = false;
	info->error = false;
}

void	parser_info_add(t_parser_info *info, int z, int color)
{
	t_list					*elt;
	t_parser_info_content	*content;

	if (info == NULL)
		return ;
	content = new_parser_info_content(z, color);
	if (content == NULL)
	{
		info->error = NULL;
		return ;
	}
	elt = ft_lstnew((void *) content);
	if (elt == NULL)
	{
		free(content);
		info->error = NULL;
		return ;
	}
	ft_lstadd_back(&(info->points), elt);
}

t_parser_info_content	*new_parser_info_content(int z, int color)
{
	t_parser_info_content	*content;

	content = (t_parser_info_content *) malloc(sizeof(t_parser_info_content));
	if (content == NULL)
		return (NULL);
	content->z_value = z;
	content->color_value = color;
	return (content);
}

void	parser_info_clear(t_parser_info *info)
{
	if (info == NULL)
		return ;
	ft_lstclear(&info->points, free);
}
