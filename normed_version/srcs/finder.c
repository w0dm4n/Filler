/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   finder.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: frmarinh <frmarinh@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/11/14 21:59:21 by frmarinh          #+#    #+#             */
/*   Updated: 2017/11/14 21:59:23 by frmarinh         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "all.h"

void			find_points(t_point *points, int *total_points,
	t_filler *filler)
{
	int		y;
	int		x;

	y = 0;
	x = 0;
	while (y < filler->map->y_size)
	{
		x = 0;
		while (x < filler->map->x_size)
		{
			if (filler->map->data[y][x] == 0 ||
				filler->map->data[y][x] == filler->player_id)
			{
				points[*total_points].y = y;
				points[*total_points].x = x;
				*total_points += 1;
			}
			x++;
		}
		y++;
	}
}

void			get_enemy_points(t_point *points, t_filler *filler, int *len)
{
	int		y;
	int		x;

	y = 0;
	x = 0;
	while (y < filler->map->y_size)
	{
		x = 0;
		while (x < filler->map->x_size)
		{
			if (filler->map->data[y][x] != 0
				&& filler->map->data[y][x] != filler->player_id)
			{
				points[*len].y = y;
				points[*len].x = x;
				*len += 1;
			}
			x++;
		}
		y++;
	}
}

#define ENEMY t_point		*enemy = &ennemies[0]

t_point			*get_close_enemy_from_point(t_point *point, t_point *ennemies,
	int enemy_len)
{
	int			i;
	int			y_diff;
	int			d;

	ENEMY;
	i = 0;
	y_diff = 0;
	d = 0;
	while (i < enemy_len)
	{
		y_diff = ennemies[i].y - point->y;
		if (y_diff < 0)
			y_diff = -y_diff;
		if (d == 0 || y_diff < d)
		{
			enemy = &ennemies[i];
		}
	}
	return (enemy);
}

#define VARS_3 int possible_points = filler->map->y_size * filler->map->x_size
#define VARS_2 int enemy_len = 0;int points_len = 0; VARS_3
#define VARS_0 int y_diff = 0; int x_diff = 0; VARS_2
#define VARS int i = 1; int d = 0; int x = 0; t_point *current = NULL; VARS_0
#define SET_DIFF current = &points[i]; d = y_diff; x = x_diff
#define NEGATIVE_0 if (y_diff < 0) y_diff = -y_diff
#define NEGATIVE_1 if (x_diff < 0) x_diff = -x_diff;

t_point			*find_closest_from_enemy(t_point *points, int total_points,
	t_filler *filler)
{
	t_point		enemy_points[filler->map->y_size * filler->map->x_size];

	VARS;
	init_points((t_point*)&enemy_points, possible_points);
	while (i < total_points)
	{
		if (points[i].valid)
		{
			if (filler->enemy)
			{
				y_diff = points[i].y - filler->enemy->y;
				x_diff = points[i].x - filler->enemy->x;
				NEGATIVE_0;
				NEGATIVE_1;
				if (d == 0 || y_diff < d || x_diff < x)
				{
					SET_DIFF;
				}
			}
		}
		i++;
	}
	return (current);
}

#define VARS_10 (t_point*)&points, total_points, filler

void			find_possible_pieces(t_filler *filler)
{
	int			possible_points;
	int			total_points;
	t_point		points[filler->map->y_size * filler->map->x_size];
	t_point		*closest_point;

	possible_points = filler->map->y_size * filler->map->x_size;
	total_points = 0;
	closest_point = NULL;
	init_points((t_point*)&points, possible_points);
	find_points((t_point*)&points, &total_points, filler);
	find_valid_points(filler, (t_point*)&points, total_points);
	if (total_points > 0 &&
		(closest_point = find_closest_from_enemy(VARS_10)) != NULL)
	{
		send_solution(closest_point, filler);
	}
	if (!filler->piece->solved)
		no_solution(filler);
	free_map(filler);
	free_piece(filler);
}
