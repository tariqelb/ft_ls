/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_push_back_long.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tel-bouh <tariqelbouhali039@gmail.com>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/06/08 22:57:13 by tel-bouh          #+#    #+#             */
/*   Updated: 2026/06/09 00:38:05 by tel-bouh         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "./ft_ls.h"

void	ft_long_add_back(t_long_format **node, t_long_format *new_node)
{
	t_long_format	*tmp;

	if (!node || !new_node)
		return ;
	new_node->next = NULL;
	if (*node == NULL)
	{
		*node = new_node;
		return ;
	}
	tmp = *node;
	while (tmp->next)
	{
		tmp = tmp->next;
	}
	tmp->next = new_node;
}

void	ft_long_add_back_at(t_long_format **node,
		t_long_format *new_node, int push_at)
{
	t_long_format	*tmp;
	int				i;

	i = 0;
	if (!node || !new_node)
		return ;
	new_node->next = NULL;
	if (*node == NULL)
	{
		*node = new_node;
		return ;
	}
	tmp = *node;
	while (tmp->next && i < push_at)
	{
		i++;
		tmp = tmp->next;
	}
	new_node->next = tmp->next;
	tmp->next = new_node;
}

int	ft_count_struct_elem_long(t_data *data)
{
	t_long_format	*temp;
	int				len;

	if (!data || !data->lng_format)
		return (0);
	temp = data->lng_format;
	len = 0;
	while (temp)
	{
		temp = temp->next;
		len++;
	}
	return (len);
}
