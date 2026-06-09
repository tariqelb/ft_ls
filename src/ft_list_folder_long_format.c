/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_list_folder_long_format.c                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tel-bouh <tariqelbouhali039@gmail.com>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/06/07 19:22:30 by tel-bouh          #+#    #+#             */
/*   Updated: 2026/06/07 19:43:46 by tel-bouh         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "./ft_ls.h"

static int	ft_init_fol(t_fol_at *f, char *filename, char *prnt_dir)
{
	f->p_dir_path = ft_join_parrent_dir(filename, prnt_dir);
	if (!f->p_dir_path)
		return (1);
	f->dir = opendir(f->p_dir_path);
	if (!f->dir)
	{
		free(f->p_dir_path);
		return (1);
	}
	f->nbr_of_elem = 0;
	f->total = 0;
	return (0);
}

static int	ft_loop_long(t_data *data, t_fol_at *f)
{
	while (1)
	{
		f->entry = readdir(f->dir);
		if (!f->entry)
			break ;
		f->path = ft_path_join(f->p_dir_path, f->entry->d_name);
		if (!f->path)
			return (1);
		if (lstat(f->path, &f->st) == -1)
		{
			free(f->path);
			continue ;
		}
		f->nbr_of_elem += ft_get_long_format_folder(data, f);
		free(f->path);
	}
	return (0);
}

static t_data	*ft_sort_long_after(t_data *data, size_t long_len)
{
	if (data->opt.op_t_flag)
		return (ft_sort_by_time_long_n_elem(data, long_len, 0));
	return (ft_sort_format_data_from_elem_n_long(data, long_len));
}

int	ft_list_folder_long_format(t_data *data,
	char *filename, char *prnt_dir)
{
	t_fol_at	f;
	size_t		long_len;

	if (ft_init_fol(&f, filename, prnt_dir))
		return (1);
	long_len = ft_count_struct_elem_long(data);
	ft_print_folder_path(data, f.p_dir_path);
	if (data->opt.op_l_flag)
		f.total = ft_get_total(data, f.p_dir_path);
	if (ft_loop_long(data, &f))
		return (1);
	closedir(f.dir);
	ft_display_total(data, f.total);
	free(f.p_dir_path);
	data = ft_sort_long_after(data, long_len);
	return (f.nbr_of_elem);
}
