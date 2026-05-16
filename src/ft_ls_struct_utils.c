/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_ls_struct_utils.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tel-bouh <tariqelbouhali039@gmail.com>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/05/16 17:18:11 by tel-bouh          #+#    #+#             */
/*   Updated: 2026/05/16 23:43:48 by tel-bouh         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "./ft_ls.h"

t_short_format	*ft_add_new(void *data, size_t size)
{
	t_short_format	*node;
	size_t		i;

	node = (t_short_format *)malloc(sizeof(t_short_format));
	if (!node)
		return (NULL);

	node->data = malloc(size);
	if (!node->data)
	{
		free(node);
		return (NULL);
	}
	i = 0;
	while (i < size)
	{
		((char *)node->data)[i] = ((char *)data)[i];
		i++;
	}
	node->next = NULL;
	return (node);
}


void	ft_push_back(t_short_format **head, t_short_format *new_node)
{
	t_short_format *tmp;

	if (!head || !new_node)
	    return;

	if (!*head)
	{
		*head = new_node;
		return;
	}

	tmp = *head;
	while (tmp->next)
		tmp = tmp->next;

	tmp->next = new_node;
}

void	ft_delete_all(t_short_format **head)
{
	t_short_format *tmp;

	while (*head)
	{
		tmp = (*head)->next;
		free((*head)->data);
		free(*head);
		*head = tmp;
	}
}
