/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mes-salh <mes-salh@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/26 13:27:18 by aennaqad          #+#    #+#             */
/*   Updated: 2024/10/04 22:52:48 by mes-salh         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	check_ac(int ac)
{
	if (ac != 1)
	{
		ft_putstr_fd("minishell: minishell: No such file or directory", 2);
		ft_exit_status(127, 1);
		exit(127);
	}
}

int	main(int ac, char **av, char **env)
{
	t_var	var;

	(void)av;
	g_sig_v = 0;
	check_ac(ac);
	var.envp = envinit(env);
	while ('X')
	{
		if (!isatty(0))
			break ;
		handel_sig();
		g_sig_v = 0;
		var.line = readline("--> minishell : ");
		if (!var.line)
			break ;
		var.cmd_list = the_input(var.line, var.envp);
		if (!var.cmd_list || g_sig_v == 1)
		{
			free(var.line);
			continue ;
		}
		(1) && (tcgetattr(0, &var.term), exec(var.cmd_list, &var.envp),
			tcsetattr(1, 0, &var.term), free(var.line), ft_malloc(0, 2), 0);
	}
	return (0);
}
