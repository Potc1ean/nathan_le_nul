/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print_all.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vboxuser <vboxuser@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/03 03:21:39 by njeanbou          #+#    #+#             */
/*   Updated: 2024/07/11 05:13:33 by vboxuser         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

void	print_all(t_params **para, t_env **env, t_put **put)
{
	t_params	*headp;
	t_env		*heade;
	t_put		*headput;
	int			i;

	headp = *para;
	heade = *env;
	headput = *put;
	i = 0;
	printf("commande :\n\n");
	while (headp != NULL)
	{
		while (headp->com[i] != NULL)
		{
			printf("%s ", headp->com[i]);
			i++;
		}
		printf("\n");
		
		if (headput->input != NULL)
			printf("inputput : %s\n", headput->input);
		else
			printf("input : aucune\n");
		if (headp->inp_red == entre1)
			printf("la commande possede un <\n");
		else if (headp->inp_red == entre2)
			printf("la commande possede un <<\n");
		else if (headp->inp_red == PIPE)
			printf("la commande possede un PIPE d'entre\n");
		else
			printf("la commande na pas de redirection d'entre\n");
		
		if (headput->output != NULL)
			printf("output : %s\n", headput->output);
		else
			printf("output : sortie std\n");
		if (headp->out_red == sortie1)
			printf("la commande possede un >\n");
		else if (headp->out_red == sortie2)
			printf("la commande possede un >>\n");
		else if (headp->out_red == PIPE)
			printf("la commande possede un PIPE de sortie\n");
		else
			printf("la commande na pas de redirection de sortie\n");
		
		i = 0;
		if (headp->next != NULL)
		{
			printf("la commande a un pipe\n");
		}

		headp = headp->next;
	}
	printf("\n\nEnvironnement :\n");
	while (heade != NULL)
	{
		printf("%s=", heade->env_name);
		printf("%s	", heade->env_value);
		if (heade->is_exported == true)
			printf("Exporté\n");
		else
			printf("Pas exporté\n");
	 	heade = heade->next;
	}
	printf("\n\n");
}

void	print_com(t_params **para)
{
	t_params	*head;
	int			i;

	head = *para;
	i = 0;
	printf("\nPreCmd : \n\n");
	while (head->com[i] != NULL)
	{
		printf("%s\n", head->com[i]);
		i++;
	}
	printf("\n\n");
}



// static int	count_env_maillon(t_env *env)
// {
// 	int	len;
// 	int	i;

// 	len = 0;
// 	i = 0;
// 	while (env->env_name[i] != '\0')
// 	{
// 		len++;
// 		i++;
// 	}
// 	i = 0;
// 	while (env->env_value[i] != '\0')
// 	{
// 		len++;
// 		i++;
// 	}
// 	return (len + 1);
// }

// char	**get_env(t_env **env)
// {
// 	char	**ex_env;
// 	int		len;
// 	int		i;
// 	t_env	*head;

// 	head = *env;
// 	len = ft_lstsize_env(head);
// 	ex_env = (char **)malloc ((len + 1) * sizeof(char *));
// 	i = 0;
// 	while (head != NULL)
// 	{
// 		len = count_env_maillon(head);
// 		ex_env[i] = (char *)malloc ((len + 1) * sizeof(char));
// 		ex_env[i] = ft_strjoin_c(head->env_name, head->env_value, '=');
// 		i++;
// 		head = head->next;
// 	}
// 	ex_env[i] = NULL;
// 	return (ex_env);
// }

// void	print_env(t_env **env)
// {
// 	char	**monenv;
// 	int i = 0;

// 	monenv = get_env(env);
// 	while (monenv[i])
// 	{
// 		printf("%s\n", monenv[i]);
// 		i++;
// 	}
// }
