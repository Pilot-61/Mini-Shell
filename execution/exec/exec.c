/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mes-salh <mes-salh@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/14 07:25:18 by mes-salh          #+#    #+#             */
/*   Updated: 2024/10/05 00:34:37 by mes-salh         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

char	*my_getenv(char *name, t_env *env)
{
	t_env	*current;

	current = env;
	while (current)
	{
		if (ft_strcmp(current->key, name) == 0)
			return (current->value);
		current = current->next;
	}
	return (NULL);
}

char	*fill_path(char *dir, char *cmd, char *full_path)
{
	while (dir)
	{
		full_path = ft_malloc((ft_strlen(dir) + ft_strlen(cmd) + 2), 1);
		if (!full_path)
			return (NULL);
		ft_strcpy(full_path, dir);
		ft_strcat(full_path, "/");
		ft_strcat(full_path, cmd);
		if (access(full_path, X_OK | F_OK) == 0)
			return (full_path);
		dir = my_split(NULL, ":");
	}
	return (NULL);
}

char	*find_command_in_path(const char *cmd, t_env *g_env)
{
	char	*path;
	char	*path_copy;
	char	*dir;
	char	*full_path;

	if ((cmd[0] == '.' && cmd[1] == '/' ) || cmd[0] == '/')
	{
		if (access(cmd, F_OK) == 0)
			return (ft_strdup(cmd));
		return (NULL);
	}
	path = my_getenv("PATH", g_env);
	if (!path)
		return (NULL);
	path_copy = ft_strdup(path);
	dir = my_split(path_copy, ":");
	full_path = NULL;
	return (fill_path(dir, (char *)cmd, full_path));
}

void	execution(t_cmd *command, char **envp, t_env *env)
{
	char		*full_path;

	check_if_directory(command);
	full_path = find_command_in_path(command->cmd, env);
	if (!full_path)
		return (cmd_not_found(command->cmd));
	if (execve(full_path, command->args, envp) == -1)
	{
		if (ft_strcmp(command->cmd, "") == 0)
		{
			ft_putstr_fd("minishell: ", 2);
			ft_putstr_fd(command->args[0], 2);
			ft_putstr_fd(": command not found\n", 2);
			ft_exit_status(127, 1);
			exit(127);
		}
		else if (access(command->cmd, X_OK) == 0)
			exit(126);
		else
			errno_msg(command->cmd);
	}
}

void	exec_cmd(t_cmd *command, char **env, t_env *envp)
{
	if (command->cmd == NULL)
	{
		ft_exit_status(1, 1);
		exit(1);
	}
	execution(command, env, envp);
}
