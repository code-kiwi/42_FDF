/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   matrix.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mhotting <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/25 10:14:33 by mhotting          #+#    #+#             */
/*   Updated: 2024/04/11 10:23:36 by mhotting         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

/*
 *	Initialize the given matrix with the identity coefficients
 */
void	matrix_init_identity(float m[4][4])
{
	size_t	i;
	size_t	j;

	i = 0;
	while (i < 4)
	{
		j = 0;
		while (j < 4)
		{
			if (i == j)
				m[i][j] = 1.0f;
			else
				m[i][j] = 0.0f;
			j++;
		}
		i++;
	}
}

/*
 *	Multiplies a matrix (4x4) by a point (4x1) in homogeneous coordinates
 */
t_vector3	matrix_applied_to_point(float m[4][4], t_vector3 p)
{
	t_vector3	result;

	result.x = p.x * m[0][0] + p.y * m[0][1] + p.z * m[0][2] + p.w * m[0][3];
	result.y = p.x * m[1][0] + p.y * m[1][1] + p.z * m[1][2] + p.w * m[1][3];
	result.z = p.x * m[2][0] + p.y * m[2][1] + p.z * m[2][2] + p.w * m[2][3];
	result.w = 1.0f;
	return (result);
}

/*
 *	Transposes the given matrix
 */
void	matrix_transpose(float m[4][4])
{
	float	temp;
	size_t	i;
	size_t	j;

	i = 0;
	while (i < 4)
	{
		j = i;
		while (j < 4)
		{
			temp = m[i][j];
			m[i][j] = m[j][i];
			m[j][i] = temp;
			j++;
		}
		i++;
	}
}

/*
 *	Copies the src matrix coefficients into the src matrix
 */
void	matrix_copy(float dest[4][4], float src[4][4])
{
	size_t	i;
	size_t	j;

	i = 0;
	while (i < 4)
	{
		j = 0;
		while (j < 4)
		{
			dest[i][j] = src[i][j];
			j++;
		}
		i++;
	}
}

/*
 *	Multiplies the m given matrix by the n given matrix
 *	Products's result is then stored into m
 *	Both matrix are 4x4
 */
void	matrix_product(float m[4][4], float n[4][4])
{
	float	temp[4][4];
	size_t	i;
	size_t	j;
	size_t	k;

	matrix_copy(temp, m);
	i = 0;
	while (i < 4)
	{
		j = 0;
		while (j < 4)
		{
			m[i][j] = 0;
			k = 0;
			while (k < 4)
			{
				m[i][j] += temp[i][k] * n[k][j];
				k++;
			}
			j++;
		}
		i++;
	}
}
