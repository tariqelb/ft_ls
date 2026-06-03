/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_sort_by_time_short_n_elem.c                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tel-bouh <tariqelbouhali039@gmail.com>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/05/28 22:23:25 by tel-bouh          #+#    #+#             */
/*   Updated: 2026/06/03 16:23:54 by tel-bouh         ###   ########.fr       */
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

t_data	*ft_sort_by_time_short_n_elem(t_data *data, int short_len)
{
	t_short_format *cur;
	int swapped;

	if (!data || !data->shrt_format)
	    return (data);

	swapped = 1;
	while (swapped)
	{
		swapped = 0;
		cur = ft_get_start_short(data->shrt_format, short_len);

		while (cur && cur->next)
		{
			if (data->opt.op_r_flag && ft_cmp_time_short(data, cur, cur->next) == 0)
			{
				ft_swap_short_data(cur, cur->next);
				swapped = 1;
				break;
			}
			if (data->opt.op_r_flag == 0 && ft_cmp_time_short(data, cur, cur->next) == 1)
			{
				//printf("reach here [%d] %ld %ld %d\n", ft_cmp_time_short(data, cur, cur->next), cur->raw_time, cur->next->raw_time, k);
				//printf("reach here  {%s} {%s}\n", cur->data, cur->next->data);
				ft_swap_short_data(cur, cur->next);
				swapped = 1;
				break;
			}
			cur = cur->next;
		}
	}
	return (data);
}
