/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   helpers4.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mes-salh <mes-salh@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/03 22:11:44 by mes-salh          #+#    #+#             */
/*   Updated: 2024/10/03 22:20:33 by mes-salh         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"
#include <sys/stat.h>

void	check_if_directory(t_cmd *command)
{
	struct stat	st;

	if (stat(command->cmd, &st) == 0 && S_ISDIR(st.st_mode))
	{
		ft_putstr_fd("minishell: ", 2);
		ft_putstr_fd(command->cmd, 2);
		ft_putstr_fd(": is a directory\n", 2);
		ft_exit_status(126, 1);
		exit(126);
	}
	else if ((command->cmd[strlen(command->cmd) - 1] == '/')
		&& !(S_ISDIR(st.st_mode)))
	{
		ft_putstr_fd("minishell: ", 2);
		ft_putstr_fd(command->cmd, 2);
		ft_putstr_fd(": is not a directory\n", 2);
		ft_exit_status(126, 1);
		exit(126);
	}
}

void	cmd_not_found(char *cmd)
{
	ft_putstr_fd("minishell: ", 2);
	ft_putstr_fd(cmd, 2);
	ft_putstr_fd(": command not found\n", 2);
	ft_exit_status(127, 1);
}

void	errno_msg(char *cmd)
{
	ft_putstr_fd("minishell: ", 2);
	ft_putstr_fd(cmd, 2);
	ft_putstr_fd(": ", 2);
	ft_putstr_fd(strerror(errno), 2);
	ft_putstr_fd("\n", 2);
	ft_exit_status(126, 1);
}
