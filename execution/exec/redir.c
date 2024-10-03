/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redir.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mes-salh <mes-salh@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/24 19:32:28 by mes-salh          #+#    #+#             */
/*   Updated: 2024/10/03 22:10:20 by mes-salh         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

void	read_redir(char *file)
{
	int		fd;

	fd = open(file, O_RDONLY);
	if (fd == -1)
		err_exit("open");
	safe_dup2(fd, STDIN_FILENO);
	safe_close(fd);
}

void	write_redir(char *file)
{
	int		fd;

	fd = open(file, O_WRONLY | O_CREAT | O_TRUNC, 0644);
	if (fd == -1)
		err_exit("open");
	safe_dup2(fd, STDOUT_FILENO);
	safe_close(fd);
}

void	append_redir(char *file)
{
	int		fd;

	fd = open(file, O_WRONLY | O_CREAT | O_APPEND, 0644);
	if (fd == -1)
		err_exit("open");
	safe_dup2(fd, STDOUT_FILENO);
	safe_close(fd);
}

void	read_heredoc(char *file)
{
	int		fd;

	fd = safe_open(file, O_RDONLY, 0644);
	safe_dup2(fd, STDIN_FILENO);
	unlink(file);
	safe_close(fd);
}

void	handle_redirections(t_redr *redirections)
{
	t_redr	*current;

	current = redirections;
	while (current != NULL)
	{
		if (ft_strcmp(current->type, "<") == 0)
			read_redir(current->redr);
		else if (ft_strcmp(current->type, ">") == 0)
			write_redir(current->redr);
		else if (ft_strcmp(current->type, ">>") == 0)
			append_redir(current->redr);
		else if (ft_strcmp(current->type, "<<") == 0)
			read_heredoc(current->redr);
		current = current->next;
	}
}
