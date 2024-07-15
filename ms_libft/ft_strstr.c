/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strstr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: njeanbou <njeanbou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/28 04:08:45 by njeanbou          #+#    #+#             */
/*   Updated: 2024/04/30 11:55:18 by njeanbou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strstr(const char *str, const char *re)
{
	int	i;
	int	z;

	while (*str != '\0')
	{
		i = 0;
		z = 0;
		while (str[i] && re[z] && str[i] == re[z])
		{
			z++;
			i++;
		}
		if (re[z] == '\0')
			return ((char *)str);
		str++;
	}
	return (NULL);
}
