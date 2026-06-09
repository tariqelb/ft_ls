/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_start_listing.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tel-bouh <tariqelbouhali039@gmail.com>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/05/15 23:30:34 by tel-bouh          #+#    #+#             */
/*   Updated: 2026/06/08 19:19:40 by tel-bouh         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "./ft_ls.h"

t_long_format	*ft_iter_till_new_data_long(t_data *data, int we_reach)
{
	int				i;
	t_long_format	*tmp;

	i = 0;
	tmp = data->lng_format;
	while (i < we_reach && tmp)
	{
		tmp = tmp->next;
		i++;
	}
	return (tmp);
}

t_short_format	*ft_iter_till_new_data_short(t_data *data, int we_reach)
{
	int				i;
	t_short_format	*tmp;

	i = 0;
	tmp = data->shrt_format;
	while (i < we_reach && tmp)
	{
		tmp = tmp->next;
		i++;
	}
	return (tmp);
}

int	ft_start_listing(t_data *data)
{
	ft_list_files(data);
	ft_list_directories(data);
	return (0);
}
