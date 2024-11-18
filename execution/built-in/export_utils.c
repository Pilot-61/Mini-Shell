/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export_utils.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mes-salh <mes-salh@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/04 20:48:29 by mes-salh          #+#    #+#             */
/*   Updated: 2024/11/18 19:20:52 by mes-salh         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

int	hadnle_eq(char *arg, t_var *var, t_env **en)
{
	char	*s;
	char	*ss;

	if (!ft_strchr(arg, '='))
	{
		var->existing = *en;
		while (var->existing)
		{
			if (ft_strcmp(var->existing->key, arg) == 0)
				return (0);
			var->existing = var->existing->next;
		}
		s = ft_strdup2(arg);
		ss = ft_strdup2("");
		lstad(en, lstnew_env(s, ss));
		free(s);
		free(ss);
		return (0);
	}
	return (1);
}

void	handle_exist(t_var *var)
{
	if (var->apnd)
	{
		var->new_value = ft_strjoin2(var->existing->value, var->v);
		free(var->existing->value);
		var->existing->value = var->new_value;
	}
	else
	{
		free(var->existing->value);
		var->existing->value = ft_strdup2(var->v);
	}
}

void	handle_plus_eq(t_var *var, char *arg)
{
	if (ft_strstr(arg, "+="))
	{
		var->plus_sign = ft_strstr(arg, "+=");
		*(var->plus_sign) = '\0';
		var->ke = ft_strdup2(arg);
		var->v = ft_strdup2(var->plus_sign + 2);
		var->apnd = 1;
	}
	else
		parse_arg(arg, &var->ke, &var->v, &var->apnd);
}

void	export_single_arg(t_env **en, char *arg)
{
	t_var	var;

	var.ke = NULL;
	var.v = NULL;
	if (!hadnle_eq(arg, &var, en))
	{
		free(var.ke);
		free(var.v);
		return ;
	}
	handle_plus_eq(&var, arg);
	var.existing = *en;
	while (var.existing)
	{
		if (ft_strcmp(var.existing->key, var.ke) == 0)
		{
			handle_exist(&var);
			free(var.ke);
			free(var.v);
			return ;
		}
		var.existing = var.existing->next;
	}
	(1) && (lstad(en, lstnew_env(var.ke, var.v)), free(var.ke), free(var.v), 0);
}

int	handle_plus_eq2(t_var *var, char *arg)
{
	if (!ft_isalpha(arg[var->i]) && arg[var->i] != '_')
		return (0);
	var->i++;
	while (arg[var->i] && arg[var->i] != '=')
	{
		if (!ft_isalnum(arg[var->i]) && arg[var->i] != '_')
			return (0);
		var->i++;
	}
	return (1);
}
