/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_ls_struct_utils.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tel-bouh <tariqelbouhali039@gmail.com>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/05/16 17:18:11 by tel-bouh          #+#    #+#             */
/*   Updated: 2026/06/05 01:26:25 by tel-bouh         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "./ft_ls.h"

t_short_format	*ft_add_new(char *data, size_t size, struct stat st, char *prnt_dir)
{
	t_short_format	*node;
	size_t		i;
	int		j;

	node = (t_short_format *)malloc(sizeof(t_short_format));
	if (!node)
	{
		ft_putstr_std("ft_ls: error, fail to allocate memory\n" ,2);
		return (NULL);
	}
	node->data = malloc(size + 1);
	if (!node->data)
	{
		free(node);
		return (NULL);
	}
	i = 0;
	while (i < size)
	{
		node->data[i] = data[i];
		i++;
	}
	node->data[i] = 0;
	node->raw_time = st.st_mtime;
	j = 0; 
	while (prnt_dir[j]) 
	{ 
		node->prnt_dir[j] = prnt_dir[j]; 
		j++;
	}
	node->prnt_dir[j] = 0; 
	if (S_ISLNK(st.st_mode))
	{
	    node->is_dir = 0;
	    node->is_exe_or_link = 2;
	}
	else if (S_ISDIR(st.st_mode))
	{
	    node->is_dir = 1;
	    node->is_exe_or_link = 0;
	}
	else
	{
	    node->is_dir = 0;
	    if (st.st_mode & (S_IXUSR | S_IXGRP | S_IXOTH))
		node->is_exe_or_link = 1;
	    else
		node->is_exe_or_link = 0;
	}
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

void	ft_push_back_at(t_short_format **node, t_short_format *new_node, int push_at)
{
	t_short_format	*tmp;
	int		i;

	if (!new_node)
		return;

	if (!*node)
	{
		*node = new_node;
		return;
	}

	i = 0;
	tmp = *node;
	while (tmp->next && i < push_at)
	{
		i++;
		tmp = tmp->next;
	}
	new_node->next = tmp->next;
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
