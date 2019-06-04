/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jsarkis <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/06/04 12:03:55 by jsarkis           #+#    #+#             */
/*   Updated: 2019/06/04 18:29:45 by jsarkis          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"
#include <stdio.h>
#include <fcntl.h>
#include <stdlib.h>
#include <unistd.h>

int ft_find(char *str, char to_find)
{
	int pos;

	pos = 0;
	while (str[pos] != to_find && str[pos] != '\0')
		pos++;
	if (str[pos] == '\0')
		pos = -1;
	return (pos);
}

int	get_next_line(const int fd, char **line)
{
	int i;
	int pos;
	static char *buff;

	if (!buff)
	{
		buff = (char *)malloc(BUFF_SIZE + 1);
		buff[0] = '\0';
		buff[BUFF_SIZE] = '\0';
	}
	if (buff[0] == '\0')
	{
		read(fd, buff, BUFF_SIZE);
	}
	else
	{
		pos = ft_find(buff, '\n') + 1;
		i = 0;
		while (buff[i + pos] != '\0')
		{
			buff[i] = buff[i + pos];
			i++;
		}
		buff[i] = buff[i+ pos];
	}
	i = 0;
	while (i < BUFF_SIZE && buff[i] != '\n' && buff[i] != '\0')
	{
		*(*line + i) = buff[i];
		i++;
	}
	if (buff[i] == '\0')
		printf("read to buff\n");
	return (0);
}

int	main()
{
	int		fd;
	char	*str;

	fd = open("test", 'r');
	str = (char *)malloc(BUFF_SIZE);
	
	get_next_line(fd, &str);
	printf("%s\n", str);
	get_next_line(fd, &str);
	printf("%s\n", str);
	get_next_line(fd, &str);
	printf("%s\n", str);
}
