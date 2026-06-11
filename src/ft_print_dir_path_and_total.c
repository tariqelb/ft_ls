/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_print_dir_path_and_total.c                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tel-bouh <tariqelbouhali039@gmail.com>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/05/24 01:22:33 by tel-bouh          #+#    #+#             */
/*   Updated: 2026/06/09 01:46:14 by tel-bouh         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "./ft_ls.h"

int	ft_print_folder_path(t_data *data, char *path)
{
	if (data->opt.op_rr_flag || data->opt.op_a_flag
		|| (data->paths.nbr_of_paths > 1 && data->opt.op_rr_flag == 0)
		|| (data->files.nbr_of_files))
	{
		if (data->first_dir)
			ft_putstr_std("\n", 1);
		ft_putstr_std(path, 1);
		if (data->opt.op_rr_flag || data->paths.nbr_of_paths > 1)
			ft_putstr_std(":", 1);
		ft_putstr_std("\n", 1);
		data->first_dir = 1;
	}
	return (0);
}

static int	ft_get_total_util(t_data *data, char *p_dir_path,
			struct dirent *entry, size_t *total)
{
	struct stat	st;
	char		*path;

	if (!data->opt.op_a_flag && entry->d_name[0] == '.')
		return (0);
	path = ft_path_join(p_dir_path, entry->d_name);
	if (!path)
		return (1);
	if (lstat(path, &st) == -1)
	{
		free(path);
		return (0);
	}
	*total += st.st_blocks;
	free(path);
	return (0);
}

size_t	ft_get_total(t_data *data, char *p_dir_path)
{
	struct dirent	*entry;
	size_t			total;
	DIR				*dir;

	dir = opendir(p_dir_path);
	if (!dir)
		return (1);
	total = 0;
	entry = readdir(dir);
	while (entry != NULL)
	{
		if (ft_get_total_util(data, p_dir_path, entry, &total))
			return (1);
		entry = readdir(dir);
	}
	closedir(dir);
	if (total)
		total /= 2;
	return (total);
}

int	ft_display_total(t_data *data, size_t total)
{
	if (data->opt.op_l_flag)
	{
		ft_putstr_std("total ", 1);
		ft_put_size_t(total, 1);
		ft_putstr_std("\n", 1);
	}
	return (0);
}
