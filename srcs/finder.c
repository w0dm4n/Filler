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

void			find_points(t_point *points, int *total_points, t_filler *filler)
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

void			no_solution(t_filler *filler)
{
	char		*answer;

	if ((answer = ft_strnew(0)) == NULL)
		return;
	asprintf(&answer, "0, 0\n");
	write(1, answer, ft_strlen(answer));

	asprintf(&answer, "No solution found for piece: \n%s\n________________________\n%s\n",
	filler->piece->raw, filler->map->raw);
	log_data(answer, STDIN_FILENO);
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

t_point			*get_close_enemy_from_point(t_point *point, t_point *ennemies, int enemy_len)
{
	int i;
	t_point	*enemy = &ennemies[0];
	int y_diff;
	int d;

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

t_point			*find_closest_from_enemy(t_point *points, int total_points, t_filler *filler)
{
	int			possible_points = filler->map->y_size * filler->map->x_size;
	t_point		enemy_points[possible_points];
	int			enemy_len;
	int			points_len;
	char		*fdp = ft_strnew(0);

	points_len = 0;
	init_points((t_point*)&enemy_points, possible_points);
	int i = 1;
	int d = 0;
	int x = 0;
	t_point *current = NULL;
	int y_diff = 0;
	int x_diff = 0;
	while (i < total_points)
	{
		if (points[i].valid)
		{
			if (filler->enemy)
			{
				y_diff = points[i].y - filler->enemy->y;
				x_diff = points[i].x - filler->enemy->x;
				if (y_diff < 0)
					y_diff = -y_diff;
				if (x_diff < 0)
					x_diff = -x_diff;
				if (d == 0 || y_diff < d || x_diff < x)
				{
					current = &points[i];
					d = y_diff;
					x = x_diff;
				}
			}
		}
		i++;
	}
	return (current);
}

void			send_solution(t_point *point, t_filler *filler)
{
	char		*fdp = ft_strnew(0);
	asprintf(&fdp, "%d, %d\n", point->y, point->x);
	write(1, fdp, ft_strlen(fdp));
	asprintf(&fdp, "Valid point sent: [%d, %d] for piece: \n%s\n________________________\n%s\n",
	point->y, point->x, filler->piece->raw, filler->map->raw);
	log_data(fdp, STDIN_FILENO);
	filler->piece->solved = TRUE;
}

void			find_possible_pieces(t_filler *filler)
{
	int			possible_points = filler->map->y_size * filler->map->x_size;
	int			total_points = 0;
	t_point		points[possible_points];
	t_point		*closest_point;

	closest_point = NULL;
	init_points((t_point*)&points, possible_points);
	find_points((t_point*)&points, &total_points, filler);
	find_valid_points(filler, (t_point*)&points, total_points);
	if (total_points > 0 &&
		(closest_point = find_closest_from_enemy((t_point*)&points, total_points, filler)) != NULL)
	{
		send_solution(closest_point, filler);
	}
	if (!filler->piece->solved)
		no_solution(filler);
	free_map(filler);
	free_piece(filler);
}
