/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_sort_format_data_from_n_elem_long.c             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tel-bouh <tariqelbouhali039@gmail.com>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/06/07 22:30:29 by tel-bouh          #+#    #+#             */
/*   Updated: 2026/06/07 22:53:29 by tel-bouh         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "./ft_ls.h"

t_long_format	*ft_get_start_long(t_long_format *head, int long_len)
{
	int	i;

	i = 0;
	while (head && i < long_len)
	{
		head = head->next;
		i++;
	}
	return (head);
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

t_data	*ft_sort_format_data_from_elem_n_long(t_data *data, int long_len)
{
	t_long_format	*cur;
	int				swapped;

	if (!data || !data->lng_format)
		return (data);
	swapped = 1;
	while (swapped)
	{
		swapped = 0;
		cur = ft_get_start_long(data->lng_format, long_len);
		while (cur && cur->next)
		{
			if (ft_compare_and_swap(data, cur, &swapped))
				break ;
			cur = cur->next;
		}
	}
	return (data);
}
