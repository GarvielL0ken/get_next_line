/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jsarkis <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/06/04 12:03:55 by jsarkis           #+#    #+#             */
/*   Updated: 2019/06/06 12:59:56 by jsarkis          ###   ########.fr       */
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
	if (str[pos] == '\0')
		pos = -1;
	return (pos);
}

int	get_next_line(const int fd, char **line)
{
	int			i;
	int			j;
	int			pos;
	static char	*buff;

	if (!buff)
	{
		buff = (char *)malloc(BUFF_SIZE + 1);
		buff[BUFF_SIZE] = '\0';
		buff[0] = '\0';
	}
	i = 0;
	j = BUFF_SIZE;
	while (j == BUFF_SIZE && buff[j] != '\n')
	{
		if (buff[0] == '\0')
			read(fd, buff, BUFF_SIZE);
		j = 0;
		printf("\n");
		if (buff[0] == '\n')
		{
			j = 0;
			while (j < BUFF_SIZE - 1)
			{
				buff[j] == buff[j + 1];
				j++;
			}
		}
		while (j < BUFF_SIZE)
		{
			if (buff[j] == '\n')
				printf("buff[%d] = \\n\n", j);
			else if (buff[j] == '\0')
				printf("buff[%d] = \\0\n", j);
			else
				printf("buff[%d] = %c\n", j, buff[j]);
			j++;
		}
		j = 0;
		while (buff[j] != '\n' && j < BUFF_SIZE && buff[j] != '\0')
		{
			*(*line + i) = buff[j];
			printf("line[%d] = %c\n", i, *(*line + i));
			i++;
			j++;
		}
		pos = ft_find_index(buff, '\n');
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
	return (0);
}

int	main()
{
	int		fd;
	char	*str_1;
	char	*str_2;
	char	*str_3;

	fd = open("test", 'r');
	str_1 = (char *)malloc(64);
	str_1[63] = '\0';
	str_2 = (char *)malloc(64);
	str_2[63] = '\0';
	str_3 = (char *)malloc(64);
	str_3[63] = '\0';

	get_next_line(fd, &str_1);
	get_next_line(fd, &str_2);
	get_next_line(fd, &str_3);
	printf("\nresult: \n");
	printf("String 1: %s\n", str_1);
	printf("String 2: %s\n", str_2);
	printf("String 3: %s\n", str_3);
	//printf("%s", str_1);
	//printf("%s", str_2);
	//printf("%s", str_3);
}
