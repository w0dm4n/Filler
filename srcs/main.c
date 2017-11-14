/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: frmarinh <frmarinh@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/11/12 15:32:22 by frmarinh          #+#    #+#             */
/*   Updated: 2017/11/12 15:33:06 by frmarinh         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "all.h"
#include <errno.h>

int		main(int argc, char **argv)
{
	char		*line;
	char		buffer[BUFFER_SIZE];
	int			res;
	t_filler	*filler;

	res = 0;
	if ((filler = alloc_filler()) == NULL)
		return (-1);
	ft_memset((void*)&buffer, 0, (BUFFER_SIZE - 1));
	while ((get_next_line(STDIN_FILENO, &line)) > 0)
	{
		if (filler->started && !filler->map)
			get_base_map(filler, line);
		else if (filler->started)
		{
			if (!filler->map->parsed && filler->map->line < (filler->map->y_size + USELESS_LINE))
			{
				asprintf(&filler->map->raw, "%s\n%s", filler->map->raw, line);
				filler->map->line++;
			}
			else
			{
				if (!filler->map->parsed)
					fill_map(filler);
				read_piece(filler, line);
			}
		}
		else
			start_filler(filler, line);
		ft_strdel(&line);
	}
	return (0);
}
