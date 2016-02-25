/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.h                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adu-pelo <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/01/12 16:57:22 by adu-pelo          #+#    #+#             */
/*   Updated: 2016/01/26 14:29:15 by adu-pelo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef GET_NEXT_LINE_H
# define GET_NEXT_LINE_H
# define BUFF_SIZE 7

# include "./libft/libft.h"
# include <stdlib.h>
# include <unistd.h>
# include <fcntl.h>

int	get_next_line(int const fd, char **line);

#endif
