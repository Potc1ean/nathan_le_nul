/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   split_para.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: njeanbou <njeanbou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/17 17:08:28 by njeanbou          #+#    #+#             */
/*   Updated: 2024/07/08 12:53:06 by njeanbou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

static int	count_word(char *str)
{
	int	i;
	int	len;

	i = 0;
	len = 0;
	if (error_quote(str) == -1)
		return (-1);
	while (str[i] != '\0')
	{
		if (ft_isalnumm(str[i]) == 1)
		{
			len++;
			while (str[i] != '\0' && ft_isalnumm(str[i]) == 1)
				i++;
		}
		len += count_red(str, &i);
		len += count_quote(str, &i);
		if (str[i] != '\0')
			i++;
	}
	return (len);
}

static int	count_len(char *str, int *i)
{
	int	len;

	len = 0;
	while (str[*i] != '\0' && str[*i] == ' ')
		(*i)++;
	if (ft_isalnumm(str[*i]) == 1)
	{
		while (str[*i] != '\0' && ft_isalnumm(str[*i]) == 1)
		{
			(*i)++;
			len++;
		}
	}
	else if (str[*i] == '<' || str[*i] == '>')
		len = red_len(str, i);
	else if (str[*i] == '\'' || str[*i] == '\"')
		len = quote_len(str, i);
	else if (str[*i] == '|')
	{
		len = 1;
		(*i)++;
	}
	else
		(*i)++;
	return (len);
}

static char	*putword(char *word, char const *s, int i, int word_len)
{
	int	j;

	j = 0;
	while (word_len > 0)
	{
		word[j] = s[i - word_len];
		j++;
		word_len--;
	}
	word[j] = '\0';
	return (word);
}

static char	**split_arg(char *str, char **dest, int nb_wd)
{
	int	i;
	int	len;
	int	word;

	i = 0;
	word = 0;
	while (word < nb_wd)
	{
		len = count_len(str, &i);
		if (len != 0)
			dest[word] = (char *)malloc ((len + 1) * sizeof(char));
		if (len != 0)
			putword(dest[word++], str, i, len);
		len = 0;
	}
	dest[word] = NULL;
	return (dest);
}

char	**split_para(char *input)
{
	char	**dest;
	int		nb_wd;

	nb_wd = count_word(input);
	if (nb_wd == -1)
		return (NULL);
	dest = (char **)malloc ((nb_wd + 1) * sizeof(char *));
	dest = split_arg(input, dest, nb_wd);
	if (dest == NULL)
	{
		free(input);
		return (NULL);
	}
	free(input);
	return (dest);
}
