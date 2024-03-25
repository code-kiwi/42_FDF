/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   matrix.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mhotting <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/25 10:14:33 by mhotting          #+#    #+#             */
/*   Updated: 2024/03/25 10:29:21 by mhotting         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

t_vector3	matrix_applied_to_point(float m[4][4], t_vector3 p)
{
	t_vector3	result;

	result.x = p.x * m[0][0] + p.y * m[0][1] + p.z * m[0][2] + p.w * m[0][3];
	result.y = p.x * m[1][0] + p.y * m[1][1] + p.z * m[1][2] + p.w * m[1][3];
	result.z = p.x * m[2][0] + p.y * m[2][1] + p.z * m[2][2] + p.w * m[2][3];
	result.w = 1.0f;
	return (result);
}
