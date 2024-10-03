/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   f_parsing.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mes-salh <mes-salh@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/24 15:16:29 by aennaqad          #+#    #+#             */
/*   Updated: 2024/10/03 22:50:04 by mes-salh         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	ft_exit_status(int exit, int type)
{
	static int	status;

	if (type == 1)
		status = exit;
	return (status);
}

t_cmd	*the_input(char *line, t_env *envp)
{
	t_tokens	*head_cmds;

	head_cmds = NULL;
	if (!line)
		exit(EXIT_FAILURE);
	if (is_empty_line(line))
		return (NULL);
	if (line)
		add_history(line);
	if (!open_close_quote(line))
		return (NULL);
	head_cmds = parser(parser_commands(tokenize(line), env_to_array(envp)));
	parse_heredock(head_cmds, env_to_array(envp));
	if (!syntaxe_error(head_cmds))
	{
		ft_putstr_fd("Syntaxe Error ;)\n", 2);
		return (ft_exit_status(258, 1), NULL);
	}
	return (parse_commands(head_cmds));
}
