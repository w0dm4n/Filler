/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: frmarinh <frmarinh@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/11/13 17:16:46 by frmarinh          #+#    #+#             */
/*   Updated: 2017/11/13 17:16:52 by frmarinh         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "all.h"

BOOL			get_map_size(t_parser *parser, char *raw)
{
	char		**line;

	line = ft_strsplit(raw, '\n');
	if (line)
	{
		log_data(raw, STDIN_FILENO);
		return (TRUE);
	}
	return (FALSE);
}

t_parser		*alloc_parser(void)
{
	t_parser	*parser;

	if (!(parser = (t_parser*)malloc(sizeof(struct s_parser))))
		return (NULL);
	parser->map_x = 0;
	parser->map_y = 0;
	return (parser);
}

t_parser		*parser(char *raw)
{
	t_parser		*parser;

	if (!(parser = alloc_parser()))
		return (NULL);
	if (!get_map_size(parser, raw))
		return (NULL);
	return (parser);
}
