/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   enemy.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: frmarinh <frmarinh@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/11/16 01:54:42 by frmarinh          #+#    #+#             */
/*   Updated: 2017/11/16 01:54:47 by frmarinh         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "all.h"

void				get_first_enemy(t_filler *filler)
{
	int		y;
	int		x;

	x = 0;
	y = 0;
	while (y < filler->map->y_size)
	{
		x = 0;
		while (x < filler->map->x_size)
		{
			if (filler->map->data[y][x] != 0 &&
				filler->map->data[y][x] != filler->player_id)
			{
				if ((filler->enemy =
					(t_point*)malloc(sizeof(struct s_point))) != NULL)
				{
					filler->enemy->y = y;
					filler->enemy->x = x;
				}
			}
			x++;
		}
		y++;
	}
}

void				find_new_enemy(t_filler *filler)
{
	int y;
	int x;

	y = 0;
	x = 0;
	while (y < filler->map->y_size)
	{
		x = 0;
		while (x < filler->map->x_size)
		{
			if (filler->map->data[y][x] != filler->old_map[y][x]
				&& filler->map->data[y][x] != filler->player_id)
			{
				if ((filler->enemy =
					(t_point*)malloc(sizeof(struct s_point))) != NULL)
				{
					filler->enemy->y = y;
					filler->enemy->x = x;
				}
			}
			x++;
		}
		y++;
	}
}
