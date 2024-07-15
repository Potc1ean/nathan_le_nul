/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strequal.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: njeanbou <njeanbou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/30 14:40:35 by njeanbou          #+#    #+#             */
/*   Updated: 2024/06/03 19:12:03 by njeanbou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_strequal(const char *str, const char *re)
{
	int	i;
	int	z;

	if (!str || !re)
		return (1);
	i = 0;
	z = 0;
	while (str[i] && re[z] && str[i] == re[z])
	{
		z++;
		i++;
	}
	if (re[z] == '\0' && ft_strlen(str) == ft_strlen(re))
		return (0);
	return (1);
}
