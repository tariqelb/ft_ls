/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_sort_from_n_to_m_elem_short.c                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tel-bouh <tariqelbouhali039@gmail.com>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/06/08 22:30:53 by tel-bouh          #+#    #+#             */
/*   Updated: 2026/08/02 21:43:08 by tariq            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "./ft_ls.h"

static void	ft_copy_short_content(t_short_format *dst, t_short_format *src)
{
	dst->data = src->data;
	ft_memcpy(dst->prnt_dir, src->prnt_dir, 256);
	dst->is_dir = src->is_dir;
	dst->raw_time = src->raw_time;
	dst->tv = src->tv;
	dst->is_exe_or_link = src->is_exe_or_link;
}

void	ft_swap_short_data(t_short_format *a, t_short_format *b)
{
	t_short_format	tmp;
	t_short_format	*next_a;
	t_short_format	*next_b;

	next_a = a->next;
	next_b = b->next;
	ft_copy_short_content(&tmp, a);
	ft_copy_short_content(a, b);
	ft_copy_short_content(b, &tmp);
	a->next = next_a;
	b->next = next_b;
}

static int	ft_compare_and_swap(t_data *data, t_short_format *cur, int *swapped)
{
	if (data->opt.op_r_flag
		&& ft_strcmp(cur->data, cur->next->data) < 0)
	{
		ft_swap_short_data(cur, cur->next);
		*swapped = 1;
		return (1);
	}
	else if (data->opt.op_r_flag == 0
		&& ft_strcmp(cur->data, cur->next->data) > 0)
	{
		ft_swap_short_data(cur, cur->next);
		*swapped = 1;
		return (1);
	}
	return (0);
}

t_data	*ft_sort_format_data_from_elem_n_to_m_short(t_data *data,
		int short_len, int end)
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
			if (ft_compare_and_swap(data, cur, &swapped))
				break ;
			cur = cur->next;
			i++;
		}
	}
	return (data);
}
