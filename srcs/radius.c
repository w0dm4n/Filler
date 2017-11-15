/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   radius.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: frmarinh <frmarinh@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/11/14 19:00:16 by frmarinh          #+#    #+#             */
/*   Updated: 2017/11/14 19:00:22 by frmarinh         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "all.h"

void		get_up_left_cells(int x, int y, int radius, t_filler *filler, t_point *points, int *count)
{
	int			index_y = 0;
	int			index_x = 0;
	int			current_y = y;
	int			current_x = x;

	while (index_y < radius && current_y > 0)
	{
		index_x = 0;
		current_x = x;
		while (index_x < radius && current_x > 0)
		{
			if (filler->map->data[current_y][current_x] == 0)
			{
				points[*count].y = current_y;
				points[*count].x = current_x;
				*count += 1;
			}
			current_x--;
			index_x++;
		}
		current_y--;
		index_y++;
	}
}

void		get_up_right_cells(int x, int y, int radius, t_filler *filler, t_point *points, int *count)
{
	int			index_y = 0;
	int			index_x = 0;
	int			current_y = y;
	int			current_x = x;

	while (index_y < radius && current_y > 0)
	{
		index_x = 0;
		current_x = x;
		while (index_x < radius && current_x > 0)
		{
			if (filler->map->data[current_y][current_x] == 0)
			{
				points[*count].y = current_y;
				points[*count].x = current_x;
				*count += 1;
			}
			current_x++;
			index_x++;
		}
		current_y--;
		index_y++;
	}
}

void		get_below_left_cells(int x, int y, int radius, t_filler *filler, t_point *points, int *count)
{
	int			index_y = 0;
	int			index_x = 0;
	int			current_y = y + 1;
	int			current_x = x;

	while (index_y < radius && current_y < filler->map->y_size)
	{
		index_x = 0;
		current_x = x;
		while (index_x < radius && current_x < filler->map->x_size)
		{
			if (filler->map->data[current_y][current_x] == 0)
			{
				points[*count].y = current_y;
				points[*count].x = current_x;
				*count += 1;
			}
			current_x--;
			index_x++;
		}
		current_y++;
		index_y++;
	}
}

void		get_below_right_cells(int x, int y, int radius, t_filler *filler, t_point *points, int *count)
{
	int			index_y = 0;
	int			index_x = 0;
	int			current_y = y + 1;
	int			current_x = x;
	char		*slt = ft_strnew(0);

	while (index_y < radius && current_y < filler->map->y_size)
	{
		index_x = 0;
		current_x = x;
		while (index_x < radius && current_x < filler->map->x_size)
		{
			if (filler->map->data[current_y][current_x] == 0)
			{
				points[*count].y = current_y;
				points[*count].x = current_x;
				*count += 1;
			}
			current_x++;
			index_x++;
		}
		current_y++;
		index_y++;
	}
}

void			find_possible_cells_from_radius(int x, int y, int radius, t_filler *filler, int *total_points, t_point *points)
{
	get_up_left_cells(x, y, radius, filler, points, total_points);
	get_up_right_cells(x, y, radius, filler, points, total_points);
	get_below_left_cells(x, y, radius, filler, points, total_points);
	get_below_right_cells(x, y, radius, filler, points, total_points);
	// y = 0;
	// x = 0;
	// while (y < filler->map->y_size)
	// {
	// 	x = 0;
	// 	while (x < filler->map->x_size)
	// 	{
	// 		if (filler->map->data[y][x] == 0)
	// 		{
	// 			points[*total_points].y = y;
	// 			points[*total_points].x = x;
	// 			*total_points += 1;
	// 		}
	// 		x++;
	// 	}
	// 	y++;
	// }
	find_valid_points(filler, points, *total_points);
}
