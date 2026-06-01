/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_sort_dirs_paths_by_time.c                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tel-bouh <tariqelbouhali039@gmail.com>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/05/31 20:37:45 by tel-bouh          #+#    #+#             */
/*   Updated: 2026/05/31 21:11:45 by tel-bouh         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "./ft_ls.h"


int ft_get_path_time(t_data *data, int i)
{
    struct stat st;

    if (lstat(data->paths.path[i], &st) == -1)
        return (1);

    data->paths.raw_time[i] = st.st_mtime;
    return (0);
}

void	ft_swap_dir_path(t_data *data, int i, int j)
{
    char    *tmp_path;
    time_t  tmp_time;

    tmp_path = data->paths.path[i];
    data->paths.path[i] = data->paths.path[j];
    data->paths.path[j] = tmp_path;

    tmp_time = data->paths.raw_time[i];
    data->paths.raw_time[i] = data->paths.raw_time[j];
    data->paths.raw_time[j] = tmp_time;
}

int     ft_cmp_time_dir_path(time_t a, time_t b)
{
        if (a < b)
            return (1);   // b is newer → swap
        if (a > b)
            return (0);
        return (-1);
}


int	ft_sort_array_paths_by_time(t_data *data)
{
	int	i;

	i = 0;
	while (i + 1 < data->paths.nbr_of_paths)
	{
		if (data->opt.op_r_flag == 0)
		{
			if (ft_cmp_time_dir_path(data->paths.raw_time[i], data->paths.raw_time[i + 1]))
				ft_swap_dir_path(data, i, i + 1);
			i = 0;
		}
		else
		{
			if (ft_cmp_time_dir_path(data->paths.raw_time[i], data->paths.raw_time[i + 1]) == 0)
				ft_swap_dir_path(data, i, i + 1);
			i = 0;
		}
		i++;	
	}
	return (0);
}

int ft_allocate_path_time(t_data *data)
{
    data->paths.raw_time = malloc(sizeof(time_t) * data->paths.nbr_of_paths);
    if (!data->paths.raw_time)
        return (1);
    return (0);
}

int ft_sort_dirs_paths_by_time(t_data *data)
{
    int i = 0;

    if (ft_allocate_path_time(data))
        return (1);

    while (i < data->paths.nbr_of_paths)
    {
        if (ft_get_path_time(data, i))
            return (1);
        i++;
    }

    ft_sort_array_paths_by_time(data);
    return (0);
}
