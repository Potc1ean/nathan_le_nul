/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pars_error.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: njeanbou <njeanbou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/30 10:01:24 by njeanbou          #+#    #+#             */
/*   Updated: 2024/07/04 10:12:45 by njeanbou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

static int	error_heredoc(char **input)
{
	int	i;
	int	nb;

	i = 0;
	nb = 0;
	while (input[i] != NULL)
	{
		if (input[i][0] == '|')
		{
			if (nb > 1)
				return (1);
			nb = 0;
		}
		if (ft_strequal(input[i], "<<") == 0)
			nb++;
		i++;
	}
	if (nb > 1)
		return (1);
	return (0);
}

static int	error_red(char **input)
{
	int	i;

	i = 0;
	while (input[i] != NULL)
	{
		if (input[i][0] == '<' || input[i][0] == '>' || input[i][0] == '|')
		{
			if (input[i + 1] == NULL)
				return (1);
			if (input[i + 1][0] == '<' || input[i + 1][0] == '>'
				|| input[i + 1][0] == '|')
				return (1);
			if (input[i][1] == '<' || input[i][1] == '>')
			{
				if (input[i][2] == '<' || input[i][2] == '>')
					return (1);
			}
		}
		i++;
	}
	return (0);
}

int	error_ex(char **input)
{
	int	i;

	i = 0;
	while (input[i] != NULL)
	{
		if (ft_strequal(input[0], ".") == 0)
			return (1);
		if (ft_strequal(input[i], "./") == 0)
			return (1);
		i++;
	}
	return (0);
}

int	ft_error(char **input, bool for_free)
{
	int	res;

	if (input == NULL || !input[0])
		res = 3;
	else if (input[0][0] == '<' || input[0][0] == '>' || input[0][0] == '|')
		res = 1;
	else if (error_heredoc(input) == 1)
		res = 4;
	else if (error_ex(input) == 1)
		res = 1;
	else
		res = error_red(input);
	if (for_free == true && res != 3)
		ft_free_tab(input);
	return (res);
}

void	print_error(int error, char *input)
{
	if (error == 1)
		printf(MSG_SYNTAX);
	if (error == 3)
		printf(MSG_QUOTE);
	if (error == 4)
		printf(MSG_HEREDOC);
	if (error != 1 && error != 4 && error != 0)
		free(input);
}
