/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ms_cmds_class.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vboxuser <vboxuser@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/27 23:17:22 by ichpakov          #+#    #+#             */
/*   Updated: 2024/07/11 05:44:33 by vboxuser         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

static int	echo_checker(char **cmd)
{
	int	i;

	i = 1;
	if (ft_strequal(cmd[0], "echo") != 0)
		return (0);
	while (ft_strequal(cmd[i], "-n") == 0)
		i++;
	if (cmd[i] && (cmd[i][0] == '-'))
		return (0);
	return (i);
}

static int	count_env_maillon(t_env *env)
{
	int	len;
	int	i;

	len = 0;
	i = 0;
	if (env->is_exported == true)
	{
		while (env->env_name[i] != '\0')
		{
			len++;
			i++;
		}
		i = 0;
		if (env->env_value != NULL)
		{
			while (env->env_value[i] != '\0')
			{
				len++;
				i++;
			}
		}
	}
	return (len + 1);
}

char	**get_env(t_env **env)
{
	char	**ex_env;
	int		len;
	int		i;
	t_env	*head;

	head = *env;
	len = ft_lstsize_env(head);
	ex_env = (char **)malloc ((len + 1) * sizeof(char *));
	i = 0;
	while (head != NULL)
	{
		len = count_env_maillon(head);
		ex_env[i] = ft_strjoin_c(head->env_name, head->env_value, '=');
		i++;
		head = head->next;
	}
	ex_env[i] = NULL;
	return (ex_env);
}

int	is_builded_cmd(char *cmd)
{
	if (ft_strcmp("cd", cmd) == 0)
		return (1);
	if (ft_strcmp("echo", cmd) == 0)
		return (1);
	if (ft_strcmp("env", cmd) == 0)
		return (1);
	if (ft_strcmp("exit", cmd) == 0)
		return (1);
	if (ft_strcmp("export", cmd) == 0)
		return (1);
	if (ft_strcmp("pwd", cmd) == 0)
		return (1);
	if (ft_strcmp("unset", cmd) == 0)
		return (1);
	return (0);
}

int	ms_exec_class(t_params *cmds, t_env **env, t_data **data, t_put *puts)
{
	if (ft_strequal(cmds->com[0], "echo") == 0)
	{
		if (echo_checker(cmds->com) == 0)
			return (exec_error(3));
		else
			ms_echo(cmds);
	}
	else if (ft_strequal(cmds->com[0], "cd") == 0)
		ms_cd(cmds, env);
	else if (ft_strequal(cmds->com[0], "pwd") == 0)
		ms_pwd();
	else if (ft_strequal(cmds->com[0], "export") == 0)
		ms_export(cmds, env);
	else if (ft_strequal(cmds->com[0], "unset") == 0)
		ms_unset(cmds, env);
	else if (ft_strequal(cmds->com[0], "env") == 0)
		ms_env(env);
	else if (ft_strequal(cmds->com[0], "exit") == 0)
		ms_exit(cmds, env, data, puts);
	else if (execve_checker(cmds->com, env) == 1)
	{
		ms_exec(cmds, get_env(env), *env);
		exec_error(2);
	}
	return (0);
}
