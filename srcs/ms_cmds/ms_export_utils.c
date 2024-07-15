/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ms_export_utils.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: njeanbou <njeanbou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/08 09:48:12 by njeanbou          #+#    #+#             */
/*   Updated: 2024/07/11 13:51:55 by njeanbou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

static char	*sve_p1(char **com, int *i)
{
	char	*var;

	var = NULL;
	if ((ft_strchr(com[*i], '=') != NULL
			&& *(ft_strchr(com[*i], '=') + 1) != '\0')
		|| (ft_strchr(com[*i], '=') != NULL && com[*i + 1] == NULL))
		var = ft_strdup(com[*i]);
	else if (ft_strstr(com[*i], "=") == NULL && (com[*i + 1] == NULL
			|| ft_strstr(com[*i + 1], "=") == NULL))
		var = ft_strdup(com[*i]);
	else if (ft_strchr(com[*i], '=') == NULL
		&& *(ft_strchr(com[*i +1], '=') + 1) == '\0'
		&& ft_strequal(com[*i + 1], "=") != 0)
		var = ft_strdup(com[*i]);
	return (var);
}

static char	*sve_p2(char **com, int *i)
{
	char	*var;

	var = NULL;
	if (ft_strstr(com[*i], "=") == NULL
		&& ft_strequal(com[*i + 1], "=") == 0 && com[*i + 2] == NULL)
	{
		var = ft_strjoin(com[*i], com[*i + 1]);
		(*i) += 1;
	}
	else if (ft_strstr(com[*i], "=") != NULL && com[*i + 1] != NULL)
	{
		var = ft_strjoin(com[*i], com[*i + 1]);
		(*i) += 1;
	}
	else if (ft_strstr(com[*i], "=") == NULL
		&& ft_strstr(com[*i + 1], "=") != NULL
		&& ft_strequal(com[*i + 1], "=") == 1)
	{
		var = ft_strjoin(com[*i], com[*i + 1]);
		(*i) += 1;
	}
	return (var);
}

static char	*sve_p3(char **com, int *i)
{
	char	*var;
	char	*tmp;

	tmp = NULL;
	var = NULL;
	if (ft_strstr(com[*i], "=") == NULL
		&& ft_strequal(com[*i + 1], "=") == 0 && com[*i + 2] != NULL)
	{
		tmp = ft_strjoin(com[*i], com[*i + 1]);
		var = ft_strjoin(tmp, com[*i + 2]);
		free(tmp);
		(*i) += 2;
	}
	return (var);
}

char	*set_var_export(char **com, int *i)
{
	char	*var;

	var = sve_p1(com, i);
	if (var == NULL)
		var = sve_p2(com, i);
	if (var == NULL)
		var = sve_p3(com, i);
	return (var);
}
