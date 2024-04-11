/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mhotting <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/11 09:57:51 by mhotting          #+#    #+#             */
/*   Updated: 2024/04/11 11:14:33 by mhotting         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

/*
 *	Returns the maximum between two float numbers
 */
float	f_max(float a, float b)
{
	if (a > b)
		return (a);
	return (b);
}

/*
 *	Returns the minimum between two float numbers
 */
float	f_min(float a, float b)
{
	if (a < b)
		return (a);
	return (b);
}

/*
 *	Destroys properly the given data and prints a message on STDERR
 *	Then exits the program with an error status code
 */
void	handle_error(t_fdf_data *data, char *error_message)
{
	if (data != NULL)
		clean_remove(data);
	ft_dprintf(STDERR_FILENO, "%s\n", error_message);
	exit(EXIT_FAILURE);
}
