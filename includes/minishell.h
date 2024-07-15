/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: njeanbou <njeanbou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/12 15:51:36 by njeanbou          #+#    #+#             */
/*   Updated: 2024/07/11 15:29:46 by njeanbou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

# include "../ms_libft/libft.h"

# include <stdio.h>

# include <readline/readline.h>
# include <readline/history.h>

# include <stdbool.h>
# include <unistd.h>
# include <stdlib.h>
# include <sys/types.h>
# include <dirent.h>
# include <signal.h>
# include <sys/stat.h>
# include <sys/wait.h>
# include <errno.h>
# include <fcntl.h>

# define GREEN_TEXT "\033[0;92m"
# define RESET_TEXT "\033[0m"
# define WELCOME_MSG "\
###############################################\n\
#                                             #\n\
#             _       _     _          _ _    #\n\
#   _ __ ___ (_)_ __ (_)___| |__   ___| | |   #\n\
#  | '_ ` _ \\| | '_ \\| / __| '_ \\ / _ \\ | |   #\n\
#  | | | | | | | | | | \\__ \\ | | |  __/ | |   #\n\
#  |_| |_| |_|_|_| |_|_|___/_| |_|\\___|_|_|   #\n\
#  by njeanbou and ichpakov                   #\n\
#                                             #\n\
###############################################\n"
# define MSG_SYNTAX "minishell: syntax error near unexpected token\n"
# define MSG_QUOTE "minishell: unclosed quote\n"
# define MSG_HEREDOC "minishell: two heredoc\n"
# define MSG_FATAL "error 1 : fatal error\n"
# define MSG_EXEC "error 2 : ca a pas execute my J\n"
# define MSG_FLAGS "error 3 : seul echo peut avoir un flag dans l'enoncer\n"
# define MSG_ARG "error 4 : too many arguments\n"
# define MSG_NOT_FOUND "error: command not found: "

typedef enum e_operator
{
	none,
	PIPE,
	entre1,
	entre2,
	sortie1,
	sortie2,
}		t_operator;

typedef struct s_put
{
	char	*input;
	char	*output;
}	t_put;

typedef struct s_params
{
	char			**com;
	t_operator		inp_red;
	t_operator		out_red;
	struct s_params	*next;
}			t_params;

typedef struct s_env
{
	char			*env_name;
	char			*env_value;
	bool			is_exported;
	struct s_env	*next;
}			t_env;

typedef struct s_data
{
	int		p_fd[2];
	int		fd_in;
	int		fd_out;
	bool	exit;
	pid_t	pid;
}			t_data;

//cmd
int		ms_cd(t_params *para, t_env **env);
int		ms_echo(t_params *para);
int		ms_env(t_env **env);
void	ms_exit(t_params *para, t_env **env, t_data **data, t_put *put);
int		ms_export(t_params *para, t_env **env);
char	*set_var_export(char **com, int *i);
int		ms_pwd(void);
int		ms_unset(t_params *para, t_env **env);

//parsing
int		set_para(t_params **param, char *input, t_env **env, t_put **put);
void	set_put(t_put **put, t_params **para);
void	ft_doc(t_params **para, t_env **env, t_put **put);
void	init_here(int *interrupted, char **doctmp, char **res);
int		doc_null(char *doc, char **doctmp);
int		doc_eq(char **doc, char **doctmp, char **res, char *exit);
int		inter(int interrupted, char **doctmp);
char	*ft_strdup_nl(const char *s1);
void	set_var(t_params **para, t_env **env);
void	set_enum(t_params **para);
char	**set_cote(char **input);
char	**split_para(char *input);
int		error_quote(char *str);
int		count_quote(char *str, int *i);
int		count_red(char *str, int *i);
int		red_len(char *str, int *i);
int		quote_len(char *str, int *i);
int		ft_error(char **input, bool for_free);
void	free_error(t_params **para, t_put **put, t_data **data);
void	print_error(int error, char *input);
void	set_varbis(t_params **para, t_env **env);
char	*mid_var(char *str, t_env **env);
char	**mid_var_env(char **split_str, t_env **env);
int		len_quote(int *i, char *str, char c);
char	*clean_quote(char *str);
int		strequal_quote(const char *str, const char *re);
char	*clean_quote_var(char *str);
int		cond_var(char **com, int i);
void	free_var(t_params **para, int i);

//error
int		exec_error(int num);

//signal
void	exec_signal(int signal);
void	handler_signal(int signal);
void	handle_sigint_heredoc(int sig);

//exec
int		ms_exec_loop(t_data *data, t_params **cmds, t_put *puts, t_env **env);
int		ms_exec_class(t_params *cmds, t_env **env, t_data **data, t_put *puts);
void	ms_exec(t_params *cmds, char **env, t_env *t_env);
void	ms_input(t_data *data, t_put *puts);
void	ms_output(t_data *data, t_put *puts, int rdr);
void	close_file(int fd);
int		open_file(char *file, int in_or_out);
char	*get_path(char *cmd, char **env);
int		ms_mycmds(t_params *cmds);
char	**get_env(t_env **env);
void	ft_free_tab(char **tab);
int		is_builded_cmd(char *cmd);
int		execve_checker(char **cmd, t_env **env);
int		check_exe(t_params **cmds);
pid_t	ft_getpid(void);
int		ms_redir_exec(t_data *data, t_params *cmds, t_put *puts, t_env **env);

//utils
char	*clean_input(char *raw_input);
t_env	*set_env(char **env);
t_env	*new_node(char *env_name, char *env_value, bool export);
void	print_all(t_params **para, t_env **env, t_put **put);
void	print_com(t_params **para);
char	*recherche_env(char *str, t_env **env);
char	*ft_strjoin_sp(char const *s1, char *s2);
char	**split_var(char *str);
int		count_wd_var(char *str);
char	*clean_var(char *var);
void	free_all(t_params **para, t_put **put, t_data **data);
t_env	*ft_lstlast_env(t_env *lst);
void	ft_lstadd_back_env(t_env **lst, t_env *new);
int		ft_lstsize_env(t_env *lst);
void	add_status(t_env **env, int status);
char	*ft_strdup_quote(const char *s1);
int		search_env(char *str, t_env **env);

#endif
