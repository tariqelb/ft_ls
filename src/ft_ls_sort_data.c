/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_ls_sort_data.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tel-bouh <tariqelbouhali039@gmail.com>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/05/25 01:35:48 by tel-bouh          #+#    #+#             */
/*   Updated: 2026/05/25 02:20:48 by tel-bouh         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "./ft_ls.h"

static void ft_copy_short_content(t_short_format *dst, t_short_format *src)
{
    dst->data = src->data;
    memcpy(dst->prnt_dir, src->prnt_dir, 256);
    dst->is_dir = src->is_dir;
}

static void ft_copy_long_content(t_long_format *dst, t_long_format *src)
{
    memcpy(dst->permission, src->permission, 11);
    dst->links = src->links;
    memcpy(dst->user, src->user, 33);
    memcpy(dst->grop, src->grop, 33);
    dst->size = src->size;
    memcpy(dst->time, src->time, 13);
    memcpy(dst->filename, src->filename, 256);
    memcpy(dst->prnt_dir, src->prnt_dir, 256);
    dst->is_dir = src->is_dir;
    dst->total = src->total;
}

void    ft_swap_short_data(t_short_format *a, t_short_format *b)
{
    t_short_format tmp;
    t_short_format *next_a;
    t_short_format *next_b;

    next_a = a->next;
    next_b = b->next;

    ft_copy_short_content(&tmp, a);
    ft_copy_short_content(a, b);
    ft_copy_short_content(b, &tmp);

    a->next = next_a;
    b->next = next_b;
}

void    ft_swap_long_data(t_long_format *a, t_long_format *b)
{
    t_long_format tmp;
    t_long_format *next_a;
    t_long_format *next_b;

    next_a = a->next;
    next_b = b->next;

    ft_copy_long_content(&tmp, a);
    ft_copy_long_content(a, b);
    ft_copy_long_content(b, &tmp);

    a->next = next_a;
    b->next = next_b;
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
			if (ft_strcmp(cur->filename, cur->next->filename) > 0)
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
			if (ft_strcmp(cur->data, cur->next->data) > 0)
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
