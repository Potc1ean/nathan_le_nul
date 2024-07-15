/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ex_errors.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vboxuser <vboxuser@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/27 23:33:35 by ichpakov          #+#    #+#             */
/*   Updated: 2024/06/19 16:09:55 by vboxuser         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

int	ft_errors(char *str)
{
	write(2, str, ft_strlen(str));
	return (0);
}

int	exec_error(int num)
{
	if (num == 0)
		return (0 * ft_errors(MSG_FATAL));
	if (num == 2)
		return (0 * ft_errors(MSG_EXEC));
	if (num == 3)
		return (0 * ft_errors(MSG_FLAGS));
	if (num == 4)
		return (0 * ft_errors(MSG_ARG));
	else
		return (0 * ft_errors(MSG_FATAL));
}
