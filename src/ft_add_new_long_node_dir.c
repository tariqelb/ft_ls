/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_add_new_long_node_dir.c                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tel-bouh <tariqelbouhali039@gmail.com>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/06/09 00:42:30 by tel-bouh          #+#    #+#             */
/*   Updated: 2026/06/09 01:36:05 by tel-bouh         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "./ft_ls.h"

t_long_format	*ft_create_long_node_dir(void)
{
	t_long_format	*node;

	node = malloc(sizeof(t_long_format));
	if (!node)
	{
		ft_putstr_std("ft_ls: error, fail to allocate memory\n", 2);
		return (NULL);
	}
	node->next = NULL;
	return (node);
}

void	ft_fill_dir_stat(t_long_format *node, struct stat st)
{
	node->links = st.st_nlink;
	node->size = st.st_size;
	node->raw_time = st.st_mtime;
	ft_fill_permissions(node->permission, st.st_mode);
	ft_fill_owner(node, &st);
	ft_fill_time(node->time, st.st_mtime);
}

int	ft_fill_dir_names(t_long_format *node, t_new_node_dir new_data)
{
	int	i;

	ft_strcpy(node->filename, new_data.entry_name);
	i = 0;
	while (new_data.prnt_dir[i])
	{
		node->prnt_dir[i] = new_data.prnt_dir[i];
		i++;
	}
	node->prnt_dir[i] = '\0';
	return (1);
}

void	ft_set_dir_flags(t_long_format *node, struct stat st)
{
	if (S_ISLNK(st.st_mode))
	{
		node->is_dir = 0;
		node->is_exe_or_link = 2;
	}
	else if (S_ISDIR(st.st_mode))
	{
		node->is_dir = 1;
		node->is_exe_or_link = 0;
	}
	else
	{
		node->is_dir = 0;
		if (st.st_mode & (S_IXUSR | S_IXGRP | S_IXOTH))
			node->is_exe_or_link = 1;
		else
			node->is_exe_or_link = 0;
	}
}

t_long_format	*ft_new_long_node_dir(t_data *data, t_new_node_dir new_data)
{
	t_long_format	*node;

	(void)data;
	(void)new_data.total;
	node = ft_create_long_node_dir();
	if (!node)
		return (NULL);
	ft_fill_dir_stat(node, new_data.st);
	ft_fill_dir_names(node, new_data);
	ft_set_dir_flags(node, new_data.st);
	return (node);
}
