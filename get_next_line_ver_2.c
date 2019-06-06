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
		read(fd, buff, BUFF_SIZE);
	i = 0;
	while (i < BUFF_SIZE && buff[i] != '\n')
	{
		*(*line + i) = buff[i];
		i++;
	}
	if (ft_find_index(buff, '\n') == -1)
		buff[0] = '\0';
}

int	main()
{
	int		fd;
	char	*str_1;
	char	*str_2;
	char	*str_3;

	fd = open("test", 'r');
	str_1 = (char *)malloc(BUFF_SIZE + 1);
	str_2 = (char *)malloc(BUFF_SIZE + 1);
	str_3 = (char *)malloc(BUFF_SIZE + 1);

	get_next_line(fd, &str_1);
	get_next_line(fd, &str_2);
	get_next_line(fd, &str_3);
	printf("result: \n");
	printf("String 1: %s\n", str_1);
	printf("String 2: %s\n", str_2);
	printf("String 3: %s\n", str_3);
	printf("%s", str_1);
	printf("%s", str_2);
	printf("%s", str_3);
}
