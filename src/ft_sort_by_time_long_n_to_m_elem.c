/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_sort_by_time_long_n_to_m_elem.c                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tel-bouh <tariqelbouhali039@gmail.com>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/05/31 19:08:14 by tel-bouh          #+#    #+#             */
/*   Updated: 2026/06/03 20:51:47 by tel-bouh         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "./ft_ls.h"

t_data	*ft_sort_by_time_long_n_to_m_elem(t_data *data, int long_len, int end)
{
	t_long_format	*cur;
	int		swapped;
	int		i;
	int		cmp;

	if (!data || !data->lng_format)
	    return (data);

	swapped = 1;
	while (swapped)
	{
		swapped = 0;
		cur = ft_get_start_long(data->lng_format, long_len);
		i = long_len;
		while (cur && cur->next && i < long_len + end - 1)
		{
			if (data->opt.op_R_flag)
				cmp = ft_cmp_time_R_flag(data, cur, cur->next);
			else
				cmp = ft_cmp_time(data, cur, cur->next);
			if (data->opt.op_r_flag && cmp == 0)
			{
				ft_swap_long_data(cur, cur->next);
				swapped = 1;
				break;
			}
			if (data->opt.op_r_flag == 0 && cmp == 1)
			{
				ft_swap_long_data(cur, cur->next);
				swapped = 1;
				break;
			}
			cur = cur->next;
			i++;
		}
	}
	return (data);
}

