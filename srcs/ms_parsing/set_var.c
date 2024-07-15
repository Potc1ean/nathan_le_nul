/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   set_var.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: njeanbou <njeanbou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/05 04:41:08 by njeanbou          #+#    #+#             */
/*   Updated: 2024/07/11 13:56:58 by njeanbou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

char	**mid_var_env(char **split_str, t_env **env)
{
	int		i;
	char	*var;

	i = 0;
	while (split_str[i] != NULL)
	{
		if (split_str[i][0] == '$' && split_str[i][1] != '\0')
		{
			var = recherche_env(split_str[i], env);
			if (var != NULL)
			{
				free(split_str[i]);
				split_str[i] = ft_strdup(var);
				free(var);
			}
		}
		i++;
	}
	split_str[i] = NULL;
	return (split_str);
}

char	*clean_quote(char *str)
{
	int		i;
	int		len;
	int		z;
	char	*res;

	i = 0;
	len = ft_strlen(str);
	while (str[i] != '\0')
	{
		if (str[i] == '\'')
			len--;
		i++;
	}
	res = (char *)malloc ((len + 1) * sizeof(char));
	i = 0;
	z = 0;
	while (str[i] != '\0')
	{
		if (str[i] != '\'')
			res[z++] = str[i];
		i++;
	}
	res[z] = '\0';
	return (res);
}

char	*mid_var(char *str, t_env **env)
{
	char	**split_str;
	char	*var;
	char	*tmp;
	int		i;

	split_str = split_var(str);
	split_str = mid_var_env(split_str, env);
	i = 0;
	var = ft_strdup("");
	while (split_str[i] != NULL)
	{
		tmp = ft_strjoin(var, split_str[i]);
		free(var);
		var = ft_strdup(tmp);
		free(tmp);
		i++;
	}
	var = clean_var(var);
	ft_free_tab(split_str);
	return (var);
}

static int	condition_var(char	**com, int *i, int *z)
{
	if (com[*i][*z] == '$' && (com[*i][*z + 1] != '\0'
		&& com[*i][*z + 1] != '\'' && com[*i][*z + 1] != '\"'
		&& com[*i][*z + 1] != ' '))
		return (0);
	else
		return (1);
}

void	set_var(t_params **para, t_env **env)
{
	char		*var;
	int			i;
	int			z;

	i = 0;
	while ((*para)->com[i] != NULL)
	{
		z = 0;
		while ((*para)->com[i][z] != '\0')
		{
			if ((*para)->com[i][z] == '\'' && (*para)->com[i][0] != '\"')
				break ;
			if (condition_var((*para)->com, &i, &z) == 0
				&& (*para)->inp_red != entre2)
			{
				var = mid_var((*para)->com[i], env);
				free((*para)->com[i]);
				(*para)->com[i] = ft_strdup(var);
				free(var);
				break ;
			}
			z++;
		}
		i++;
	}
}
