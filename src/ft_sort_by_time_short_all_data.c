/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_sort_by_time_short_all_data.c                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tel-bouh <tariqelbouhali039@gmail.com>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/05/29 00:54:32 by tel-bouh          #+#    #+#             */
/*   Updated: 2026/06/08 21:57:47 by tel-bouh         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "./ft_ls.h"

static void	ft_swap_nodes_short(t_data *data,
			t_short_format **prev, t_short_format **cur)
{
	t_short_format	*tmp;

	tmp = (*cur)->next;
	(*cur)->next = tmp->next;
	tmp->next = *cur;
	if (*prev == NULL)
		data->shrt_format = tmp;
	else
		(*prev)->next = tmp;
	*cur = data->shrt_format;
	*prev = NULL;
}

static int	ft_should_swap_short(t_data *data,
			t_short_format *cur)
{
	if (data->opt.op_r_flag)
		return (!ft_cmp_time_short(data, cur, cur->next));
	return (ft_cmp_time_short(data, cur, cur->next));
}

t_data	*ft_sort_by_time_short_all_data(t_data *data)
{
	t_short_format	*prev;
	t_short_format	*cur;

	if (!data || !data->shrt_format)
		return (data);
	prev = NULL;
	cur = data->shrt_format;
	while (cur && cur->next)
	{
		if (ft_should_swap_short(data, cur))
		{
			ft_swap_nodes_short(data, &prev, &cur);
			continue ;
		}
		prev = cur;
		cur = cur->next;
	}
	return (data);
}
