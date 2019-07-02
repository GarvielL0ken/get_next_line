/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jsarkis <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/07/01 17:42:37 by jsarkis           #+#    #+#             */
/*   Updated: 2019/07/02 14:53:31 by jsarkis          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"
#include "libft/libft.h"
#include <stdio.h>
#include <stdlib.h>
#include <fcntl.h>

int		get_next_line(const int fd, char **line)
{
	static t_list	*head;
	int				read_ret;
	int				i;
	int				end_of_line;

	if (!line || fd < 0 || read(fd, NULL, 0) < 0 || BUFF_SIZE < 1)
		return (-1);
	if (!head)
	{
		head = (t_list *)malloc(sizeof(t_list));
		head->content = ft_strnew(BUFF_SIZE + 1);
		head->content_size = fd;
	}
	*line = ft_strnew(BUFF_SIZE + 1);
	
	i = 0;
	end_of_line = 0;
	while (!end_of_line)
	{
		read_ret = read(fd, head->content, BUFF_SIZE);
		if (read_ret)
			i = ft_strncpyi(line, head->content, ft_find_index(head->content, '\n'), i);
		if (read_ret != BUFF_SIZE || ft_find_index(head->content, '\n') != -1)
			end_of_line = 1;
	}
	if (read_ret == 0)
		return (0);
	else
		return (1);
}
