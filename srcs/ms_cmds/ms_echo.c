/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ms_echo.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: njeanbou <njeanbou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/13 15:25:16 by njeanbou          #+#    #+#             */
/*   Updated: 2024/06/19 16:49:05 by njeanbou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

static void	print_echo(char *str)
{
	size_t	i;

	i = 0;
	while (str[i])
	{
		if (str[i] == '\\')
		{
			if (str[i + 1])
			{
				ft_putchar_fd(str[i + 1], STDOUT_FILENO);
				i += 2;
			}
			else
			{
				break ;
			}
		}
		else
		{
			ft_putchar_fd(str[i], STDOUT_FILENO);
			i++;
		}
	}
}

int	ms_echo(t_params *para)
{
	int	i;

	i = 1;
	if (para->inp_red == entre2)
	{
		ft_putchar_fd('\n', STDOUT_FILENO);
		return (EXIT_SUCCESS);
	}
	while (ft_strequal(para->com[i], "-n") == 0)
		i++;
	while (para->com[i] != NULL)
	{
		print_echo(para->com[i]);
		if (!para->com[i + 1])
			break ;
		ft_putchar_fd(' ', STDOUT_FILENO);
		i++;
	}
	if (ft_strequal(para->com[1], "-n") != 0)
		write(STDOUT_FILENO, "\n", 1);
	return (EXIT_SUCCESS);
}
