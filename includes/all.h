/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   all.h                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: frmarinh <frmarinh@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/11/12 15:34:16 by frmarinh          #+#    #+#             */
/*   Updated: 2017/11/12 15:34:28 by frmarinh         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef ALL_H
# define ALL_H

# include <stdio.h>
# include <fcntl.h>
# include <sys/types.h>
# include <sys/uio.h>
# include <unistd.h>
# include <errno.h>
# include <string.h>

# include   "../libft/includes/libft.h"
# define BOOL					int
# define TRUE					1
# define FALSE					0
# define START_GAME				"exec"
# define FILE_SIZE				150
# define BUFFER_SIZE			16384
# define OPEN_ERROR				-1
# define MAX_MAP_SIZE			10024
# define USELESS_LINE			1
# define FIRST_PLAYER			'O'
# define SECOND_PLAYER			'X'

typedef struct			s_point
{
	int					x;
	int					y;
	BOOL				valid;
}						t_point;

typedef struct			s_parser
{
	int					map_x;
	int					map_y;
}						t_parser;

typedef struct			s_map
{
	BOOL				parsed;
	int					**data;
	int					x_size;
	int					y_size;
	int					line;
	char				*raw;
}						t_map;

typedef struct			s_piece
{
	int					**data;
	int					x_size;
	int					y_size;
	char				*raw;
	int					line;
	int					parsed;
	BOOL				solved;
}						t_piece;

typedef struct			s_filler
{
	t_piece				*piece;
	t_parser			*parser;
	t_map				*map;
	BOOL				started;
	int					player_id;
	char				*player_name;
	int					**old_map;
	t_point				*enemy;
}						t_filler;

/*
**	UTILS
*/
void					fill_zero_array(int *array, int len);

/*
**	FILER
*/
t_filler				*alloc_filler(void);
void					start_filler(t_filler *filler, char *received);

/*
**	MAP
*/
void					get_base_map(t_filler *filler, char *raw);
void					fill_map(t_filler *filler);
void					free_map(t_filler *filler);

/*
**	LOGGER
*/
void					log_data(char *raw, int std);

/*
**	PIECE
*/
void					read_piece(t_filler *filler, char *line);
void					free_piece(t_filler *filler);

/*
**	FINDER
*/
void					find_possible_pieces(t_filler *filler);

/*
**	RESOLVER
*/
void					find_valid_points(t_filler *filler, t_point *points, int total_points);

/*
**	RADIUS
*/
void					find_possible_cells_from_radius(int x, int y, int radius, t_filler *filler, int *total_points, t_point *points);

/*
**	POINT
*/
void					fill_zero_point(t_point *point);
void					init_points(t_point *points, int len);
void					find_valid_points(t_filler *filler, t_point *points, int total_points);
void					free_points(t_point **points, int total_points);
#endif
