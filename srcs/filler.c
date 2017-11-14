/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   filler.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: frmarinh <frmarinh@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/11/13 16:08:40 by frmarinh          #+#    #+#             */
/*   Updated: 2017/11/13 16:12:24 by frmarinh         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "all.h"

void			start_filler(t_filler *filler, char *received)
{
	char		**content;

	content = ft_strsplit(received, ' ');
	if (strstr(received, START_GAME) && content != NULL && content[0] != NULL)
	{
		if (content[2] != NULL)
			filler->player_id = (strstr(content[2], "p1")) ? 1 : 2;
		filler->player_name = (content[4] != NULL) ? ft_strdup(content[4]) : NULL;
	}
	else
	{
		printf("Wrong input in stdin\n");
		exit(-1);
	}
	if (filler->player_id <= 0 || filler->player_name == NULL)
	{
		printf("Wrong input in stdin\n");
		exit(-1);
	}
	filler->started = TRUE;
	ft_free_array((void**)content);
}

t_filler		*alloc_filler(void)
{
	t_filler	*filler;

	filler = NULL;
	if (!(filler = (t_filler*)malloc(sizeof(struct s_filler))))
		return (NULL);
	filler->started = FALSE;
	filler->player_id = 0;
	filler->player_name = NULL;
	filler->map = NULL;
	filler->parser = NULL;
	filler->piece = NULL;
	return (filler);
}
