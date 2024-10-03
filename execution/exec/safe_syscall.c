/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   safe_syscall.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mes-salh <mes-salh@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/24 20:31:26 by mes-salh          #+#    #+#             */
/*   Updated: 2024/10/02 15:22:53 by mes-salh         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

void	err_exit(char *msg)
{
	perror(msg);
	exit(EXIT_FAILURE);
}

pid_t	safe_fork(void)
{
	pid_t	pid;

	pid = fork();
	if (pid == -1)
		err_exit("fork");
	return (pid);
}

void	safe_dup2(int old_fd, int new_fd)
{
	if (dup2(old_fd, new_fd) == -1)
		err_exit("dup2");
}

int	safe_open(char *file, int flags, int mode)
{
	int	fd;

	fd = open(file, flags, mode);
	if (fd == -1)
		err_exit("open");
	return (fd);
}

void	safe_close(int fd)
{
	if (close(fd) == -1)
		err_exit("close");
}
