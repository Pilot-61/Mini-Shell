/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cmd_tools.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mes-salh <mes-salh@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/24 15:50:44 by aennaqad          #+#    #+#             */
/*   Updated: 2024/09/27 21:22:53 by mes-salh         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

t_cmd	*new_cmd_node(char **content, t_redr *head_red)
{
	t_cmd	*node;

	node = (t_cmd *)ft_malloc((sizeof(t_cmd)), 1);
	if (!node)
		return (NULL);
	if (content[0] == NULL)
		node->args = NULL;
	else
		node->args = content;
	node->redirections = head_red;
	node->cmd = content[0];
	node->next = NULL;
	return (node);
}

t_redr	*create_red_node(char *red, char *type)
{
	t_redr	*node;

	node = ft_malloc((sizeof(t_redr)), 1);
	if (node == NULL)
		return (NULL);
	node->redr = ft_strdup(red);
	node->type = ft_strdup(type);
	node->next = NULL;
	return (node);
}

void	add_red_back(t_redr **head_red, t_redr *node)
{
	t_redr	*curr;

	if (*head_red == NULL)
		*head_red = node;
	else
	{
		curr = *head_red;
		while (curr->next != NULL)
			curr = curr->next;
		curr->next = node;
	}
}

void	add_cmd_back(t_cmd **head_cmds, t_cmd *node)
{
	t_cmd	*curr;

	if (*head_cmds == NULL)
		*head_cmds = node;
	else
	{
		curr = *head_cmds;
		while (curr->next != NULL)
			curr = curr->next;
		curr->next = node;
	}
}

void	create_linkd_list_red(t_parser *var)
{
	var->red = ft_strdup(var->curr->data);
	var->curr = var->curr->next;
	while (var->curr && var->curr->flag == 3)
		var->curr = var->curr->next;
	var->node_redirection = create_red_node(var->curr->data, var->red);
	add_red_back(&var->head_red, var->node_redirection);
}
