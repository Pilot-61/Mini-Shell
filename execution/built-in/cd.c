/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mes-salh <mes-salh@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/02 23:43:08 by mes-salh          #+#    #+#             */
/*   Updated: 2024/09/28 02:26:20 by mes-salh         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

void	change_dir(char *temp, t_env **envp)
{
	char	old_pwd[PATH_MAX];
	char	new_pwd[PATH_MAX];

	if (getcwd(old_pwd, sizeof(old_pwd)) == NULL)
	{
		printf("PLAYZA: cd: invalid path\n");
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
	{
		printf("PLAYZA: cd: %s: No such file or directory\n", temp);
		return ((void)ft_exit_status(1, 1));
	}
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
