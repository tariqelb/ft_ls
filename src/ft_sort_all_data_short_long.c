/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_sort_all_data_short_long.c                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tel-bouh <tariqelbouhali039@gmail.com>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/05/20 22:00:01 by tel-bouh          #+#    #+#             */
/*   Updated: 2026/06/08 19:19:26 by tel-bouh         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "./ft_ls.h"

static void	ft_swap_data_long(t_data *data, t_long_format *cur,
			t_long_format *prev)
{
	t_long_format	*tmp;

	tmp = cur->next;
	cur->next = tmp->next;
	tmp->next = cur;
	if (prev == NULL)
		data->lng_format = tmp;
	else
		prev->next = tmp;
	cur = data->lng_format;
	prev = NULL;
}

t_data	*ft_sort_long_format_all_data(t_data *data)
{
	t_long_format	*prev;
	t_long_format	*cur;

	if (!data || !data->lng_format)
		return (data);
	prev = NULL;
	cur = data->lng_format;
	while (cur && cur->next)
	{
		if (ft_strcmp(cur->filename, cur->next->filename) > 0)
		{
			ft_swap_data_long(data, cur, prev);
			continue ;
		}
		else
		{
			prev = cur;
			cur = cur->next;
		}
	}
	return (data);
}

static void	ft_swap_data_short(t_data *data, t_short_format *cur,
		t_short_format *prev)
{
	t_short_format	*tmp;

	tmp = cur->next;
	cur->next = tmp->next;
	tmp->next = cur;
	if (prev == NULL)
		data->shrt_format = tmp;
	else
		prev->next = tmp;
	cur = data->shrt_format;
	prev = NULL;
}

t_data	*ft_sort_short_format_all_data(t_data *data)
{
	t_short_format	*prev;
	t_short_format	*cur;

	if (!data || !data->shrt_format)
		return (data);
	prev = NULL;
	cur = data->shrt_format;
	while (cur && cur->next)
	{
		if (ft_strcmp(cur->data, cur->next->data) > 0)
		{
			ft_swap_data_short(data, cur, prev);
			continue ;
		}
		else
		{
			prev = cur;
			cur = cur->next;
		}
	}
	return (data);
}
