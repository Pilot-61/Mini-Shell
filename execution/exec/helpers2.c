/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   helpers2.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mes-salh <mes-salh@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/15 00:38:50 by mes-salh          #+#    #+#             */
/*   Updated: 2024/09/27 22:25:35 by mes-salh         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

void	copy_env_to_array(t_env *envp, char **env, int key_len, int value_len)
{
	t_env	*temp;
	int		count;

	temp = envp;
	count = 0;
	while (temp)
	{
		key_len = ft_strlen(temp->key);
		value_len = ft_strlen(temp->value);
		env[count] = ft_malloc((key_len + value_len + 2), 1);
		if (!env[count])
			return ;
		ft_strcpy(env[count], temp->key);
		ft_strcat(env[count], "=");
		ft_strcat(env[count], temp->value);
		temp = temp->next;
		count++;
	}
	env[count] = NULL;
}

char	**env_to_array(t_env *envp)
{
	int		count;
	t_env	*temp;
	char	**env_array;
	int		key_len;
	int		value_len;

	temp = envp;
	count = 0;
	while (temp)
	{
		count++;
		temp = temp->next;
	}
	env_array = ft_malloc((sizeof(char *) * (count + 1)), 1);
	if (!env_array)
		return (NULL);
	temp = envp;
	key_len = 0;
	value_len = 0;
	copy_env_to_array(envp, env_array, key_len, value_len);
	return (env_array);
}

void	ft_free(char **ptr)
{
	int	i;

	i = 0;
	while (ptr[i] != NULL)
	{
		free(ptr[i]);
		i++;
	}
	free(ptr);
}

void	free_cmd_list(t_cmd *cmd_list)
{
	t_cmd	*temp;

	while (cmd_list)
	{
		temp = cmd_list;
		cmd_list = cmd_list->next;
		free(temp->cmd);
		free(temp->args);
		free(temp);
	}
}
