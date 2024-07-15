/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   set_varbis.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: njeanbou <njeanbou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/15 19:32:47 by njeanbou          #+#    #+#             */
/*   Updated: 2024/07/10 19:29:39 by njeanbou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

static void	mod_var(t_env *head, char **line, bool *new_var)
{
	while (head != NULL)
	{
		if (ft_strequal(head->env_name, line[0]) == 0
			&& head->is_exported == true)
		{
			free(head->env_value);
			head->env_value = ft_strdup(line[1]);
			(*new_var) = true;
		}
		if (ft_strequal(head->env_name, line[0]) == 0
			&& head->is_exported == false)
		{
			head->is_exported = true;
			(*new_var) = true;
		}
		head = head->next;
	}
}

static char	**set_line(char *var)
{
	char	**line;
	int		i;

	i = 0;
	if (ft_strstr(var, "=") != NULL)
	{
		line = (char **)malloc (3 * sizeof(char *));
		line[0] = (char *)malloc (ft_strlen(var) * sizeof(char));
		while (var[i + 1] != '\0')
		{
			line[0][i] = var[i];
			i++;
		}
		line[0][i] = '\0';
		line[1] = ft_strdup("");
		line[2] = NULL;
	}
	else
	{
		line = (char **)malloc(3 * sizeof(char *));
		line[0] = ft_strdup(var);
		line[1] = ft_strdup("");
		line[2] = NULL;
	}
	return (line);
}

static int	add_varbis(char *var, t_env **env)
{
	t_env	*new;
	t_env	*head;
	char	**line;
	bool	new_var;

	head = *env;
	new_var = false;
	if (ft_strstr(var, "=") != NULL && (*(ft_strstr(var, "=") + 1)) != '\0')
		line = ft_split(var, '=');
	else
	{
		line = set_line(var);
	}
	mod_var(head, line, &new_var);
	if (new_var == false)
	{
		new = new_node(line[0], line[1], true);
		ft_lstadd_back_env(env, new);
	}
	ft_free_tab(line);
	return (EXIT_SUCCESS);
}

void	set_varbis(t_params **para, t_env **env)
{
	int		i;
	int		z;
	char	*var;
	char	*tmp;

	var = NULL;
	tmp = NULL;
	i = 0;
	if ((*para)->com[0] != NULL && (*para)->com[1] != NULL
		&& (*para)->com[2] != NULL && (*para)->com[3] != NULL)
		return ;
	while ((*para)->com[i] != NULL)
	{
		if ((*para)->com[i][0] != '=' && cond_var((*para)->com, i) != 0)
		{
			z = i;
			var = set_var_export((*para)->com, &i);
			tmp = clean_quote_var(var);
			free(var);
			add_varbis(tmp, env);
			free(tmp);
			free_var(para, z);
		}
		i++;
	}
}
