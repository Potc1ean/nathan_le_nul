/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   set_varbis_utils.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: njeanbou <njeanbou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/10 19:29:03 by njeanbou          #+#    #+#             */
/*   Updated: 2024/07/11 13:56:26 by njeanbou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

char	*clean_quote_var(char *str)
{
	int		i;
	int		len;
	int		z;
	char	*res;

	i = 0;
	len = ft_strlen(str);
	while (str[i] != '\0')
	{
		if (str[i] == '\'' || str[i] == '\"')
			len--;
		i++;
	}
	res = (char *)malloc ((len + 1) * sizeof(char));
	i = 0;
	z = 0;
	while (str[i] != '\0')
	{
		if (str[i] != '\'' && str[i] != '\"')
			res[z++] = str[i];
		i++;
	}
	res[z] = '\0';
	return (res);
}

int	cond_var(char **com, int i)
{
	if (com[i] != NULL && ft_strstr(com[i], "=") != NULL && com[i + 1] == NULL)
		return (1);
	else if (com[i] != NULL && com[i + 1] != NULL
		&& ft_strstr(com[i], "=") != NULL)
		return (2);
	else if (com[i] && com[i + 1] != NULL
		&& ft_strstr(com[i + 1], "=") != NULL && com[i + 2] == NULL)
		return (2);
	else if (com[i] != NULL && com[i + 1] != NULL && com[i + 2] != NULL
		&& ft_strequal(com[i + 1], "=") == 0)
		return (3);
	return (0);
}

void	free_var(t_params **para, int i)
{
	if (cond_var((*para)->com, i) == 1)
	{
		free((*para)->com[i]);
		(*para)->com[i] = NULL;
	}
	else if (cond_var((*para)->com, i) == 2)
	{
		free((*para)->com[i + 1]);
		free((*para)->com[i]);
		(*para)->com[i] = NULL;
		(*para)->com[i + 1] = NULL;
	}
	else if (cond_var((*para)->com, i) == 3)
	{
		free((*para)->com[i]);
		free((*para)->com[i + 1]);
		free((*para)->com[i + 2]);
		(*para)->com[i] = NULL;
		(*para)->com[i + 1] = NULL;
		(*para)->com[i + 2] = NULL;
	}
}
