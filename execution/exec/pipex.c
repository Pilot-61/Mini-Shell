/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mes-salh <mes-salh@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/24 19:46:59 by mes-salh          #+#    #+#             */
/*   Updated: 2024/10/01 19:49:15 by mes-salh         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

void	cprocess(t_cmd *current_cmd, int p_pipe, int p_fd[2], t_env *env)
{
	if (p_pipe != STDIN_FILENO)
	{
		dup2(p_pipe, STDIN_FILENO);
		close(p_pipe);
	}
	if (p_fd[1] != STDOUT_FILENO)
	{
		close(p_fd[0]);
		dup2(p_fd[1], STDOUT_FILENO);
		close(p_fd[1]);
	}
	handle_redirections(current_cmd->redirections);
	if (current_cmd->cmd && is_buit_in(current_cmd, &env))
	{
		ft_exit_status(0, 1);
		close(p_fd[0]);
		close(p_fd[1]);
		close(current_cmd->control.old_stdin);
		close(current_cmd->control.old_stdout);
		exit(EXIT_SUCCESS);
	}
	exec_cmd(current_cmd, env_to_array(env), env);
	exit(EXIT_FAILURE);
}

void	wait_for_child_processes(int command_count, int pid)
{
	int	i;
	int	status;

	i = 0;
	status = 0;
	if (waitpid(pid, &status, 0) != -1)
	{
		if (WIFEXITED(status))
			status = WEXITSTATUS(status);
		else if (WIFSIGNALED(status))
			status = WTERMSIG(status) + 128;
		ft_exit_status(status, 1);
	}
	while (i < command_count - 1)
	{
		wait(NULL);
		i++;
	}
}

void	err_exit(char *msg)
{
	perror(msg);
	exit(EXIT_FAILURE);
}

void	exec_pip(t_cmd *commands, int command_count, t_env *env)
{
	int		i;
	int		p_fd[2];
	int		p_pipe;
	pid_t	pid;
	t_cmd	*current_cmd;

	(1) && (i = -1, p_pipe = STDIN_FILENO, current_cmd = commands, 0);
	while (++i < command_count)
	{
		if (i < command_count - 1 && pipe(p_fd) == -1)
			err_exit("pipe");
		pid = fork();
		if (pid == -1)
			(1) && (dup2(STDIN_FILENO, p_fd[0]), dup2(STDOUT_FILENO, p_fd[1]),
				close(p_fd[0]), close(p_fd[1]), err_exit("fork"), 0);
		if (pid == 0)
			cprocess(current_cmd, p_pipe, p_fd, env);
		else
		{
			if (i > 0)
				close(p_pipe);
			if (i < command_count - 1)
				(1) && (close(p_fd[1]), p_pipe = p_fd[0], 0);
		}
		current_cmd = current_cmd->next;
	}
	wait_for_child_processes(command_count, pid);
}
