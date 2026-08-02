/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_sort_from_n_to_m_elem_long.c                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tel-bouh <tariqelbouhali039@gmail.com>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/05/30 22:58:03 by tel-bouh          #+#    #+#             */
/*   Updated: 2026/08/02 21:42:18 by tariq            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "./ft_ls.h"

static void	ft_copy_long_content(t_long_format *dst, t_long_format *src)
{
	ft_memcpy(dst->permission, src->permission, 11);
	dst->links = src->links;
	ft_memcpy(dst->user, src->user, 33);
	ft_memcpy(dst->grop, src->grop, 33);
	dst->size = src->size;
	dst->raw_time = src->raw_time;
	dst->tv = src->tv;
	ft_memcpy(dst->time, src->time, 13);
	ft_memcpy(dst->filename, src->filename, 256);
	ft_memcpy(dst->link_file, src->link_file, 256);
	ft_memcpy(dst->prnt_dir, src->prnt_dir, 256);
	dst->is_dir = src->is_dir;
	dst->total = src->total;
	dst->is_exe_or_link = src->is_exe_or_link;
}

void	ft_swap_long_data(t_long_format *a, t_long_format *b)
{
	t_long_format	tmp;
	t_long_format	*next_a;
	t_long_format	*next_b;

	next_a = a->next;
	next_b = b->next;
	ft_copy_long_content(&tmp, a);
	ft_copy_long_content(a, b);
	ft_copy_long_content(b, &tmp);
	a->next = next_a;
	b->next = next_b;
}

static int	ft_compare_and_swap(t_data *data, t_long_format *cur, int *swapped)
{
	if (data->opt.op_r_flag
		&& ft_strcmp(cur->filename, cur->next->filename) < 0)
	{
		ft_swap_long_data(cur, cur->next);
		*swapped = 1;
		return (1);
	}
	else if (data->opt.op_r_flag == 0
		&& ft_strcmp(cur->filename, cur->next->filename) > 0)
	{
		ft_swap_long_data(cur, cur->next);
		*swapped = 1;
		return (1);
	}
	return (0);
}

t_data	*ft_sort_format_data_from_elem_n_to_m_long(t_data *data,
		int long_len, int end)
{
	t_long_format	*cur;
	int				swapped;
	int				i;

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
			if (ft_compare_and_swap(data, cur, &swapped))
				break ;
			cur = cur->next;
			i++;
		}
	}
	return (data);
}
