/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   resolver.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: frmarinh <frmarinh@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/11/14 22:01:25 by frmarinh          #+#    #+#             */
/*   Updated: 2017/11/14 22:01:32 by frmarinh         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "all.h"

static BOOL			can_fill_piece(t_filler *filler, t_point *point)
{
	int		current_y = point->y;
	int		current_x = point->x;
	int		index_y = 0;
	int		index_x = 0;
	int		touched	= 0;
	t_piece	*piece = filler->piece;
	int		**map = filler->map->data;

	while (index_y < piece->y_size)
	{
		if (current_y >= filler->map->y_size || current_y < 0)
			return (FALSE);
		index_x = 0;
		current_x = point->x;
		while (index_x < piece->x_size)
		{
			if (current_x >= filler->map->x_size || current_x < 0)
				return (FALSE);
			if (map[current_y][current_x] == filler->player_id && piece->data[index_y][index_x] != 0)
				touched++;
			else if (piece->data[index_y][index_x] != 0
				&& map[current_y][current_x] != 0
				&& map[current_y][current_x] != filler->player_id)
				return (FALSE);
			current_x++;
			index_x++;
		}
		current_y++;
		index_y++;
	}
	if (touched == 1)
		return (TRUE);
	else
		return (FALSE);
}

void				find_valid_points(t_filler *filler, t_point *points, int total_points)
{
	int		i;

	i = 0;
	while (i < total_points)
	{
		if (can_fill_piece(filler, &points[i]))
			points[i].valid = TRUE;
		i++;
	}
}
