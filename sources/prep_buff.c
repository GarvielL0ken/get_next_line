/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   prep_buff.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jsarkis <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/07/09 09:49:25 by jsarkis           #+#    #+#             */
/*   Updated: 2019/07/09 09:59:52 by jsarkis          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/get_next_line.h"

void	prep_buff(char **buff)
{
	int pos;

	pos = ft_find_index(*buff, '\n');
	if (pos == -1)
		*(*buff) = '\0';
	else
		*buff = ft_str_shift(*buff, pos + 1);
}
