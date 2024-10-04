/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mes-salh <mes-salh@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/26 13:27:18 by aennaqad          #+#    #+#             */
/*   Updated: 2024/10/04 17:32:47 by mes-salh         ###   ########.fr       */
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
	while (isatty(0))
	{
		handel_sig();
		g_sig_v = 0;
		var.line = readline("--> minishell : ");
		var.cmd_list = the_input(var.line, var.envp);
		if (!var.cmd_list || g_sig_v == 1)
		{
			free(var.line);
			continue ;
		}
		tcgetattr(0, &var.term);
		exec(var.cmd_list, &var.envp);
		tcsetattr(1, 0, &var.term);
		free(var.line);
		ft_malloc(0, 2);
	}
	return (0);
}
