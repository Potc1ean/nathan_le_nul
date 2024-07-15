/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strstrbool.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: njeanbou <njeanbou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/05 04:45:25 by njeanbou          #+#    #+#             */
/*   Updated: 2024/04/30 14:39:13 by njeanbou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_strstrbool(const char *str, const char *re)
{
	int	i;
	int	z;

	if (!str || !re)
		return (1);
	while (*str != '\0')
	{
		i = 0;
		z = 0;
		while (str[i] && re[z] && str[i] == re[z])
		{
			z++;
			i++;
		}
		if (re[z] == '\0' && ft_strlen(str) == ft_strlen(re))
			return (0);
		str++;
	}
	return (1);
}
