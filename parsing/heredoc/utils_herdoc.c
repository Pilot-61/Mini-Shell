/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_herdoc.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aennaqad <aennaqad@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/24 16:23:02 by aennaqad          #+#    #+#             */
/*   Updated: 2024/10/05 13:01:19 by aennaqad         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

t_herdoc	*ft_last_her(t_herdoc *lst)
{
	t_herdoc	*tmplst;

	if (!lst)
		return (NULL);
	tmplst = lst;
	while (tmplst->next != NULL)
	{
		tmplst = tmplst->next;
	}
	return (tmplst);
}

t_herdoc	*create_herdoc_node(char **_EOF)
{
	t_herdoc	*node;

	node = ft_malloc((sizeof(t_herdoc)), 1);
	if (node == NULL)
		return (NULL);
	node->_eofs = _EOF;
	node->next = NULL;
	return (node);
}

void	ft_her_add_back(t_herdoc **lst, t_herdoc *newa)
{
	t_herdoc	*last;

	if (!lst)
		return ;
	last = *lst;
	if (last == NULL)
		*lst = newa;
	else
	{
		last = ft_last_her(*lst);
		last->next = newa;
	}
}

int	ft_isalnum(int c)
{
	return ((c >= 'a' && c <= 'z')
		|| (c >= 'A' && c <= 'Z')
		|| (c >= 48 && c <= 57));
}

void	next_skip_spaces(t_tokens **curr)
{
	(*curr) = (*curr)->next;
	while ((*curr) && (*curr)->flag == 3)
		(*curr) = (*curr)->next;
}
