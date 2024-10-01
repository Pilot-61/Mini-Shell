/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mes-salh <mes-salh@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/03 04:09:55 by mes-salh          #+#    #+#             */
/*   Updated: 2024/09/28 23:29:54 by mes-salh         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

void	export_single_arg(t_env **en, char *arg)
{
	char	*k;
	char	*v;
	int		apnd;
	t_env	*existing;

	if (!ft_strchr(arg, '='))
	{
		existing = *en;
		while (existing)
		{
			if (ft_strcmp(existing->key, arg) == 0)
				return ;
			existing = existing->next;
		}
		lstaddb_env(en, lstnew_env(ft_strdup(arg), ft_strdup("")));
		return ;
	}
	(1) && (parse_arg(arg, &k, &v, &apnd), existing = *en, 0);
	while (existing)
	{
		if (ft_strcmp(existing->key, k) == 0)
			return (ex_var(existing, k, v, apnd));
		existing = existing->next;
	}
	(1) && (lstaddb_env(en, lstnew_env(k, v)), free(k), free(v), 0);
}

void	export_multiple_args(t_env **en, char **args)
{
	int	i;

	i = 0;
	while (args[i])
	{
		export_single_arg(en, args[i]);
		i++;
	}
}

void	export(t_env **en, char **args)
{
	export_multiple_args(en, args);
	ft_exit_status(0, 1);
}