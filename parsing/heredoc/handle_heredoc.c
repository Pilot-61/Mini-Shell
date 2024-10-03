/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handle_heredoc.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mes-salh <mes-salh@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/24 15:57:26 by aennaqad          #+#    #+#             */
/*   Updated: 2024/10/03 22:49:16 by mes-salh         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"
#include <unistd.h>

int	is_not_dlr(char *str)
{
	int	i;

	i = 0;
	while (str[i])
	{
		if (str[i] == '$')
			return (0);
		i++;
	}
	return (1);
}

void	handle_signal(int sig)
{
	(void)sig;
	if (sig == SIGINT)
	{
		close(0);
		g_sig_v = 1;
	}
}

void	expand_her(char *l, char **env, int fd)
{
	char	*exapned_l;

	exapned_l = NULL;
	exapned_l = ft_strdup(expand_dlr_args(l, env));
	write(fd, exapned_l, ft_strlen(exapned_l));
	exapned_l = NULL;
}

void	handle_file(t_tokens **curr, int *fd, int *i, char **env)
{
	char	*f_name;

	f_name = ft_strjoin("/tmp/file_", ft_itoa(*i));
	next_skip_spaces(curr);
	while ('X')
	{
		if (access(f_name, F_OK) == -1)
		{
			*fd = open(f_name, O_WRONLY | O_CREAT | O_TRUNC, 0644);
			if (*fd == -1)
				err_exit("open");
			break ;
		}
		else
		{
			(1) && ((*i)++, f_name = ft_strjoin("/tmp/file_", ft_itoa(*i)), 0);
			continue ;
		}
		(*i)++;
	}
	handle_herdoc_del(curr, env, *fd, f_name);
	close(*fd);
}

void	parse_heredock(t_tokens *line, char **env)
{
	int			fd;
	int			i;
	t_tokens	*curr;

	i = 2024;
	curr = line;
	signal(SIGINT, handle_signal);
	while (curr)
	{
		if (g_sig_v == 1)
			break ;
		if (!ft_strncmp(curr->type, "HEREDOC", 7))
			handle_file(&curr, &fd, &i, env);
		if (curr)
			curr = curr->next;
	}
}
