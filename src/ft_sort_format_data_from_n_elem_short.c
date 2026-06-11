/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_sort_format_data_from_n_elem_short.c            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tel-bouh <tariqelbouhali039@gmail.com>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/06/07 22:38:19 by tel-bouh          #+#    #+#             */
/*   Updated: 2026/06/11 00:58:25 by tel-bouh         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "./ft_ls.h"

t_short_format	*ft_get_start_short(t_short_format *head, int short_len)
{
	int	i;

	i = 0;
	while (head && i < short_len)
	{
		head = head->next;
		i++;
	}
	return (head);
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

t_data	*ft_sort_format_data_from_elem_n_short(t_data *data, int short_len)
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
			if (ft_compare_and_swap(data, cur, &swapped))
				break ;
			cur = cur->next;
		}
	}
	return (data);
}
