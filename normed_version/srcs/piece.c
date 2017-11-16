/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   piece.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: frmarinh <frmarinh@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/11/13 22:15:13 by frmarinh          #+#    #+#             */
/*   Updated: 2017/11/13 22:15:19 by frmarinh         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "all.h"

t_piece		*alloc_piece(void)
{
	t_piece		*piece;

	if (!(piece = (t_piece*)malloc(sizeof(struct s_piece))))
		return (NULL);
	if (!(piece->raw = ft_strnew(0)))
		return (NULL);
	piece->x_size = 0;
	piece->y_size = 0;
	piece->line = 0;
	piece->data = NULL;
	piece->solved = FALSE;
	return (piece);
}

#define FN_1 static void		fill_zero_piece(t_piece *piece) {
#define FN_2 int i = 0; while (i < piece->y_size)
#define FN_3 fill_zero_array(piece->data[i++], piece->x_size); }
#define FUNC FN_1 FN_2 FN_3

FUNC;

#define PIECE filler->piece

void		parse_piece(t_filler *filler, char *line)
{
	char	**data;
	int		i;

	i = 0;
	if ((data = ft_strsplit(line, ' ')) == NULL)
		return ;
	filler->piece->parsed = FALSE;
	filler->piece->x_size = (data[2]) ? ft_atoi(data[2]) : 0;
	filler->piece->y_size = (data[1]) ? ft_atoi(data[1]) : 0;
	if (PIECE->x_size <= 0 || filler->piece->x_size > filler->map->x_size \
		|| PIECE->y_size <= 0 || filler->piece->y_size > filler->map->y_size)
	{
		printf("Wrong piece in stdin (%d,%d)\n", PIECE->x_size, PIECE->y_size);
		exit(-1);
	}
	if (!(PIECE->data = (int**)malloc(sizeof(int**) * filler->piece->y_size)))
		return ;
	while (i < filler->piece->y_size)
	{
		if (!(PIECE->data[i++] = (int*)malloc(sizeof(int*) * PIECE->x_size)))
			return ;
	}
	fill_zero_piece(filler->piece);
}

void		free_piece(t_filler *filler)
{
	int		i;

	i = 0;
	if (filler->piece)
	{
		while (i < filler->piece->y_size)
			free(filler->piece->data[i++]);
		free(filler->piece->data);
		if (filler->piece->raw)
			ft_strdel(&filler->piece->raw);
		free(filler->piece);
		filler->piece = NULL;
	}
}

void		parse_x_value(char *line, int y_pos, t_piece *piece)
{
	int x_pos;

	x_pos = 0;
	while (x_pos < piece->x_size)
	{
		if (line[x_pos] == '*')
			piece->data[y_pos][x_pos] = 1;
		x_pos++;
	}
}

#define T_1 if (filler->piece != NULL) filler->piece->line++
#define VARS char **lines = NULL; int i = 0;

void		read_piece(t_filler *filler, char *line)
{
	VARS;
	if (filler->piece == NULL)
		if ((filler->piece = alloc_piece()) == NULL)
			return ;
	if (filler->piece->line == 0)
		parse_piece(filler, line);
	else if (filler->piece->line < filler->piece->y_size)
		asprintf(&filler->piece->raw, "%s\n%s", filler->piece->raw, line);
	else if (!filler->piece->parsed)
	{
		asprintf(&filler->piece->raw, "%s\n%s", filler->piece->raw, line);
		if ((lines = ft_strsplit(filler->piece->raw, '\n')))
		{
			while (lines[i])
			{
				parse_x_value(lines[i], i, filler->piece);
				i++;
			}
			ft_free_array((void**)lines);
		}
		find_possible_pieces(filler);
	}
	T_1;
}
