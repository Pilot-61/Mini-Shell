/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   built_in.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mes-salh <mes-salh@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/02 00:27:13 by mes-salh          #+#    #+#             */
/*   Updated: 2024/10/03 20:40:00 by mes-salh         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

char	*cargs(char **arg)
{
	int		i;
	int		len;
	char	*result;

	i = -1;
	len = 0;
	while (arg && arg[++i] != NULL)
	{
		len += ft_strlen(arg[i]);
		if (arg[i + 1])
			len++;
	}
	result = ft_malloc((len + 1), 1);
	if (!result)
		return (NULL);
	result[0] = '\0';
	i = -1;
	while (arg && arg[++i] != NULL)
	{
		ft_strcat(result, arg[i]);
		if (arg[i + 1])
			ft_strcat(result, " ");
	}
	return (result);
}

int	is_buit_in(t_cmd *c, t_env **envp)
{
	char	*cmd;
	char	*arg;
	t_cmd	*t;

	(1) && (t = c, cmd = ft_strdup(t->cmd), arg = cargs(&t->args[1]), 0);
	if (ft_strcmp(cmd, "env") == 0)
		return (printenv(*envp), 1);
	else if (ft_strcmp(cmd, "pwd") == 0)
		return (get_cwd(), 1);
	else if (ft_strcmp(cmd, "echo") == 0)
		return (echo(arg), 1);
	else if (ft_strcmp(cmd, "cd") == 0)
		return (change_dir(arg, envp), 1);
	else if (ft_strcmp(cmd, "export") == 0)
	{
		if (c->args[1] == NULL)
			return (export_notargs(envp), 1);
		else
			return (export(envp, &c->args[1]), 1);
	}
	else if (ft_strcmp(cmd, "unset") == 0)
		return (unset(envp, arg), 1);
	else if (ft_strcmp(cmd, "exit") == 0)
		return (exit_shell(*envp, t), 1);
	return (0);
}
