/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_ls_sort_data.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tel-bouh <tariqelbouhali039@gmail.com>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/05/25 01:35:48 by tel-bouh          #+#    #+#             */
/*   Updated: 2026/06/04 00:17:16 by tel-bouh         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "./ft_ls.h"

static void ft_copy_short_content(t_short_format *dst, t_short_format *src)
{
	dst->data = src->data;
	memcpy(dst->prnt_dir, src->prnt_dir, 256);
	dst->is_dir = src->is_dir;
	dst->raw_time = src->raw_time;
	dst->is_exe_or_link = src->is_exe_or_link;
}

static void ft_copy_long_content(t_long_format *dst, t_long_format *src)
{
	memcpy(dst->permission, src->permission, 11);
	dst->links = src->links;
	memcpy(dst->user, src->user, 33);
	memcpy(dst->grop, src->grop, 33);
	dst->size = src->size;
	dst->raw_time = src->raw_time;
	memcpy(dst->time, src->time, 13);
	memcpy(dst->filename, src->filename, 256);
	memcpy(dst->prnt_dir, src->prnt_dir, 256);
	dst->is_dir = src->is_dir;
	dst->is_exe_or_link = src->is_exe_or_link;
	dst->total = src->total;
}

t_long_format *ft_get_start_long(t_long_format *head, int long_len)
{
	int i = 0;

	while (head && i < long_len)
	{
	    head = head->next;
	    i++;
	}
	return (head);
}

t_data *ft_sort_format_data_from_elem_n_long(t_data *data, int long_len)
{
	t_long_format *cur;
	int swapped;

	if (!data || !data->lng_format)
	    return (data);

	swapped = 1;
	while (swapped)
	{
		swapped = 0;

		// 🔥 always restart from offset (not head)
		cur = ft_get_start_long(data->lng_format, long_len);

		while (cur && cur->next)
		{
			if (data->opt.op_r_flag && ft_strcmp(cur->filename, cur->next->filename) < 0)
			{
				ft_swap_long_data(cur, cur->next);
				swapped = 1;
				break; // 🔥 go back to offset start
			}
			else if (data->opt.op_r_flag == 0 && ft_strcmp(cur->filename, cur->next->filename) > 0)
			{
				ft_swap_long_data(cur, cur->next);
				swapped = 1;
				break; // 🔥 go back to offset start
			}
			cur = cur->next;
		}
	}

	return (data);
}

t_short_format *ft_get_start_short(t_short_format *head, int short_len)
{
	int i = 0;

	while (head && i < short_len)
	{
		//printf("head : : : [%s]\n ", head->data);
	    head = head->next;
	    i++;
	}
	return (head);
}

t_data *ft_sort_format_data_from_elem_n_short(t_data *data, int short_len)
{
	t_short_format *cur;
	int swapped;

	if (!data || !data->shrt_format)
	    return (data);


	swapped = 1;
	while (swapped)
	{
		swapped = 0;

		// 🔥 always restart from offset (not head)
		cur = ft_get_start_short(data->shrt_format, short_len);

		while (cur && cur->next)
		{
			if (data->opt.op_r_flag && ft_strcmp(cur->data, cur->next->data) < 0)
			{
				ft_swap_short_data(cur, cur->next);
				swapped = 1;
				break; // 🔥 go back to offset start
			}
			else if (data->opt.op_r_flag == 0 && ft_strcmp(cur->data, cur->next->data) > 0)
			{
				ft_swap_short_data(cur, cur->next);
				swapped = 1;
				break; // 🔥 go back to offset start
			}
			cur = cur->next;
		}
	}

	return (data);
}
