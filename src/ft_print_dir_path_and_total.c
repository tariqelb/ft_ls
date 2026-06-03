/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_print_dir_path_and_total.c                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tel-bouh <tariqelbouhali039@gmail.com>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/05/24 01:22:33 by tel-bouh          #+#    #+#             */
/*   Updated: 2026/06/03 17:15:07 by tel-bouh         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "./ft_ls.h"

int     ft_print_folder_path(t_data *data, char *path)
{
        if (data->opt.op_R_flag || data->opt.op_a_flag || (data->paths.nbr_of_paths > 1 && data->opt.op_R_flag == 0) || (data->files.nbr_of_files))
        {
		if (data->first_dir)
                	ft_putstr_std("\n", 1);
                ft_putstr_std(path, 1);
		if (data->opt.op_R_flag || data->paths.nbr_of_paths > 1)
			ft_putstr_std(":", 1);
                ft_putstr_std("\n", 1);
		data->first_dir = 1;
        }

        return (0);
}

size_t ft_get_total(t_data *data, char *p_dir_path)
{
	struct stat     st;
	char            *path;
	DIR             *dir;
	struct dirent   *entry;
	size_t          total;

	dir = opendir(p_dir_path);
	if (!dir)
	    return (1);
	total = 0;
	while ((entry = readdir(dir)) != NULL)
	{
	    // skip . and ..
	    //if (ft_strcmp(entry->d_name, ".") == 0 ||
		//ft_strcmp(entry->d_name, "..") == 0)
		//continue;
	    // skip hidden files if no -a
	    if (!data->opt.op_a_flag && entry->d_name[0] == '.')
		continue;
	    path = ft_path_join(p_dir_path, entry->d_name);
	    if (!path)
		return (1);
	    if (lstat(path, &st) == -1)
	    {
		free(path);
		continue;
	    }
	    total += st.st_blocks;
	    free(path);
	}
	closedir(dir);
	if (total)
		total /= 2;
	
	return (total); // depends on system
}

int	ft_display_total(t_data *data, size_t total)
{
	if (data->opt.op_l_flag)
	{
		ft_putstr_std("total ", 1); 
		ft_put_size_t(total, 1); 
		ft_putstr_std("\n", 1); 
	}
}
