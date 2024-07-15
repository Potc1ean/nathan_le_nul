/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   set_env.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: njeanbou <njeanbou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/28 07:01:12 by njeanbou          #+#    #+#             */
/*   Updated: 2024/07/05 16:32:49 by njeanbou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

static void	free_node(t_env *node)
{
	free(node->env_name);
	free(node->env_value);
	free(node);
}

t_env	*new_node(char *env_name, char *env_value, bool export)
{
	t_env	*new;

	new = (t_env *)malloc (sizeof(t_env));
	if (env_name != NULL)
		new->env_name = ft_strdup(env_name);
	else
		new->env_name = NULL;
	if (env_value != NULL)
		new->env_value = ft_strdup(env_value);
	else
		new->env_value = NULL;
	new->is_exported = export;
	new->next = NULL;
	return (new);
}

static void	set_node(t_env **head, t_env **temp, char **line)
{
	if (!(*head))
	{
		(*head) = new_node(line[0], line[1], true);
		(*temp) = (*head);
	}
	else
	{
		(*temp)->next = new_node(line[0], line[1], true);
		(*temp) = (*temp)->next;
	}
	ft_free_tab(line);
}

t_env	*set_env(char **env)
{
	t_env	*head;
	t_env	*temp;
	char	**line;
	int		i;

	head = NULL;
	temp = NULL;
	i = 0;
	while (env[i])
	{
		line = ft_split(env[i], '=');
		set_node(&head, &temp, line);
		i++;
	}
	return (head);
}

void	add_status(t_env **env, int status)
{
	t_env	*head;
	t_env	*new;
	bool	new_var;
	char	*stat;

	head = *env;
	new_var = false;
	stat = ft_itoa(status);
	new = new_node("?", stat, false);
	while (head != NULL)
	{
		if (ft_strequal(head->env_name, "?") == 0)
		{
			free(head->env_value);
			head->env_value = ft_strdup(stat);
			new_var = true;
		}
		head = head->next;
	}
	if (new_var == false)
		ft_lstadd_back_env(env, new);
	else
		free_node(new);
	free(stat);
}
