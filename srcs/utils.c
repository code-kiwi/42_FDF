/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mhotting <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/11 09:57:51 by mhotting          #+#    #+#             */
/*   Updated: 2024/04/09 21:14:29 by mhotting         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

float	f_max(float a, float b)
{
	if (a > b)
		return (a);
	return (b);
}

float	f_min(float a, float b)
{
	if (a < b)
		return (a);
	return (b);
}

void	handle_error(t_fdf_data *data, char *error_message)
{
	if (data != NULL)
		clean_remove(data);
	ft_dprintf(STDERR_FILENO, "%s\n", error_message);
	exit(EXIT_FAILURE);
}
