/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mhotting <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/11 09:57:51 by mhotting          #+#    #+#             */
/*   Updated: 2024/03/11 12:36:01 by mhotting         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

void	handle_error(t_fdf_data *data, char *error_message)
{
	if (data != NULL)
		clean_remove(data);
	ft_dprintf(STDERR_FILENO, "%s\n", error_message);
	exit(EXIT_FAILURE);
}
