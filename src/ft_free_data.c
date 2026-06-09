/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_free_data.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tel-bouh <tariqelbouhali039@gmail.com>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/06/04 21:35:14 by tel-bouh          #+#    #+#             */
/*   Updated: 2026/06/06 22:12:36 by tel-bouh         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "./ft_ls.h"

void	ft_free_short_format(t_short_format *lst)
{
	t_short_format	*tmp;

	while (lst)
	{
		tmp = lst->next;
		free(lst->data);
		free(lst);
		lst = tmp;
	}
}

void	ft_free_long_format(t_long_format *lst)
{
	t_long_format	*tmp;

	while (lst)
	{
		tmp = lst->next;
		free(lst);
		lst = tmp;
	}
}

void	ft_free_data(t_data *data)
{
	if (!data)
		return ;
	ft_free_str_array(data->args);
	ft_free_paths_data(&data->paths, data->paths.nbr_of_paths);
	ft_free_files_data(&data->files, data->files.nbr_of_files);
	ft_free_short_format(data->shrt_format);
	ft_free_long_format(data->lng_format);
}
