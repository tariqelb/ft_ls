/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_sort_by_time_short_n_to_m_elem.c                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tel-bouh <tariqelbouhali039@gmail.com>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/05/31 19:14:58 by tel-bouh          #+#    #+#             */
/*   Updated: 2026/05/31 19:52:49 by tel-bouh         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "./ft_ls.h"

t_data	*ft_sort_by_time_short_n_to_m_elem(t_data *data, int short_len, int end)
{
	t_short_format	*cur;
	int		swapped;
	int		i;

	if (!data || !data->shrt_format)
	    return (data);
	swapped = 1;
	while (swapped)
	{
		swapped = 0;
		cur = ft_get_start_short(data->shrt_format, short_len);
		i = short_len;
		while (cur && cur->next && i < short_len + end - 1)
		{
			if (data->opt.op_r_flag && ft_cmp_time_short(cur, cur->next) == 0)
			{
				ft_swap_short_data(cur, cur->next);
				swapped = 1;
				break;
			}
			if (data->opt.op_r_flag == 0 && ft_cmp_time_short(cur, cur->next) == 1)
			{
				//printf("-------------reach here [%d] %ld %ld k %d\n", ft_cmp_time_short(cur, cur->next), cur->raw_time, cur->next->raw_time, k);
				ft_swap_short_data(cur, cur->next);
				swapped = 1;
				break;
			}
			cur = cur->next;
			i++;
		}
	}
	return (data);
}
