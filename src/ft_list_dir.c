/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_list_dir.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tel-bouh <tariqelbouhali039@gmail.com>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/06/06 23:39:33 by tel-bouh          #+#    #+#             */
/*   Updated: 2026/06/09 22:10:58 by tel-bouh         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "./ft_ls.h"

int	ft_loop_over_dirs(t_data *data, t_dir *dir, int d_index)
{
	dir->path = ft_path_join(data->paths.path[d_index],
			dir->entry->d_name);
	if (!dir->path)
		return (1);
	if (lstat(dir->path, &dir->st) == -1)
	{
		free(dir->path);
		return (0);
	}
	if (data->opt.op_l_flag)
		ft_get_long_format_dir(data, dir->entry->d_name,
			d_index, dir->st);
	else
		ft_get_short_format_dir(data, dir->entry->d_name,
			d_index, dir->st);
	free(dir->path);
	return (0);
}

int	ft_list_dir(t_data *data, int d_index)
{
	t_dir	dir;

	dir.total = 0;
	dir.dir = opendir(data->paths.path[d_index]);
	if (!dir.dir)
		return (1);
	if (data->paths.nbr_of_paths > 1
		|| data->opt.op_rr_flag
		|| data->files.nbr_of_files)
		ft_print_folder_path(data, data->paths.path[d_index]);
	if (data->opt.op_l_flag)
		dir.total = ft_get_total(data, data->paths.path[d_index]);
	dir.entry = readdir(dir.dir);
	while (dir.entry != NULL)
	{
		if (ft_loop_over_dirs(data, &dir, d_index))
			return (closedir(dir.dir), 1);
		dir.entry = readdir(dir.dir);
	}
	closedir(dir.dir);
	ft_display_total(data, dir.total);
	return (0);
}
