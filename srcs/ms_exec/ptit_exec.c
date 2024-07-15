/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ptit_exec.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ichpakov <ichpakov@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/13 11:02:34 by ichpakov          #+#    #+#             */
/*   Updated: 2024/07/15 13:59:05 by ichpakov         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

void	ms_exec(t_params *cmds, char **env, t_env *t_envv)
{
	char	**s_cmd;
	char	*path;

	while (t_envv)
	{
		if (ft_strstr(t_envv->env_name, "PATH"))
			break ;
		t_envv = t_envv->next;
	}
	if (!t_envv)
	{
		ft_free_tab(env);
		printf(MSG_NOT_FOUND"%s\n", cmds->com[0]);
		exit(2);
	}
	s_cmd = cmds->com;
	path = get_path(s_cmd[0], env);
	execve(path, s_cmd, env);
	ft_putstr_fd(MSG_NOT_FOUND, 2);
	ft_putendl_fd(s_cmd[0], 2);
	ft_free_tab(env);
	exit(2);
}

static int	ms_fork(t_data *data, t_params *cmds, t_put *puts, t_env **env)
{
	data->pid = fork();
	if (data->pid == 0)
	{
		if (cmds->out_red == PIPE)
		{
			if ((dup2(data->p_fd[1], STDOUT_FILENO) == -1
					|| close(data->p_fd[0]) == -1))
				return (exec_error(0));
		}
		else if (cmds->out_red == sortie1)
			ms_output(data, puts, 1);
		else if (cmds->out_red == sortie2)
			ms_output(data, puts, 2);
		ms_exec_class(cmds, env, &data, puts);
		exit(0);
	}
	if (cmds->out_red == PIPE)
	{
		if (dup2(data->p_fd[0], STDIN_FILENO) == -1
			|| close(data->p_fd[0]) == -1 || close(data->p_fd[1]) == -1)
			return (exec_error(0));
	}
	return (0);
}

int	ms_redir_exec(t_data *data, t_params *cmds, t_put *puts, t_env **env)
{
	int	status;

	if (puts->input && (close(open(puts->input, O_RDONLY)) == -1))
		return (256 * (printf("no such file or directory\n") / 26));
	if (cmds->inp_red == entre1 || cmds->inp_red == entre2)
		ms_input(data, puts);
	if (cmds->out_red == PIPE)
	{
		if (pipe(data->p_fd) == -1)
			return (exec_error(0));
	}
	if ((cmds->inp_red != PIPE) && (cmds->out_red != PIPE)
		&& is_builded_cmd(cmds->com[0]))
	{
		if (cmds->out_red == sortie1)
			ms_output(data, puts, 1);
		else if (cmds->out_red == sortie2)
			ms_output(data, puts, 2);
		ms_exec_class(cmds, env, &data, puts);
	}
	else
		ms_fork(data, cmds, puts, env);
	return (WIFEXITED(status));
}

static void	supp_heredoc(t_data *data, t_env **env, t_put *puts)
{
	char	**rm;
	char	**var_env;

	var_env = get_env(env);
	rm = malloc (3 * sizeof(char *));
	rm[0] = "rm";
	rm[1] = puts->input;
	rm[2] = NULL;
	data->pid = fork();
	if (data->pid == 0)
		execve(get_path("rm", var_env), rm, var_env);
	else
		waitpid(data->pid, 0, 0);
	ft_free_tab(var_env);
	free(rm);
}

int	ms_exec_loop(t_data *data, t_params **cmds, t_put *puts, t_env **env)
{
	t_params	*t_cmds;
	int			status;
	int			saved_stdin;
	int			saved_stdout;

	saved_stdin = dup(STDIN_FILENO);
	saved_stdout = dup(STDOUT_FILENO);
	t_cmds = *cmds;
	signal(SIGINT, exec_signal);
	signal(SIGQUIT, exec_signal);
	while (t_cmds != NULL)
	{
		status = ms_redir_exec(data, t_cmds, puts, env);
		t_cmds = t_cmds->next;
	}
	waitpid(data->pid, &status, 0);
	signal(SIGINT, handler_signal);
	signal(SIGQUIT, handler_signal);
	dup2(saved_stdin, STDIN_FILENO);
	dup2(saved_stdout, STDOUT_FILENO);
	close(saved_stdin);
	if ((*cmds)->inp_red == entre2)
		supp_heredoc(data, env, puts);
	return (status);
}
