/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ms_cd.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: njeanbou <njeanbou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/30 13:48:37 by njeanbou          #+#    #+#             */
/*   Updated: 2024/06/19 16:48:46 by njeanbou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

static char	*change_pwd(t_env **env)
{
	char	*tmp;
	t_env	*head;
	char	*path;

	head = *env;
	tmp = recherche_env("$PWD", env);
	while (head != NULL)
	{
		if (ft_strequal(head->env_name, "PWD") == 0)
		{
			path = getcwd(NULL, 0);
			free(head->env_value);
			head->env_value = ft_strdup(path);
			free(path);
		}
		head = head->next;
	}
	return (tmp);
}

static void	change_oldpwd(char *tmp, t_env **env)
{
	t_env	*head;

	head = *env;
	while (head != NULL)
	{
		if (ft_strstrbool(head->env_name, "OLDPWD") == 0)
		{
			free(head->env_value);
			head->env_value = ft_strdup(tmp);
		}
		head = head->next;
	}
}

char	*set_path(char **com, t_env **env)
{
	char	*path;
	char	*tmp;

	if (com[1] == NULL)
		path = recherche_env("$HOME", env);
	else if (com[1][0] == '~')
	{
		if (com[1][1] == '\0')
			path = recherche_env("$HOME", env);
		else
		{
			tmp = recherche_env("$HOME", env);
			path = ft_strjoin(tmp, com[1] + 1);
			free(tmp);
		}
	}
	else if (com[1][0] == '-' && com[1][1] == '\0')
		path = recherche_env("$OLDPWD", env);
	else
		path = ft_strdup(com[1]);
	return (path);
}

int	ms_cd(t_params *para, t_env **env)
{
	char	*tmp;
	char	*path;

	path = set_path(para->com, env);
	if (access(path, F_OK) != 0)
		printf("minishell: cd: %s: No such file or directory\n", path);
	if (chdir(path) == 0)
	{
		tmp = change_pwd(env);
		change_oldpwd(tmp, env);
		if (para->com[1] != NULL)
		{
			if (para->com[1][0] == '-' && para->com[1][1] == '\0')
				ms_pwd();
		}
		free(tmp);
		free(path);
		return (0);
	}
	free(path);
	return (-1);
}
