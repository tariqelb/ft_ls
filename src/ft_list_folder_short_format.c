/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_list_folder_short_format.c                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tel-bouh <tariqelbouhali039@gmail.com>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/06/07 19:20:14 by tel-bouh          #+#    #+#             */
/*   Updated: 2026/06/07 19:46:19 by tel-bouh         ###   ########.fr       */
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

static int	ft_loop_short(t_data *data, t_fol_at *f)
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
		f->nbr_of_elem += ft_get_short_format_folder(data, f);
		free(f->path);
	}
	return (0);
}

static t_data	*ft_sort_short_after(t_data *data, size_t short_len)
{
	if (data->opt.op_t_flag)
		return (ft_sort_by_time_short_n_elem(data, short_len, 0));
	return (ft_sort_format_data_from_elem_n_short(data, short_len));
}

int	ft_list_folder_short_format(t_data *data,
	char *filename, char *prnt_dir)
{
	t_fol_at	f;
	size_t		short_len;

	if (ft_init_fol(&f, filename, prnt_dir))
		return (1);
	short_len = ft_count_struct_elem_short(data);
	ft_print_folder_path(data, f.p_dir_path);
	if (ft_loop_short(data, &f))
		return (1);
	closedir(f.dir);
	free(f.p_dir_path);
	data = ft_sort_short_after(data, short_len);
	return (f.nbr_of_elem);
}
