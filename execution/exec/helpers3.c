/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   helpers3.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mes-salh <mes-salh@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/24 22:40:25 by mes-salh          #+#    #+#             */
/*   Updated: 2024/09/29 00:20:12 by mes-salh         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

int	built_in_check(char *command)
{
	if (ft_strcmp(command, "echo") == 0)
		return (1);
	else if (ft_strcmp(command, "cd") == 0)
		return (1);
	else if (ft_strcmp(command, "pwd") == 0)
		return (1);
	else if (ft_strcmp(command, "export") == 0)
		return (1);
	else if (ft_strcmp(command, "unset") == 0)
		return (1);
	else if (ft_strcmp(command, "env") == 0)
		return (1);
	else if (ft_strcmp(command, "exit") == 0)
		return (1);
	return (0);
}

void	my_dup2(int old_stdin, int old_stdout)
{
	if (dup2(old_stdin, STDIN_FILENO) == -1)
		err_exit("dup2");
	if (dup2(old_stdout, STDOUT_FILENO) == -1)
		err_exit("dup2");
	if (close(old_stdin) == -1)
		err_exit("close");
	if (close(old_stdout) == -1)
		err_exit("close");
}

void	init_control(t_control *control)
{
	control->old_stdin = dup(STDIN_FILENO);
	control->old_stdout = dup(STDOUT_FILENO);
}

void	child_helper(t_cmd *current_cmd, t_env *env)
{
	handle_redirections(current_cmd->redirections);
	if (current_cmd->cmd)
		exec_cmd(current_cmd, env_to_array(env), env);
	exit(EXIT_SUCCESS);
}

int	builin_checker(t_cmd *current_cmd, t_env **envp, t_control control)
{
	if (current_cmd->args && built_in_check(current_cmd->cmd))
	{
		if (current_cmd->redirections)
			handle_redirections(current_cmd->redirections);
		if (is_buit_in(current_cmd, envp))
			my_dup2(control.old_stdin, control.old_stdout);
		return (1);
	}
	return (0);
}
