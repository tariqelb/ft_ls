/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_iterate_recursion_long_format.c                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tel-bouh <tariqelbouhali039@gmail.com>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/06/08 01:38:53 by tel-bouh          #+#    #+#             */
/*   Updated: 2026/06/11 21:20:06 by tel-bouh         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "./ft_ls.h"

static int	ft_process_dir_long(t_data *data, t_long_format *temp, int i)
{
	int	nbr_of_elem;

	nbr_of_elem = 0;
	if (temp->is_dir == 1
		&& ft_strcmp(temp->filename, ".") != 0
		&& ft_strcmp(temp->filename, "..") != 0)
	{
		nbr_of_elem = ft_list_folder_long_format_at(
				data, temp->filename, temp->prnt_dir, i);
		if (data->opt.op_t_flag)
			data = ft_sort_by_time_long_n_to_m_elem(data, i + 1, nbr_of_elem);
		else
			data = ft_sort_format_data_from_elem_n_to_m_long(
					data, i + 1, nbr_of_elem);
		ft_display_long_format_n_to_m_data(data, i + 1, nbr_of_elem);
	}
	return (nbr_of_elem);
}

int	ft_iterate_recursion_long_format(t_data *data, int we_reach)
{
	int				i;
	int				len;
	t_long_format	*temp;

	temp = ft_iter_till_new_data_long(data, we_reach);
	len = ft_count_struct_elem_long(data);
	i = we_reach;
	while (i < len)
	{
		ft_process_dir_long(data, temp, i);
		temp = temp->next;
		len = ft_count_struct_elem_long(data);
		i++;
	}
	return (0);
}
