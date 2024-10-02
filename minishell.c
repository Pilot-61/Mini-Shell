/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mes-salh <mes-salh@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/26 13:27:18 by aennaqad          #+#    #+#             */
/*   Updated: 2024/10/02 13:47:27 by mes-salh         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"



int	main(int ac, char **av, char **env)
{
	t_var	var;

	(void)av;
	g_sig_v = 0;
	if (ac != 1)
	{
		printf("minishell: minishell: No such file or directory");
		ft_exit_status(127, 1);
		exit(127);
	}
	var.envp = envinit(env);
	while (isatty(0))
	{
		handel_sig();
		var.line = readline("--> minishell : ");
		var.cmd_list = the_input(var.line, var.envp);
		if (!var.cmd_list)
		{
			free(var.line);
			continue ;
		}
		g_sig_v = 1;
		// printList_tcmd(var.cmd_list);
		tcgetattr(0, &var.term);
		exec(var.cmd_list, &var.envp);
		tcsetattr(1, 0, &var.term);
		g_sig_v = 0;
		free(var.line);
		ft_malloc(0, 2);
	}
	return (0);
}
