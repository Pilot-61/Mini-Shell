/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mes-salh <mes-salh@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/14 07:25:18 by mes-salh          #+#    #+#             */
/*   Updated: 2024/09/30 19:23:56 by mes-salh         ###   ########.fr       */
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
		if (access(cmd, X_OK | F_OK) == 0)
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
	char	*full_path;

	full_path = find_command_in_path(command->cmd, env);
	if (!full_path)
	{
		printf("minishell: %s: command not found\n", command->cmd);
		ft_exit_status(127, 1);
		exit(127);
	}
	if (execve(full_path, command->args, envp) == -1)
	{
		if (ft_strcmp(command->cmd, "") == 0)
			printf("minishell: %s: command not found\n", command->cmd);
		else
			printf("minishell: %s: %s\n", command->cmd, strerror(errno));
		ft_exit_status(126, 1);
		exit(126);
	}
}

void	exec_cmd(t_cmd *command, char **env, t_env *envp)
{
	if (command->cmd == NULL)
	{
		printf("minishell: : command not found\n");
		ft_exit_status(1, 1);
		exit(1);
	}
	execution(command, env, envp);
}
