/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   toknizer.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mes-salh <mes-salh@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/24 15:51:05 by aennaqad          #+#    #+#             */
/*   Updated: 2024/09/27 21:22:21 by mes-salh         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

t_tokens	*createnode(char *value, char *type, int flag)
{
	t_tokens	*node;

	node = ft_malloc((sizeof(t_tokens)), 1);
	if (node == NULL)
		return (NULL);
	node->data = ft_strdup(value);
	node->type = ft_strdup(type);
	node->join_mode = 0;
	node->flag = flag;
	node->next = NULL;
	return (node);
}

void	add_back(t_tokens **head, char *value, char *type, int flag)
{
	t_tokens	*node;
	t_tokens	*curr;

	node = createnode(value, type, flag);
	if (node == NULL)
		return ;
	if (*head == NULL)
		*head = node;
	else
	{
		curr = *head;
		while (curr->next != NULL)
			curr = curr->next;
		curr->next = node;
	}
}

char	*to_linkd_list(t_tokens **head, char *value, char *type, char *start)
{
	if (!ft_strncmp(value, "|", 1))
		add_back(head, value, type, 2);
	else
		add_back(head, value, type, 1);
	return (++start);
}

char	*qtkn(t_tokens **head, char *start, int *in_sngl_qts, int *in_dbl_qts)
{
	if (*start == '\'')
	{
		add_back(head, "\'", "SINGLE_QUOTE", 8);
		*in_sngl_qts = !*in_sngl_qts;
	}
	else
	{
		add_back(head, "\"", "DOUBLE_QUOTE", 7);
		*in_dbl_qts = !*in_dbl_qts;
	}
	return (++start);
}
