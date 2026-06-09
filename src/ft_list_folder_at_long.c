/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_list_folder_at_long.c                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tel-bouh <tariqelbouhali039@gmail.com>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/06/07 18:55:04 by tel-bouh          #+#    #+#             */
/*   Updated: 2026/06/09 14:59:25 by tel-bouh         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "./ft_ls.h"

static int	ft_init_fol_at(t_fol_at *f, char *filename, char *prnt_dir)
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

static int	ft_loop_long_at(t_data *data, t_fol_at *f)
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
		f->nbr_of_elem += ft_get_long_format_folder_at(data, f);
		free(f->path);
	}
	return (0);
}

int	ft_list_folder_long_format_at(t_data *data,
		char *filename, char *prnt_dir, int i)
{
	t_fol_at	f;

	if (ft_init_fol_at(&f, filename, prnt_dir))
		return (1);
	ft_print_folder_path(data, f.p_dir_path);
	if (data->opt.op_l_flag)
		f.total = ft_get_total(data, f.p_dir_path);
	data->i = i;
	if (ft_loop_long_at(data, &f))
		return (1);
	closedir(f.dir);
	free(f.p_dir_path);
	ft_display_total(data, f.total);
	return (f.nbr_of_elem);
}
