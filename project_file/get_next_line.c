/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_ver_4.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jsarkis <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/06/10 15:01:17 by jsarkis           #+#    #+#             */
/*   Updated: 2019/06/10 18:26:57 by jsarkis          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"
#include <stdlib.h>
#include <unistd.h>
#include "libft/ft_find_index.c"

char	*init(char *buff, int *i, int *j, int *read_ret)
{
	*i = 0;
	*j = BUFF_SIZE;
	*read_ret = BUFF_SIZE;
	if (!buff)
	{
		buff = (char *)malloc(BUFF_SIZE + 1);
		buff[BUFF_SIZE] = '\0';
		buff[0] = '\0';
	}
	return (buff);
}

char	*shift_bytes(char *buff, int *j, int pos)
{
	if (pos == -1)
		buff[0] = '\0';
	else
	{
		*j = 0;
		pos++;
		while (buff[pos + *j] != '\0')
		{
			buff[*j] = buff[pos + *j];
			j++;
		}
		buff[*j] = '\0';
	}
	return (buff);
}

int		calc_return(int read_ret, int pos)
{
	if (read_ret == BUFF_SIZE && BUFF_SIZE > 0 && pos != -1)
		return (1);
	else if (read_ret < BUFF_SIZE && read_ret >= 0  && BUFF_SIZE > 0)
		return (0);
	else
		return (-1);
}

int		get_next_line(const int fd, char **line)
{
	int			i;
	int			j;
	int			pos;
	int			read_ret;
	static char	*buff;

	buff = init(buff, &i, &j, &read_ret);
	if (!line || fd < 0)
		return (-1);
	*line = (char *)malloc(256 + 1);
	i = 0;
	while (i++ < 256)
		*(*line + i) = '\0';
	i = 0;
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
		pos = ft_find_index(buff, '\n');
		if (ft_find_index(buff, '\0') != BUFF_SIZE && pos == -1)
			j = BUFF_SIZE;
		buff = shift_bytes(buff, &j, pos);
	}
	return (calc_return(read_ret, pos));
}
