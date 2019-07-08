/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jsarkis <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/07/01 17:42:37 by jsarkis           #+#    #+#             */
/*   Updated: 2019/07/08 11:06:14 by jsarkis          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"
#include "libft/libft.h"
#include <stdio.h>
#include <stdlib.h>
#include <fcntl.h>

void	prep_buff(char **buff)
{
	int	pos;

	pos = ft_find_index(*buff, '\n');
	if (pos == -1)
		*(*buff) = '\0';
	else
		*buff = ft_str_shift(*buff, pos + 1);
}

int		gnl_main_loop(const int fd, char **line, char **buff)
{
	int	i;
	int	end_of_line;
	int	read_ret;

	*line = ft_strnew(1000 * 250);
	i = 0;
	end_of_line = 0;
	while (!end_of_line)
	{
		if (!ft_find_index(*buff, '\0'))
			read_ret = read(fd, *buff, BUFF_SIZE);
		else
			read_ret = BUFF_SIZE;
		*(*buff + read_ret) = '\0';
		if (read_ret)
			i = ft_strncpyi(line, *buff, ft_find_index(*buff, '\n'), i);
		if (read_ret != BUFF_SIZE || ft_find_index(*buff, '\n') != -1)
			end_of_line = 1;
		prep_buff(buff);
	}
	return ((read_ret || i));
}

int		get_next_line(const int fd, char **line)
{
	static t_list	*head;
	t_list			*temp;

	if (!line || fd < 0 || read(fd, NULL, 0) < 0 || BUFF_SIZE < 1)
		return (-1);
	if (!head)
		head = ft_lstnew_content_malloc((BUFF_SIZE + 1), fd);
	temp = head;
	while ((int)temp->content_size != fd && temp->next)
		temp = temp->next;
	if ((int)temp->content_size != fd)
		temp = ft_lstnew_content_malloc((BUFF_SIZE + 1), fd);
	return (gnl_main_loop(fd, line, (char **)&(temp->content)));
	read(0, NULL, 10);
}
