/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export2.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mes-salh <mes-salh@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/26 01:48:20 by mes-salh          #+#    #+#             */
/*   Updated: 2024/09/27 03:40:34 by mes-salh         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

void	export_notargs(t_env **envp)
{
	t_env	*temp;

	temp = *envp;
	export_sort_alpha(&temp);
	while (temp)
	{
		if (ft_strcmp(temp->value, "") != 0)
			printf("declare -x %s=\"%s\"\n", temp->key, temp->value);
		else
			printf("declare -x %s\n", temp->key);
		temp = temp->next;
	}
	ft_exit_status(0, 1);
}

void	export_sort_alpha(t_env **envp)
{
	t_env	*temp;
	t_env	*temp2;
	char	*key;
	char	*value;

	temp = *envp;
	while (temp)
	{
		temp2 = temp->next;
		while (temp2)
		{
			if (ft_strcmp(temp->key, temp2->key) > 0)
			{
				key = temp->key;
				value = temp->value;
				temp->key = temp2->key;
				temp->value = temp2->value;
				temp2->key = key;
				temp2->value = value;
			}
			temp2 = temp2->next;
		}
		temp = temp->next;
	}
}
