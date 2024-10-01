/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signals_minishell.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mes-salh <mes-salh@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/24 17:04:32 by aennaqad          #+#    #+#             */
/*   Updated: 2024/09/30 19:17:45 by mes-salh         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

void	ft_sig(int a)
{
	if (g_sig_v == 0)
	{
		if (a == SIGINT)
		{
			write(1, "\n", 1);
			rl_on_new_line();
			rl_replace_line("", 0);
			rl_redisplay();
		}
	}
}

void	handle_sig_child(int a)
{
	if (g_sig_v == 1)
	{
		if (a == SIGQUIT)
		{
			dprintf(1, "Quit : 3\n");
		}
		if (a == SIGINT)
		{
			rl_on_new_line();
		}
	}
}

void	handel_sig(void)
{
	signal(SIGINT, ft_sig);
	signal(SIGQUIT, ft_sig);
	rl_catch_signals = 0;
}
