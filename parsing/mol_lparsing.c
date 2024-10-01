/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mol_lparsing.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aennaqad <aennaqad@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/24 15:16:29 by aennaqad          #+#    #+#             */
/*   Updated: 2024/09/28 21:33:54 by aennaqad         ###   ########.fr       */
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

void print_tokens(t_tokens *tk)
{
	t_tokens *curr = tk;
	while (curr)
	{
		printf("data : {%s} - flag {%d} - %s \n",curr->data,curr->flag,curr->type);
		curr = curr->next;
	}
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
	head_cmds = parse_heredock(head_cmds, env_to_array(envp));
	if (!syntaxe_error(head_cmds))
	{
		printf("Syntaxe Error ;)\n");
		return (ft_exit_status(258, 1), NULL);
	}
	return (parse_commands(head_cmds));
}
