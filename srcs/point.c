/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   point.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: frmarinh <frmarinh@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/11/14 21:43:24 by frmarinh          #+#    #+#             */
/*   Updated: 2017/11/14 21:43:31 by frmarinh         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "all.h"

void			fill_zero_point(t_point *point)
{
	point->x = 0;
	point->y = 0;
	point->valid = FALSE;
}

void			init_points(t_point *points, int len)
{
	int			i;

	i = 0;
	while (i < len)
		fill_zero_point(&points[i++]);
}
