/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: frmarinh <frmarinh@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/11/13 17:09:47 by frmarinh          #+#    #+#             */
/*   Updated: 2017/11/13 17:09:51 by frmarinh         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "all.h"

void				free_map(t_filler *filler)
{
	int		i;

	i = 0;
	if (filler->map)
	{
		while (i < filler->map->y_size)
			free(filler->map->data[i++]);
		free(filler->map->data);
		if (filler->map->raw)
			ft_strdel(&filler->map->raw);
		free(filler->map);
		filler->map = NULL;
	}
}

static void			fill_zero_map(t_map *map)
{
	int		i;

	i = 0;
	while (i < map->y_size)
		fill_zero_array(map->data[i++], map->x_size);
}

void				alloc_map(t_filler *filler, int x, int y)
{
	int		i;

	i = 0;
	if (!(filler->map = (t_map*)malloc(sizeof(struct s_map))))
		return;
	filler->map->line = 0;
	filler->map->parsed = FALSE;
	if ((filler->map->raw = ft_strnew(0)) == NULL)
		return ;
	if (x > 0 && x < MAX_MAP_SIZE && y > 0 && y < MAX_MAP_SIZE)
	{
		filler->map->x_size = x;
		filler->map->y_size = y;
		if (!(filler->map->data = (int**)malloc(sizeof(int**) * filler->map->y_size)))
			return;
		while (i < filler->map->y_size)
		{
			if (!(filler->map->data[i++] = (int*)malloc(sizeof(int*) * filler->map->x_size)))
				return;
		}
		fill_zero_map(filler->map);
	}
	else
	{
		printf("Wrong input in stdin\n");
		exit(-1);
	}
}

void				get_base_map(t_filler *filler, char *raw)
{
	char	**data;

	if ((data = ft_strsplit(raw, ' ')) != NULL && data[1] && data[2])
		alloc_map(filler, ft_atoi(data[2]), ft_atoi(data[1]));
	else
	{
		printf("Wrong input in stdin\n");
		exit(-1);
	}
}

static void			parse_x_value(char *line, t_map *map, int y_pos)
{
	int x_pos;

	x_pos = 0;
	if (y_pos < map->y_size)
	{
		while (x_pos < map->x_size)
		{
			if (line[x_pos] == '.')
				map->data[y_pos][x_pos] = 0;
			else if (line[x_pos] == FIRST_PLAYER)
				map->data[y_pos][x_pos] = 1;
			else if (line[x_pos] == SECOND_PLAYER)
				map->data[y_pos][x_pos] = 2;
			x_pos++;
		}
	}
}

void				fill_map(t_filler *filler)
{
	t_map		*map;
	char		**lines;
	int			i;
	char		**line;
	int			y_pos;

	map = filler->map;
	map->parsed = TRUE;
	map->line = 0;
	i = 1;
	line = NULL;
	y_pos = 0;
	fill_zero_map(filler->map);
	if ((lines = ft_strsplit(map->raw, '\n')) != NULL)
	{
		while (lines[i])
		{
			if ((line = ft_strsplit(lines[i], ' ')) != NULL)
			{
				if (line[1])
					parse_x_value(line[1], map, y_pos++);
				ft_free_array((void**)line);
			}
			i++;
		}
		ft_free_array((void**)lines);
	}
}
