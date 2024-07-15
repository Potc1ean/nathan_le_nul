/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   split_var.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: njeanbou <njeanbou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/16 15:53:13 by njeanbou          #+#    #+#             */
/*   Updated: 2024/07/11 13:55:32 by njeanbou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

int	count_wd_var(char *str)
{
	int	i;
	int	len;

	i = 0;
	len = 0;
	if (ft_isalnumm(str[0]) == 1)
		len++;
	while (str[i] != '\0')
	{
		if (str[i] == '\"' || str[i] == '\'' || str[i] == ' '
			|| str[i] == '$' || str[i] == '\n')
			len++;
		i++;
	}
	return (len);
}

int	count_len(char *str, int *i, bool *var)
{
	int	len;

	len = 0;
	while (str[*i] != '\0')
	{
		if (str[*i] == '$' && (*var) == false && (*i) != 0)
		{
			(*var) = true;
			break ;
		}
		if ((str[*i] == ' ' || str[*i] == '\''
				|| str[*i] == '\"' || str[*i] == '\n')
			&& (*var) == true)
		{
			(*var) = false;
			break ;
		}
		if (str[*i] == '$' && len != 0 && (*var) == true)
		{
			break ;
		}
		(*i)++;
		len++;
	}
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

static char	**split_words(char *str, char **dest, int nb_wd)
{
	int		i;
	int		len;
	int		word;
	bool	var;

	i = 0;
	word = 0;
	var = false;
	while (word < nb_wd)
	{
		len = count_len(str, &i, &var);
		dest[word] = (char *)malloc ((len + 1) * sizeof(char));
		putword(dest[word++], str, i, len);
		len = 0;
	}
	dest[word] = NULL;
	return (dest);
}

char	**split_var(char *str)
{
	char	**dest;
	int		nb_wd;

	nb_wd = count_wd_var(str);
	dest = (char **)malloc ((nb_wd + 1) * sizeof(char *));
	if (!dest)
		return (0);
	dest = split_words(str, dest, nb_wd);
	return (dest);
}
