/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_list_files.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tel-bouh <tariqelbouhali039@gmail.com>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/05/16 00:00:14 by tel-bouh          #+#    #+#             */
/*   Updated: 2026/06/11 20:34:31 by tel-bouh         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "./ft_ls.h"

char	ft_check_is_hiden_file(char *path_file)
{
	int	len;

	len = ft_strlen(path_file);
	while (len > 0 && path_file[len - 1] != '/')
	{
		len--;
	}
	if (path_file[len] == '.')
		return (1);
	return (0);
}

int	ft_list_single_file(t_data *data, int f_index)
{
	struct stat	st;

	if (lstat(data->files.file[f_index], &st) == -1)
	{
		perror(data->files.file[f_index]);
		return (1);
	}
	if (data->opt.op_l_flag)
	{
		if (ft_get_long_format(data, f_index, st))
			return (1);
	}
	else
	{
		if (ft_get_short_format(data, f_index, st))
			return (1);
	}
	return (0);
}

int	ft_sort_and_display_file_data(t_data *data)
{
	if (data->opt.op_t_flag)
	{
		if (data->opt.op_l_flag)
			data = ft_sort_by_time_long_n_elem(data, 0, 1);
		else
			data = ft_sort_by_time_short_n_elem(data, 0, 1);
	}
	else
	{
		if (data->opt.op_l_flag)
			data = ft_sort_format_data_from_elem_n_long(data, 0);
		else
			data = ft_sort_format_data_from_elem_n_short(data, 0);
	}
	if (data->opt.op_l_flag)
		ft_display_long_format(data);
	else
		ft_display_short_format_column(data);
	if (data->paths.nbr_of_paths)
		ft_putstr_std("\n", 1);
	return (0);
}

int	ft_list_files(t_data *data)
{
	int	i;

	if (data->files.nbr_of_files == 0)
		return (0);
	i = 0;
	while (i < data->files.nbr_of_files)
	{
		ft_list_single_file(data, i);
		i++;
	}
	ft_sort_and_display_file_data(data);
	return (0);
}
