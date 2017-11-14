/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   resolver.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: frmarinh <frmarinh@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/11/14 02:50:30 by frmarinh          #+#    #+#             */
/*   Updated: 2017/11/14 02:50:35 by frmarinh         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "all.h"

void			resolve(t_filler *filler)
{
	int y = 0;
	int x = 0;
	char *fdp = ft_strnew(0);
	while (y < filler->map->y_size)
	{
		x = 0;
		while (x < filler->map->x_size)
		{
			if (filler->map->data[y][x] == 2)
			{
				asprintf(&fdp, "19 %d\n", x - 3);
				write(1, fdp, ft_strlen(fdp));
				log_data(fdp, STDIN_FILENO);
			}
			x++;
		}
		y++;
	}
	free_piece(filler);
}
