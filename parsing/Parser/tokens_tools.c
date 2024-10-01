/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tokens_tools.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aennaqad <aennaqad@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/30 22:00:32 by aennaqad          #+#    #+#             */
/*   Updated: 2024/09/28 22:02:38 by aennaqad         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

t_tokens	*ft_last_tkn(t_tokens *lst)
{
	t_tokens	*tmplst;

	if (!lst)
		return (NULL);
	tmplst = lst;
	while (tmplst->next != NULL)
	{
		tmplst = tmplst->next;
	}
	return (tmplst);
}

void	ft_tkn_add_back(t_tokens **lst, t_tokens *newa)
{
	t_tokens	*last;

	if (!lst)
		return ;
	last = *lst;
	if (last == NULL)
		*lst = newa;
	else
	{
		last = ft_last_tkn(*lst);
		last->next = newa;
	}
}

t_tokens	*ft_new_token(void *content)
{
	t_tokens	*node;

	node = (t_tokens *)ft_malloc((sizeof(t_tokens)), 1);
	if (!node)
		return (NULL);
	node->data = content;
	node->next = NULL;
	return (node);
}

void	copy_and_add_to_list(t_tokens *curr, t_tokens **new_head)
{
	t_tokens	*new_token;

	if (!ft_strcmp(curr->data, "\x03"))
		return ;
	new_token = copy_node(curr);
	if (new_token)
		ft_tkn_add_back(new_head, new_token);
}

t_tokens	*copy_node(t_tokens *node)
{
	t_tokens	*new_node;

	new_node = ft_malloc((sizeof(t_tokens)), 1);
	if (!new_node)
	{
		printf("Failed to allocate memory for new node.\n");
		return (NULL);
	}
	if (node->flag == 7 || node->flag == 8)
	{
		new_node->data = ft_strdup("");
		new_node->type = ft_strdup("EMPTY");
		new_node->flag = 777;
	}
	else
	{
		new_node->flag = node->flag;
		new_node->data = ft_strdup(node->data);
		new_node->type = ft_strdup(node->type);
	}
	new_node->join_mode = 0;
	new_node->next = NULL;
	return (new_node);
}
