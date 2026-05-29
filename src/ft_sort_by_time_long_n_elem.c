/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_sort_by_time_long_n_elem.c                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tel-bouh <tariqelbouhali039@gmail.com>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/05/28 22:19:43 by tel-bouh          #+#    #+#             */
/*   Updated: 2026/05/29 01:46:33 by tel-bouh         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "./ft_ls.h"

int	ft_cmp_time(t_long_format *a, t_long_format *b)
{
	if (a->raw_time < b->raw_time)
	    return (1);   // b is newer → swap
	if (a->raw_time > b->raw_time)
	    return (0);
	return (ft_strcmp(a->filename, b->filename)); // tie breaker
}

t_data	*ft_sort_by_time_long_n_elem(t_data *data, int long_len)
{
	t_long_format *cur;
	int swapped;

	if (!data || !data->lng_format)
	    return (data);

	swapped = 1;
	while (swapped)
	{
		swapped = 0;
		cur = ft_get_start_long(data->lng_format, long_len);

		while (cur && cur->next)
		{
			if (data->opt.op_r_flag && !ft_cmp_time(cur, cur->next))
			{
				ft_swap_long_data(cur, cur->next);
				swapped = 1;
				break;
			}
			if (data->opt.op_r_flag == 0 && ft_cmp_time(cur, cur->next))
			{
				ft_swap_long_data(cur, cur->next);
				swapped = 1;
				break;
			}
			cur = cur->next;
		}
	}
	return (data);
}
