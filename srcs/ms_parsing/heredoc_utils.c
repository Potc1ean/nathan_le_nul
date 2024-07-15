/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heredoc_utils.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: njeanbou <njeanbou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/04 14:54:12 by njeanbou          #+#    #+#             */
/*   Updated: 2024/07/04 14:56:28 by njeanbou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

void	init_here(int *interrupted, char **doctmp, char **res)
{
	*interrupted = 0;
	*doctmp = ft_strdup("");
	*res = NULL;
}

int	doc_null(char *doc, char **doctmp)
{
	if (doc == NULL)
	{
		free(*doctmp);
		return (1);
	}
	else
		return (0);
}

int	doc_eq(char **doc, char **doctmp, char **res, char *exit)
{
	if (ft_strequal(*doc, exit) == 0)
	{
		if (*doc)
			free(*doc);
		if (*doctmp == NULL)
			return (1);
		*res = ft_strdup_nl(*doctmp);
		if (*doctmp)
			free(*doctmp);
		return (2);
	}
	return (0);
}

int	inter(int interrupted, char **doctmp)
{
	if (interrupted)
	{
		free(*doctmp);
		return (1);
	}
	return (0);
}
