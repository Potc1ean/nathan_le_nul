/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lst_utils.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: njeanbou <njeanbou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/02 17:30:31 by njeanbou          #+#    #+#             */
/*   Updated: 2024/07/08 11:06:20 by njeanbou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

t_env	*ft_lstlast_env(t_env *lst)
{
	if (!lst)
		return (NULL);
	while (lst->next)
		lst = lst->next;
	return (lst);
}

void	ft_lstadd_back_env(t_env **lst, t_env *new)
{
	if (!lst || !new)
		return ;
	if (*lst)
		ft_lstlast_env(*lst)->next = new;
	else
		*lst = new;
}

char	*ft_strjoin_sp(char const *s1, char *s2)
{
	char	*new;
	int		i;
	int		j;

	i = 0;
	j = 0;
	if (!s1 || !s2)
		return (s2);
	new = (char *)malloc((ft_strlen(s1) + ft_strlen(s2) + 2) * sizeof(char));
	if (!new)
		return (NULL);
	while (s1[i])
	{
		new[i] = s1[i];
		i++;
	}
	new[i++] = ' ';
	while (s2[j])
	{
		new[i] = s2[j];
		i++;
		j++;
	}
	new[i] = '\0';
	return (new);
}

int	ft_lstsize_env(t_env *lst)
{
	int	count;

	count = 0;
	while (lst)
	{
		count++;
		lst = lst->next;
	}
	return (count);
}

char	*ft_strdup_quote(const char *s1)
{
	char	*dup;
	size_t	len;
	size_t	i;
	size_t	z;

	len = ft_strlen(s1) - 1;
	dup = (char *) malloc(len * sizeof(*s1));
	i = 1;
	z = 0;
	if (dup == NULL)
		return (NULL);
	if (s1[0] == '\'')
	{
		while (s1[i] != '\0' && s1[i] != '\'')
			dup[z++] = s1[i++];
	}
	if (s1[0] == '\"')
	{
		while (s1[i] != '\0' && s1[i] != '\"')
			dup[z++] = s1[i++];
	}
	dup[z] = '\0';
	return (dup);
}
