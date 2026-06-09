/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_sort_by_time_long_all_data.c                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tel-bouh <tariqelbouhali039@gmail.com>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/06/08 19:47:52 by tel-bouh          #+#    #+#             */
/*   Updated: 2026/06/08 21:54:06 by tel-bouh         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "./ft_ls.h"

static void	ft_swap_nodes_long(t_data *data,
			t_long_format **prev, t_long_format **cur)
{
	t_long_format	*tmp;

	tmp = (*cur)->next;
	(*cur)->next = tmp->next;
	tmp->next = *cur;
	if (*prev == NULL)
		data->lng_format = tmp;
	else
		(*prev)->next = tmp;
	*cur = data->lng_format;
	*prev = NULL;
}

static int	ft_should_swap_long(t_data *data,
			t_long_format *cur)
{
	if (data->opt.op_r_flag)
		return (!ft_cmp_time(data, cur, cur->next));
	return (ft_cmp_time(data, cur, cur->next));
}

t_data	*ft_sort_by_time_long_all_data(t_data *data)
{
	t_long_format	*prev;
	t_long_format	*cur;

	if (!data || !data->lng_format)
		return (data);
	prev = NULL;
	cur = data->lng_format;
	while (cur && cur->next)
	{
		if (ft_should_swap_long(data, cur))
		{
			ft_swap_nodes_long(data, &prev, &cur);
			continue ;
		}
		prev = cur;
		cur = cur->next;
	}
	return (data);
}
