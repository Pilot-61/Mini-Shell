/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   echo.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mes-salh <mes-salh@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/03 01:31:43 by mes-salh          #+#    #+#             */
/*   Updated: 2024/09/28 20:19:24 by mes-salh         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

static int	is_n_flag(const char *str)
{
	if (*str != '-')
		return (0);
	str++;
	while (*str == 'n')
		str++;
	return (*str == '\0' || *str == ' ');
}

void	check_arg(char *arg)
{
	if (!arg)
	{
		write(STDOUT_FILENO, "\n", 1);
		return ;
	}
}

void	echo(char *arg)
{
	int	skip_newline;
	int	arg_len;

	skip_newline = 0;
	check_arg(arg);
	while (*arg == ' ')
		arg++;
	while (is_n_flag(arg))
	{
		skip_newline = 1;
		while (*arg != ' ' && *arg != '\0')
			arg++;
		while (*arg == ' ')
			arg++;
	}
	if (*arg != '\0')
	{
		arg_len = ft_strlen(arg);
		write(STDOUT_FILENO, arg, arg_len);
	}
	if (!skip_newline)
		write(STDOUT_FILENO, "\n", 1);
	ft_exit_status(0, 1);
}
