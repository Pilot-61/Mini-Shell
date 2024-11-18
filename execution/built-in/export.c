/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mes-salh <mes-salh@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/03 04:09:55 by mes-salh          #+#    #+#             */
/*   Updated: 2024/11/18 19:23:34 by mes-salh         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

char	*ft_strstr(const char *haystack, const char *needle)
{
	const char	*h;
	const char	*n;

	if (!*needle)
		return ((char *)haystack);
	while (*haystack)
	{
		h = haystack;
		n = needle;
		while (*h && *n && (*h == *n))
		{
			h++;
			n++;
		}
		if (!*n)
			return ((char *)haystack);
		haystack++;
	}
	return (NULL);
}

int	is_valid_export(char *arg)
{
	t_var	var;

	var.i = 0;
	if (ft_strstr(arg, "+="))
	{
		var.plus_sign = ft_strstr(arg, "+=");
		*(var).plus_sign = '\0';
		if (!ft_isalpha(arg[var.i]) && arg[var.i] != '_')
			return (0);
		var.i++;
		while (arg[var.i])
		{
			if (arg[var.i] == '=')
				return (1);
			if (!ft_isalnum(arg[var.i]) && arg[var.i] != '_')
				return (0);
			var.i++;
		}
		*(var).plus_sign = '+';
		return (1);
	}
	if (!handle_plus_eq2(&var, arg))
		return (0);
	return (1);
}

void	export_multiple_args(t_env **en, char **args)
{
	int	i;

	i = 0;
	while (args[i])
	{
		if (args[i][0] == '\0' || args[i][0] == '='
			|| !is_valid_export(args[i]))
		{
			ft_putstr_fd("minishell: export: `", 2);
			ft_putstr_fd(args[i], 2);
			ft_putstr_fd("': not a valid identifier\n", 2);
			ft_exit_status(1, 1);
		}
		else
			export_single_arg(en, args[i]);
		i++;
	}
}

void	export(t_env **en, char **args)
{
	export_multiple_args(en, args);
	ft_exit_status(0, 1);
}
