/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   logger.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: frmarinh <frmarinh@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/11/13 17:28:25 by frmarinh          #+#    #+#             */
/*   Updated: 2017/11/13 17:28:30 by frmarinh         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "all.h"

void		log_data(char *raw, int std)
{
	static int			i = 0;
	char				file[FILE_SIZE];
	int					fd;

	fd = 0;
	ft_memset((char*)&file, 0, (FILE_SIZE - 1));
	sprintf(file, "/Users/frmarinh/Desktop/work/filler/logs/%s_%s", (std == STDIN_FILENO) ? "in" : "out", ft_itoa(i++));
	if ((fd = open((char*)&file, O_RDWR | O_CREAT, 0666)) != OPEN_ERROR)
		write(fd, raw, ft_strlen(raw));
	else
		printf("%s %s\n", strerror(errno),(char*)&file);
}
