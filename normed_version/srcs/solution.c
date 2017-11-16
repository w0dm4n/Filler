/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   solution.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: frmarinh <frmarinh@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/11/16 01:28:07 by frmarinh          #+#    #+#             */
/*   Updated: 2017/11/16 01:28:12 by frmarinh         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "all.h"

void			no_solution(t_filler *filler)
{
	char		*answer;

	if ((answer = ft_strnew(0)) == NULL)
		return ;
	asprintf(&answer, "0, 0\n");
	write(1, answer, ft_strlen(answer));
	asprintf(&answer, "No solution found for piece: "
	"\n%s\n________________________\n%s\n",
	filler->piece->raw, filler->map->raw);
	log_data(answer, STDIN_FILENO);
}

void			send_solution(t_point *point, t_filler *filler)
{
	char		*msg;

	if ((msg = ft_strnew(0)) == NULL)
		return ;
	asprintf(&msg, "%d, %d\n", point->y, point->x);
	write(1, msg, ft_strlen(msg));
	asprintf(&msg, "Valid point sent: [%d, %d] for piece: "
	"\n%s\n________________________\n%s\n",
	point->y, point->x, filler->piece->raw, filler->map->raw);
	log_data(msg, STDIN_FILENO);
	filler->piece->solved = TRUE;
}
