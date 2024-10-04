/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_atoi.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mes-salh <mes-salh@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/04 16:56:49 by mes-salh          #+#    #+#             */
/*   Updated: 2024/10/04 17:40:07 by mes-salh         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

int	exit_code_check(int exit_code)
{
	if (exit_code > 255)
		exit_code = exit_code % 256;
	else if (exit_code < 0)
		exit_code = 256 + exit_code;
	else if (exit_code == 1)
		exit(EXIT_FAILURE);
	return (exit_code);
}

void	print_err(void)
{
	ft_putstr_fd("minishell: exit: numeric argument required\n", 2);
	exit(255);
}

long	my_atoi(char *str)
{
	int			i;
	long		s;
	long		r;

	r = 0;
	s = 1;
	i = 0;
	while (str[i] == ' ' || (str[i] >= 9 && str[i] <= 13))
		i++;
	if (str[i] == '+' || str[i] == '-')
	{
		if (str[i] == '-')
			s = s * -1;
		i++;
	}
	while (str[i] >= '0' && str[i] <= '9')
	{
		r = r * 10 + str[i] - '0';
		if ((r * s) > INT_MAX || (r * s) < INT_MIN)
			print_err();
		i++;
	}
	return (s * r);
}
