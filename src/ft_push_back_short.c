/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_push_back_short.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tel-bouh <tariqelbouhali039@gmail.com>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/06/08 22:47:27 by tel-bouh          #+#    #+#             */
/*   Updated: 2026/06/09 00:41:06 by tel-bouh         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "./ft_ls.h"

void	ft_push_back(t_short_format **node, t_short_format *new_node)
{
	t_short_format	*tmp;

	if (!new_node)
		return ;
	if (!*node)
	{
		*node = new_node;
		return ;
	}
	tmp = *node;
	while (tmp->next)
		tmp = tmp->next;
	tmp->next = new_node;
}

void	ft_push_back_at(t_short_format **node,
		t_short_format *new_node, int push_at)
{
	t_short_format	*tmp;
	int				i;

	if (!new_node)
		return ;
	if (!*node)
	{
		*node = new_node;
		return ;
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

int	ft_count_struct_elem_short(t_data *data)
{
	int				len;
	t_short_format	*temp;

	if (!data || !data->shrt_format)
		return (0);
	temp = data->shrt_format;
	len = 0;
	while (temp)
	{
		temp = temp->next;
		len++;
	}
	return (len);
}
