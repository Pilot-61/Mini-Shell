/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execution.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mes-salh <mes-salh@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/24 19:03:37 by mes-salh          #+#    #+#             */
/*   Updated: 2024/09/30 19:21:38 by mes-salh         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	exec(t_cmd *cmd_list, t_env **envp)
{
	t_cmd		*current_cmd;
	int			cmds;
	t_control	control;

	init_control(&control);
	cmds = command_count(cmd_list);
	current_cmd = cmd_list;
	signal(SIGQUIT, handle_sig_child);
	signal(SIGINT, handle_sig_child);
	if (cmds == 1 && builin_checker(current_cmd, envp, control))
	{
		close(control.old_stdin);
		close(control.old_stdout);
		return ;
	}
	else
		exec_pip(cmd_list, cmds, *envp);
	close(control.old_stdin);
	close(control.old_stdout);
}
