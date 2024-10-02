/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mol_lparsing.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mes-salh <mes-salh@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/24 15:16:29 by aennaqad          #+#    #+#             */
/*   Updated: 2024/10/02 13:50:02 by mes-salh         ###   ########.fr       */
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

void	printList_tcmd(t_cmd *lst)
{
	t_cmd *curr = lst;

	while (curr)
	{
		int i = 0;
		printf("\033[31mcmd : %s \033[0m\n", curr->cmd);
		while (curr->args && curr->args[i]) {
			printf("\033[1;32margs(%d)\033[0m : {%s} \033[0m\n",i, curr->args[i]);
			i++;
		}
		t_redr *re =  curr->redirections;
		printf("----- redirection Linked List ---- \n");
		int g = 0;
		while (re)
		{
				printf("\033[0;32m----- redirection Node %d ---- \033[0m\n", g);
			printf("\033[1;33mtype of redirection : [%s]\n\033[0m",re->type);
			printf("\033[1;33mname of file to open : [%s]\n\033[0m",re->redr);
			g++;
			re = re->next;
		}
		free(re);
		curr = curr->next;
		printf("\033[34m------------ Next Cmd ---------\033[0m\n");
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
	// print_tokens(head_cmds);
	if (!syntaxe_error(head_cmds))
	{
		printf("Syntaxe Error ;)\n");
		return (ft_exit_status(258, 1), NULL);
	}
	return (parse_commands(head_cmds));
}
