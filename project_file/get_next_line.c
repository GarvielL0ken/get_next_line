/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jsarkis <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/06/10 15:01:17 by jsarkis           #+#    #+#             */
/*   Updated: 2019/06/18 19:24:25 by jsarkis          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"
#include <stdlib.h>
#include <unistd.h>
#include "libft/libft.h"

char	*init(int *i, int *j, char *buff, char **line)
{
	*i = 0;
	*j = BUFF_SIZE;
	if (!buff)
		buff = ft_strnew(BUFF_SIZE + 1);
	*line = ft_strnew(1000 * 1000);
	return (buff);
}

char	*shift_bytes(char *buff, int *j)
{
	int pos;

	pos = ft_find_index(buff, '\n');
	if (ft_find_index(buff, '\0') != BUFF_SIZE && pos == -1)
		*j = BUFF_SIZE;
	if (pos == -1)
		buff[0] = '\0';
	else
	{
		*j = 0;
		pos = pos + 1;
		while (buff[pos + *j] != '\0')
		{
			buff[*j] = buff[pos + *j];
			*j = *j + 1;
		}
		buff[*j] = '\0';
	}
	return (buff);
}

int		calc_return(int read_ret, int i)
{
	if ((read_ret > 0 || i > 0) && BUFF_SIZE > 0)
		return (1);
	else if (read_ret == 0 && BUFF_SIZE > 0)
		return (0);
	else
		return (-1);
}

int		get_next_line(const int fd, char **line)
{
	int			i;
	int			j;
	int			read_ret;
	static char	*buff;

	read_ret = BUFF_SIZE;
	if (!line || fd < 0 || read(fd, NULL, 0) < 0)
		return (-1);
	buff = init(&i, &j, buff, line);
	while (j == BUFF_SIZE && buff[j] != LF && read_ret == BUFF_SIZE)
	{
		if (buff[0] == '\0')
			read_ret = read(fd, buff, BUFF_SIZE);
		buff[read_ret] = '\0';
		j = 0;
		while (buff[j] != LF && j < BUFF_SIZE && buff[j] != '\0')
		{
			*(*line + i) = buff[j];
			i++;
			j++;
		}
		buff = shift_bytes(buff, &j);
	}
	return (calc_return(read_ret, i));
}
