/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_print_dir_path_and_total.c                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tel-bouh <tariqelbouhali039@gmail.com>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/05/24 01:22:33 by tel-bouh          #+#    #+#             */
/*   Updated: 2026/05/26 02:08:11 by tel-bouh         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "./ft_ls.h"

int     ft_print_folder_path(t_data *data, char *path)
{
        if (data->opt.op_R_flag || data->opt.op_a_flag || data->paths.nbr_of_paths > 1)
        {
                ft_putstr_std(path, 1);
		if (data->opt.op_R_flag == 0 || data->opt.op_a_flag  == 0)
			ft_putstr_std(":", 1);
                ft_putstr_std("\n", 1);
        }
        return (0);
}

size_t	 ft_get_total(t_data *data, char *p_dir_path)
{
	struct stat     st;
	char		*path;
	DIR		*dir;
	struct dirent   *entry;
	size_t		total;

	dir = opendir(p_dir_path);
	if (!dir)       
	{
		free(p_dir_path);
		return (1);
	}
	total = 0;
	while ((entry = readdir(dir)) != NULL)
	{  
		path = ft_path_join(p_dir_path, entry->d_name);
		//printf("lstat path check : {%s} {%s} {%s}\n", p_dir_path, entry->d_name, path );
		if (ft_strcmp(entry->d_name, "..") == 0 || ft_strcmp(entry->d_name, ".") == 0)
			continue;
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
	return (total);
}

int	ft_display_total(size_t total)
{
	ft_putstr_std("total ", 1); 
	ft_put_size_t(total, 1); 
	ft_putstr_std("\n", 1); 
}
