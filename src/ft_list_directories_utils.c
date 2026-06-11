/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_list_directories_utils.c                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tel-bouh <tariqelbouhali039@gmail.com>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/06/07 00:15:58 by tel-bouh          #+#    #+#             */
/*   Updated: 2026/06/07 00:16:01 by tel-bouh         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "./ft_ls.h"

t_data	*ft_resort_for_recursion(t_data *data, int we_reach)
{
	if (data->opt.op_l_flag)
		return (ft_sort_format_data_from_elem_n_long(data, we_reach));
	return (ft_sort_format_data_from_elem_n_short(data, we_reach));
}

void	ft_handle_recursion(t_data *data, int we_reach)
{
	if (!data->opt.op_rr_flag)
		return ;
	if (data->opt.op_l_flag)
		ft_iterate_recursion_long_format(data, we_reach);
	else
		ft_iterate_recursion_short_format(data, we_reach);
}

int	ft_update_we_reach(t_data *data)
{
	if (data->opt.op_l_flag)
		return (ft_count_struct_elem_long(data));
	return (ft_count_struct_elem_short(data));
}
