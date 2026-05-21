/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_ls_struct_utils.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tel-bouh <tariqelbouhali039@gmail.com>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/05/16 17:18:11 by tel-bouh          #+#    #+#             */
/*   Updated: 2026/05/21 02:16:59 by tel-bouh         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "./ft_ls.h"

t_short_format	*ft_add_new(void *data, size_t size, struct stat st, char *prnt_dir)
{
	t_short_format	*node;
	size_t		i;
	int		j;

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
	j = 0; 
	while (prnt_dir[j]) 
	{ 
		node->prnt_dir[j] = prnt_dir[j]; 
		j++;
	}

	if (S_ISDIR(st.st_mode))
		node->is_dir = 1;
	else
		node->is_dir = 0;
	node->next = NULL;
	return (node);
}

void	ft_push_back(t_short_format **node, t_short_format *new_node)
{
	t_short_format	*tmp;

	if (!new_node)
		return;

	if (!*node)
	{
		*node = new_node;
		return;
	}

	tmp = *node;
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
