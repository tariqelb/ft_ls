/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_list_directories.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tel-bouh <tariqelbouhali039@gmail.com>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/05/17 23:57:34 by tel-bouh          #+#    #+#             */
/*   Updated: 2026/06/07 00:21:56 by tel-bouh         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "./ft_ls.h"

static void	ft_prepare_dirs(t_data *data)
{
	if (data->paths.nbr_of_paths > 1 && data->opt.op_t_flag)
		ft_sort_dirs_paths_by_time(data);
}

static void	ft_set_lengths(t_data *data, int *l, int *s)
{
	if (data->opt.op_l_flag)
		*l = ft_count_struct_elem_long(data);
	else
		*s = ft_count_struct_elem_short(data);
}

static t_data	*ft_sort_after_list(t_data *data, int l, int s)
{
	if (data->opt.op_t_flag)
	{
		if (data->opt.op_l_flag)
			return (ft_sort_by_time_long_n_elem(data, l, 0));
		return (ft_sort_by_time_short_n_elem(data, s, 0));
	}
	if (data->opt.op_l_flag)
		return (ft_sort_format_data_from_elem_n_long(data, l));
	return (ft_sort_format_data_from_elem_n_short(data, s));
}

static void	ft_display_formats(t_data *data, int l, int s)
{
	if (data->opt.op_l_flag)
		ft_display_long_format_n_data(data, l);
	else
		ft_display_short_format_n_data_column(data, s);
}

int	ft_list_directories(t_data *data)
{
	int	i;
	int	short_len;
	int	long_len;
	int	we_reach;

	i = 0;
	short_len = 0;
	long_len = 0;
	we_reach = 0;
	ft_prepare_dirs(data);
	while (i < data->paths.nbr_of_paths)
	{
		ft_set_lengths(data, &long_len, &short_len);
		ft_list_dir(data, i);
		data = ft_sort_after_list(data, long_len, short_len);
		ft_display_formats(data, long_len, short_len);
		data = ft_resort_for_recursion(data, we_reach);
		ft_handle_recursion(data, we_reach);
		we_reach = ft_update_we_reach(data);
		i++;
	}
	return (0);
}
