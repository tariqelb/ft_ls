/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_sort_by_time_short_n_to_m_elem.c                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tel-bouh <tariqelbouhali039@gmail.com>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/05/31 19:14:58 by tel-bouh          #+#    #+#             */
/*   Updated: 2026/06/08 22:11:44 by tel-bouh         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "./ft_ls.h"

static int	ft_compare_swap_data(t_data *data,
			t_short_format *cur, int *swapped)
{
	int	cmp;

	if (data->opt.op_R_flag)
		cmp = ft_cmp_time_short_upper_r_flag(data, cur, cur->next);
	else
		cmp = ft_cmp_time_short(data, cur, cur->next);
	if (data->opt.op_r_flag && cmp == 0)
	{
		ft_swap_short_data(cur, cur->next);
		*swapped = 1;
		return (1);
	}
	if (data->opt.op_r_flag == 0 && cmp == 1)
	{
		ft_swap_short_data(cur, cur->next);
		*swapped = 1;
		return (1);
	}
	return (0);
}

t_data	*ft_sort_by_time_short_n_to_m_elem(t_data *data, int short_len, int end)
{
	t_short_format	*cur;
	int				swapped;
	int				i;

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
			if (ft_compare_swap_data(data, cur, &swapped))
				break ;
			cur = cur->next;
			i++;
		}
	}
	return (data);
}
