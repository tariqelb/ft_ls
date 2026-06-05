/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_free_data.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tel-bouh <tariqelbouhali039@gmail.com>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/06/04 21:35:14 by tel-bouh          #+#    #+#             */
/*   Updated: 2026/06/04 21:52:41 by tel-bouh         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "./ft_ls.h"


void ft_free_str_array(char **arr)
{
    int i;

    if (!arr)
        return;
    i = 0;
    while (arr[i])
    {
        free(arr[i]);
        i++;
    }
    free(arr);
}

void ft_free_str_array_index(char **arr, int index)
{
    int i;

    if (!arr)
        return;
    i = 0;
    while (i < index)
    {
        free(arr[i]);
        i++;
    }
    free(arr);
}


void ft_free_paths_data(t_path *paths, int index)
{
    if (!paths)
        return;
    ft_free_str_array_index(paths->path, index);
    free(paths->raw_time);
}

void ft_free_files_data(t_file *files, int index)
{
    if (!files)
        return;
    ft_free_str_array_index(files->file, index);
}

void ft_free_short_format(t_short_format *lst)
{
    t_short_format *tmp;

    while (lst)
    {
        tmp = lst->next;
        free(lst->data); // ✅ malloc'ed
        free(lst);
        lst = tmp;
    }
}

void ft_free_long_format(t_long_format *lst)
{
    t_long_format *tmp;

    while (lst)
    {
        tmp = lst->next;
        free(lst);
        lst = tmp;
    }
}

void ft_free_data(t_data *data)
{
    if (!data)
        return;

    ft_free_str_array(data->args);
    ft_free_paths_data(&data->paths, data->paths.nbr_of_paths);
    ft_free_files_data(&data->files, data->files.nbr_of_files);
    ft_free_short_format(data->shrt_format);
    ft_free_long_format(data->lng_format);
}
