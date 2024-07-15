/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ms_puts.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: njeanbou <njeanbou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/27 13:31:52 by ichpakov          #+#    #+#             */
/*   Updated: 2024/07/10 16:09:14 by njeanbou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

/* ms_input:
*   ouvre le fichier d'input si c'est possible.
*/
void	ms_input(t_data *data, t_put *puts)
{
	close_file(data->fd_in);
	data->fd_in = open_file(puts->input, 0);
	if (data->fd_in == -1)
	{
		exec_error(1);
		return ;
	}
	dup2(data->fd_in, 0);
}

/* ms_output:
*   ouvre le fichier de sortie pour une ecriture 
*   qui ecrase le fichier ou non.
*/
void	ms_output(t_data *data, t_put *puts, int rdr)
{
	close_file(data->fd_out);
	if (rdr == 1)
		data->fd_out = open_file(puts->output, 1);
	else
		data->fd_out = open_file(puts->output, 2);
	if (data->fd_out == -1)
	{
		exec_error(2);
		return ;
	}
	dup2(data->fd_out, 1);
}
