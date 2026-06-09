/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_sort_by_time_short_n_elem.c                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tel-bouh <tariqelbouhali039@gmail.com>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/05/28 22:23:25 by tel-bouh          #+#    #+#             */
/*   Updated: 2026/06/08 22:07:25 by tel-bouh         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "./ft_ls.h"

int	ft_cmp_time_short(t_data *data, t_short_format *a, t_short_format *b)
{
	int	ascii;

	if (a->raw_time < b->raw_time)
		return (1);
	if (a->raw_time > b->raw_time)
		return (0);
	ascii = ft_strcmp(a->data, b->data);
	if (data->opt.op_r_flag == 0 && ascii < 0)
		return (1);
	else if (data->opt.op_r_flag == 0 && ascii > 0)
		return (0);
	if (data->opt.op_r_flag == 1 && ascii > 0)
		return (0);
	else if (data->opt.op_r_flag == 1 && ascii < 0)
		return (1);
	else
		return (-1);
}

int	ft_cmp_time_short_upper_r_flag(t_data *data,
		t_short_format *a, t_short_format *b)
{
	int	ascii;

	if (a->raw_time < b->raw_time)
		return (1);
	if (a->raw_time > b->raw_time)
		return (0);
	ascii = ft_strcmp(a->data, b->data);
	if (data->opt.op_r_flag == 0 && ascii < 0)
		return (0);
	else if (data->opt.op_r_flag == 0 && ascii > 0)
		return (1);
	if (data->opt.op_r_flag == 1 && ascii > 0)
		return (1);
	else if (data->opt.op_r_flag == 1 && ascii < 0)
		return (0);
	else
		return (-1);
}

static int	ft_compare_swap_data(t_data *data,
			t_short_format *cur, int file, int *swapped)
{
	int	cmp;

	if (file)
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

t_data	*ft_sort_by_time_short_n_elem(t_data *data, int short_len, int file)
{
	t_short_format	*cur;
	int				swapped;

	if (!data || !data->shrt_format)
		return (data);
	swapped = 1;
	while (swapped)
	{
		swapped = 0;
		cur = ft_get_start_short(data->shrt_format, short_len);
		while (cur && cur->next)
		{
			if (ft_compare_swap_data(data, cur, file, &swapped))
				break ;
			cur = cur->next;
		}
	}
	return (data);
}
