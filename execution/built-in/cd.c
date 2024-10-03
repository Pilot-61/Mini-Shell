/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mes-salh <mes-salh@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/02 23:43:08 by mes-salh          #+#    #+#             */
/*   Updated: 2024/10/03 22:18:30 by mes-salh         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

void	cd_error(char *temp)
{
	ft_putstr_fd("minishell: cd:", 2);
	ft_putstr_fd(temp, 2);
	ft_putstr_fd(": No such file or directory\n", 2);
	ft_exit_status(1, 1);
}

void	change_dir(char *temp, t_env **envp)
{
	char	old_pwd[PATH_MAX];
	char	new_pwd[PATH_MAX];

	if (getcwd(old_pwd, sizeof(old_pwd)) == NULL)
	{
		ft_putstr_fd("minishell: cd: invalid path\n", 2);
		chdir(temp);
		if (getcwd(new_pwd, sizeof(new_pwd)) == NULL)
			return ((void)ft_exit_status(1, 1));
		update_env(envp, "OLDPWD", old_pwd);
		update_env(envp, "PWD", new_pwd);
		return ((void)ft_exit_status(0, 1));
	}
	if (temp == NULL || *temp == '\0')
		temp = getenv("HOME");
	if (chdir(temp) != 0)
		return (cd_error(temp));
	if (getcwd(new_pwd, sizeof(new_pwd)) == NULL)
		return ((void)ft_exit_status(1, 1));
	update_env(envp, "OLDPWD", old_pwd);
	update_env(envp, "PWD", new_pwd);
	ft_exit_status(0, 1);
}

void	update_env(t_env **envp, const char *key, const char *value)
{
	t_env	*env;

	env = *envp;
	while (env)
	{
		if (strcmp(env->key, key) == 0)
		{
			free(env->value);
			env->value = ft_strdup2(value);
			return ;
		}
		env = env->next;
	}
	lstaddb_env(envp, lstnew_env(ft_strdup(key), ft_strdup(value)));
}
