/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.h                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jsarkis <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/07/09 10:00:36 by jsarkis           #+#    #+#             */
/*   Updated: 2019/07/09 10:14:05 by jsarkis          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef GET_NEXT_LINE_H
# define GET_NEXT_LINE_H
# define BUFF_SIZE 50
# include "../sources/libft/libft.h"
# include <stdlib.h>
# include <fcntl.h>

void	prep_buff(char **buff);

int		gnl_main_loop(const int fd, char **line, char **buff);

int		get_next_line_lst(const int fd, char **line);

int		get_next_line(const int fd, char **line);

#endif
