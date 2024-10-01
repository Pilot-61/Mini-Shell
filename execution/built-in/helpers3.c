/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   helpers3.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mes-salh <mes-salh@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/06 03:46:38 by mes-salh          #+#    #+#             */
/*   Updated: 2024/09/15 00:57:04 by mes-salh         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

int	ft_isalpha(int c)
{
	return ((c >= 'a' && c <= 'z') || (c >= 'A' && c <= 'Z') || c == '_');
}

int	is_valid_key(char *key)
{
	int	i;

	i = 0;
	if (!ft_isalpha(key[i]))
		return (0);
	while (key[++i])
	{
		if (!ft_isalnum(key[i]))
			return (0);
	}
	return (1);
}

int	check_exp(char *arg)
{
	if (!is_valid_key(arg))
	{
		printf("minishell: export: `%s': not a valid identifier\n", arg);
		return (0);
	}
	return (1);
}
