/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_ls_sort_format.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tel-bouh <tariqelbouhali039@gmail.com>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/05/20 22:00:01 by tel-bouh          #+#    #+#             */
/*   Updated: 2026/05/21 03:16:12 by tel-bouh         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "./ft_ls.h"

t_data *ft_sort_long_format(t_data *data, int long_len)
{
	int				i;
	t_long_format	*start;
	t_long_format	*head;
	t_long_format	*cur;
	t_long_format	*tmp;

	if (!data || !data->lng_format)
		return (data);

	head = data->lng_format;
	start = data->lng_format;

	i = 0;
	while (start && i < long_len)
	{
		start = start->next;
		i++;
	}

	if (!start)
		return (data);

	cur = start;

	while (cur && cur->next)
	{
		if (i == 0)
			head = cur;
		if (ft_strcmp(cur->filename, cur->next->filename) > 0)
		{
			tmp = cur->next;

			// swap adjacent nodes safely
			cur->next = tmp->next;
			tmp->next = cur;

			// IMPORTANT: if start moved, update start
			if (cur == start)
				start = tmp;

			// restart from beginning of sublist
			cur = start;
		}
		else
		{
			cur = cur->next;
		}
	}
	//*(data->lng_format) = head;

	return (data);
}


t_data	*ft_sort_short_format(t_data *data, int short_len)
{
	int				i;
	t_short_format	*start;
	t_short_format	*head;
	t_short_format	*cur;
	t_short_format	*tmp;
	

	if (!data || !data->lng_format)
		return (data);
	head = data->shrt_format;
	start = data->shrt_format;

	i = 0;
	while (start && i < short_len)
	{
		start = start->next;
		i++;
	}

	if (!start)
		return (data);

	cur = start;

	while (cur && cur->next)
	{
		if (ft_strcmp(cur->data, cur->next->data) > 0)
		{
			tmp = cur->next;

			// swap adjacent nodes safely
			cur->next = tmp->next;
			tmp->next = cur;

			// IMPORTANT: if start moved, update start
			if (cur == start)
				start = tmp;

			// restart from beginning of sublist
			cur = start;
		}
		else
		{
			cur = cur->next;
		}
	}
	data->shrt_format = head;

	return (data);
}
