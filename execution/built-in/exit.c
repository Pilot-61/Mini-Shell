/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mes-salh <mes-salh@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/07 02:57:26 by mes-salh          #+#    #+#             */
/*   Updated: 2024/09/28 19:28:51 by mes-salh         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

void	free_env(t_env **env)
{
	t_env	*temp;

	while (*env)
	{
		temp = *env;
		*env = (*env)->next;
		free(temp->key);
		free(temp->value);
		free(temp);
	}
}

int	ft_isdigit(int c)
{
	return (c >= '0' && c <= '9');
}

int	is_numeric(const char *str)
{
	if (*str == '-' || *str == '+')
		str++;
	if (!*str)
		return (0);
	while (*str)
	{
		if (!ft_isdigit(*str))
			return (0);
		str++;
	}
	return (1);
}

int	exit_many_args(t_cmd *arg)
{
	if (arg->args[1] && arg->args[2])
	{
		if (is_numeric(arg->args[1]))
		{
			printf("minishell: exit: too many arguments\n");
			return (1);
		}
		else
		{
			printf("minishell: exit: %s: numeric argument required\n",
				arg->args[1]);
			exit(255);
		}
	}
	return (0);
}

void	exit_shell(t_env *env, t_cmd *arg)
{
	int		exit_code;

	exit_code = 0;
	if (arg->args[1] && arg->args[2])
	{
		exit_code = exit_many_args(arg);
		if (exit_code)
			return ;
		free_env(&env);
	}
	else if (arg->args[1])
	{
		if (is_numeric(arg->args[1]))
			exit_code = atoi(arg->args[1]);
		else
		{
			printf("minishell: exit: %s: numeric argument required\n",
				arg->args[1]);
			exit_code = 255;
		}
	}
	free_env(&env);
	exit(exit_code);
}
