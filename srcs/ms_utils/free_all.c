/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free_all.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: njeanbou <njeanbou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/30 09:33:51 by njeanbou          #+#    #+#             */
/*   Updated: 2024/06/19 16:43:13 by njeanbou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

void	free_error(t_params **para, t_put **put, t_data **data)
{
	free((*para));
	free((*put));
	free((*data));
}

void	free_para(t_params **para)
{
	t_params	*current;
	t_params	*next;
	int			i;

	if (!para || !*para)
		return ;
	current = *para;
	while (current != NULL)
	{
		next = current->next;
		if (current->com)
		{
			i = 0;
			while (current->com[i])
			{
				free(current->com[i]);
				i++;
			}
			free(current->com);
		}
		free(current);
		current = next;
	}
	current = NULL;
}

void	free_all(t_params **para, t_put **put, t_data **data)
{
	free_para(para);
	if ((*put)->input != NULL)
		free((*put)->input);
	if ((*put)->output != NULL)
		free((*put)->output);
	free((*put));
	free((*data));
}
