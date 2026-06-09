/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_display_format_column_two.c                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tel-bouh <tariqelbouhali039@gmail.com>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/06/09 16:17:08 by tel-bouh          #+#    #+#             */
/*   Updated: 2026/06/09 16:31:44 by tel-bouh         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "./ft_ls.h"

int	ft_get_term_width(void)
{
	struct winsize	w;

	if (ioctl(1, TIOCGWINSZ, &w) == -1)
		return (80);
	return (w.ws_col);
}

int	ft_get_max_len(t_short_format *list)
{
	int	max;
	int	len;

	max = 0;
	while (list)
	{
		len = ft_strlen((char *)list->data);
		if (len > max)
			max = len;
		list = list->next;
	}
	return (max);
}

int	ft_list_size(t_short_format *list)
{
	int	count;

	count = 0;
	while (list)
	{
		count++;
		list = list->next;
	}
	return (count);
}

void	ft_display_short_format_column(t_data *data)
{
	ft_display_short_format_n_data_column(data, 0);
}

t_short_format	**ft_build_array(t_short_format *start, int *count)
{
	t_short_format	*tmp;
	t_short_format	**arr;
	int				i;

	tmp = start;
	*count = 0;
	while (tmp && ++(*count))
		tmp = tmp->next;
	if (*count == 0)
		return (NULL);
	arr = malloc(sizeof(t_short_format *) * (*count));
	if (!arr)
		return (NULL);
	tmp = start;
	i = 0;
	while (tmp)
	{
		arr[i++] = tmp;
		tmp = tmp->next;
	}
	return (arr);
}
