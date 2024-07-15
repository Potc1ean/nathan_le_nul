/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ichpakov <ichpakov@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/27 14:52:31 by njeanbou          #+#    #+#             */
/*   Updated: 2024/07/15 17:03:52 by ichpakov         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "includes/minishell.h"

static char	*get_input(void)
{
	char	*raw_input;
	char	*input;

	raw_input = readline("minishell$ ");
	input = clean_input(raw_input);
	free(raw_input);
	if (input != NULL && input[0] != ' ')
	{
		if (ft_strstr(input, "<<") == NULL)
			add_history(input);
	}
	return (input);
}

void	init_data(t_params **para, t_put **put, t_data **data)
{
	*para = (t_params *)malloc (sizeof(t_params));
	*put = (t_put *) malloc (sizeof(t_put));
	*data = NULL;
	*data = malloc(sizeof(t_data));
	(*data)->fd_in = -2;
	(*put)->input = NULL;
	(*put)->output = NULL;
}

void	loop_shell(t_params *para, t_env *lstenv, t_put *put, t_data *data)
{
	int		error;
	char	*input;

	while (1)
	{
		input = get_input();
		if (input != NULL && input[0] != ' ')
		{
			init_data(&para, &put, &data);
			error = set_para(&para, input, &lstenv, &put);
			if (error == 0 && para->com[0] != NULL)
			{
				//print_all(&para, &lstenv, &put);
				add_status(&lstenv, ms_exec_loop(data, &para, put, &lstenv));
			}
			if (error != 0)
			{
				print_error(error, input);
				free_error(&para, &put, &data);
			}
			else
				free_all(&para, &put, &data);	
		}
		else if (isatty(STDIN_FILENO) == 0)
			exit(EXIT_SUCCESS);
		else if (input == NULL)
			return ((void)printf("Exit\n"));
	}
}

static void	incr_shlvl(t_env **env)
{
	t_env	*head;
	int		lvl;

	head = *env;
	while (head != NULL)
	{
		if (ft_strequal(head->env_name, "SHLVL") == 0)
		{
			lvl = ft_atoi(head->env_value);
			lvl++;
			free(head->env_value);
			head->env_value = ft_itoa(lvl);
		}
		head = head->next;
	}
}

int	main(int argc, char **argv, char **env)
{
	t_params	*para;
	t_env		*lstenv;
	t_put		*put;
	t_data		*data;

	printf("\n%s\n\n", WELCOME_MSG);
	para = NULL;
	put = NULL;
	data = NULL;
	signal(SIGINT, handler_signal);
	signal(SIGQUIT, handler_signal);
	if (argc < 1 || argv[1] != NULL)
		exit(EXIT_FAILURE);
	lstenv = set_env(env);
	incr_shlvl(&lstenv);
	loop_shell(para, lstenv, put, data);
	return (0);
}
