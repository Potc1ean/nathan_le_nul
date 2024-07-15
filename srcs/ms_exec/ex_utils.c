/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ex_utils.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: njeanbou <njeanbou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/27 13:31:24 by ichpakov          #+#    #+#             */
/*   Updated: 2024/07/10 16:07:11 by njeanbou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

/* close_file
*   ferme un fichier seulement si il existe.
*/
void	close_file(int fd)
{
	if (fd > 0)
		close(fd);
}

/* open_file :
*   prends un fichier et sa nature en parametre.
*   Esayes d'ouvrir le fichier avec les droits
*   necessaire a sa nature. Renvoie son fd si tout functionne.
*/
int	open_file(char *file, int in_or_out)
{
	int	ret;

	ret = 0;
	if (in_or_out == 0)
		ret = open(file, O_RDONLY, 0777);
	if (in_or_out == 1)
		ret = open(file, O_WRONLY | O_CREAT | O_TRUNC, 0777);
	if (in_or_out == 2)
		ret = open(file, O_CREAT | O_WRONLY | O_APPEND, 0777);
	if (ret == -1)
		ret = -1;
	return (ret);
}

int	check_exe(t_params **cmds)
{
	t_params	*head;
	int			i;

	i = -1;
	head = *cmds;
	while (head != NULL)
	{
		i++;
		printf("%s\n", head->com[0]);
		if (ft_strequal(head->com[0], "./minishell") == 0 && i > 0)
			return (1);
		head = head->next;
	}
	return (0);
}
