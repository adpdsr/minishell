/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_tabdup.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adu-pelo <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/03/12 15:55:07 by adu-pelo          #+#    #+#             */
/*   Updated: 2016/03/14 16:37:18 by adu-pelo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	**ft_tabdup(char **tab)
{
	int		i;
	int		len;
	char	**cpy;

	if (tab)
	{
		i = 0;
		len = ft_tablen(tab);
		if (!(cpy = (char **)malloc(sizeof(char *) * (len + 1))))
			return (NULL);
		while (i < len)
		{
			cpy[i] = ft_strdup(tab[i]);
			i++;
		}
		cpy[i] = NULL;
		return (cpy);
	}
	return (NULL);
}
