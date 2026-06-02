/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_sort_by_time_long_n_elem.c                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tel-bouh <tariqelbouhali039@gmail.com>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/05/28 22:19:43 by tel-bouh          #+#    #+#             */
/*   Updated: 2026/06/02 17:45:13 by tel-bouh         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "./ft_ls.h"

int	ft_cmp_time(t_data *data, t_long_format *a, t_long_format *b)
{
	int	ascii;

	if (a->raw_time < b->raw_time)
	    return (1);   // b is newer → swap
	if (a->raw_time > b->raw_time)
	    return (0);
	ascii = ft_strcmp(a->filename, b->filename);
	//printf("cmp; [%s] [%s]  %ld %ld %d ascii %d\n", a->filename, b->filename,  a->raw_time, b->raw_time, ft_strcmp(a->filename, b->filename), ascii);
	if (data->opt.op_r_flag == 0 && ascii > 0)
		return (1);
	else if (data->opt.op_r_flag == 0 && ascii < 0)
		return (0);
	else if (data->opt.op_r_flag == 1 && ascii > 0)
		return (0);
	else if (data->opt.op_r_flag == 1 && ascii < 0)
		return (1);
	else
		return (-1);
}

t_data	*ft_sort_by_time_long_n_elem(t_data *data, int long_len)
{
	t_long_format *cur;
	int swapped;

	if (!data || !data->lng_format)
	    return (data);

	swapped = 1;
	while (swapped)
	{
		swapped = 0;
		cur = ft_get_start_long(data->lng_format, long_len);

		while (cur && cur->next)
		{
			if (data->opt.op_r_flag && ft_cmp_time(data, cur, cur->next) == 0)
			{
				ft_swap_long_data(cur, cur->next);
				swapped = 1;
				break;
			}
			if (data->opt.op_r_flag == 0 && ft_cmp_time(data, cur, cur->next) == 1)
			{
				ft_swap_long_data(cur, cur->next);
				swapped = 1;
				break;
			}
			cur = cur->next;
		}
	}
	return (data);
}
