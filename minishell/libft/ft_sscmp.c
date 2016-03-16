/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_sscmp.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adu-pelo <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/03/12 17:52:58 by adu-pelo          #+#    #+#             */
/*   Updated: 2016/03/12 17:57:35 by adu-pelo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int		ft_sscmp(char *s, char *s1, char *s2)
{
	if (!ft_strcmp(s, s1) || !ft_strcmp(s, s2))
		return (1);
	return (0);
}