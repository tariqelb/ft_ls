/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_free_data_util.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tel-bouh <tariqelbouhali039@gmail.com>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/06/06 22:07:10 by tel-bouh          #+#    #+#             */
/*   Updated: 2026/06/06 22:11:16 by tel-bouh         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "./ft_ls.h"

void	ft_free_str_array(char **arr)
{
	int	i;

	if (!arr)
		return ;
	i = 0;
	while (arr[i])
	{
		free(arr[i]);
		i++;
	}
	free(arr);
}

void	ft_free_str_array_index(char **arr, int index)
{
	int	i;

	if (!arr)
		return ;
	i = 0;
	while (i < index)
	{
		free(arr[i]);
		i++;
	}
	free(arr);
}

void	ft_free_paths_data(t_path *paths, int index)
{
	if (!paths)
		return ;
	ft_free_str_array_index(paths->path, index);
	free(paths->raw_time);
}

void	ft_free_files_data(t_file *files, int index)
{
	if (!files)
		return ;
	ft_free_str_array_index(files->file, index);
}
