/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jsarkis <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/06/04 12:03:55 by jsarkis           #+#    #+#             */
/*   Updated: 2019/06/10 15:02:47 by jsarkis          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"
#include <stdio.h>
#include <fcntl.h>
#include <stdlib.h>
#include <unistd.h>

int ft_find_index(char *str, char to_find)
{
	int pos;

	pos = 0;
	while (str[pos] != to_find && str[pos] != '\0')
		pos++;
	if (str[pos] == '\0' && to_find != '\0')
		pos = -1;
	return (pos);
}

void	ft_print_buff_char(int i, char c, const char *buff_name)
{
	printf("%s[%d] = ", buff_name, i);
	if (c == LF)
		printf("LF\n");
	else if (c == '\0')
		printf("\\0\n");
	else
		printf("%c\n", c);
}

void	ft_print_buff(char *buff)
{
	int i;

	i = 0;
	while (i < BUFF_SIZE)
	{
		ft_print_buff_char(i, buff[i], "buff");
		i++;
	}
}

int	get_next_line(const int fd, char **line)
{
	int			i;
	int			j;
	int			pos;
	int			read_ret;
	static char	*buff;

	if (!buff)
	{
		buff = (char *)malloc(BUFF_SIZE + 1);
		buff[BUFF_SIZE] = '\0';
		buff[0] = '\0';
	}
	i = 0;
	j = BUFF_SIZE;
	read_ret = BUFF_SIZE;
	while (j == BUFF_SIZE && buff[j] != LF && read_ret == BUFF_SIZE)
	{
		if (buff[0] == '\0')
			read_ret = read(fd, buff, BUFF_SIZE);
		buff[read_ret] = '\0';
		j = 0;
		j = 0;
		while (buff[j] != LF && j < BUFF_SIZE && buff[j] != '\0')
		{
			*(*line + i) = buff[j];
			ft_print_buff_char(i, *(*line + i), "line");
			i++;
			j++;
		}
		pos = ft_find_index(buff, '\n');
		if (ft_find_index(buff, '\0') != BUFF_SIZE && pos == -1)
			j = BUFF_SIZE;
		if (pos == -1)
			buff[0] = '\0';
		else
		{
			j = 0;
			pos++;
			while (buff[pos + j] != '\0')
			{
				buff[j] = buff[pos + j];
				j++;
			}
			buff[j] = '\0';
		}
	}
	if (read_ret == BUFF_SIZE && BUFF_SIZE > 0 && pos != -1)
		read_ret = 1;
	else if (read_ret < BUFF_SIZE && BUFF_SIZE > 0)
		read_ret = 0;
	else
		read_ret = -1;
	return (read_ret);
}
