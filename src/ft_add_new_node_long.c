/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_add_new_node_long.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tel-bouh <tariqelbouhali039@gmail.com>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/06/09 00:44:13 by tel-bouh          #+#    #+#             */
/*   Updated: 2026/06/09 23:31:19 by tel-bouh         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "./ft_ls.h"

t_long_format	*ft_create_long_node(void)
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

void	ft_fill_stat_info(t_long_format *node, struct stat st)
{
	node->links = st.st_nlink;
	node->size = st.st_size;
	ft_fill_permissions(node->permission, st.st_mode);
	ft_fill_owner(node, &st);
	ft_fill_time(node->time, st.st_mtime);
}

int	ft_fill_names(t_long_format *node, char *filename, char *prnt_dir)
{
	int	j;

	if (!prnt_dir)
		return (0);
	ft_strcpy(node->filename, filename);
	j = 0;
	while (prnt_dir[j] && j < 255)
	{
		node->prnt_dir[j] = prnt_dir[j];
		j++;
	}
	node->prnt_dir[j] = '\0';
	return (1);
}

void	ft_set_type_flags(t_long_format *node, struct stat st)
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

t_long_format	*ft_new_long_node(t_data *data, int i,
			struct stat st, char *prnt_dir)
{
	t_long_format	*node;
	char			full_path[PATH_MAX];

	node = ft_create_long_node();
	if (!node)
		return (NULL);
	ft_fill_stat_info(node, st);
	if (!ft_fill_names(node, data->files.file[i], prnt_dir))
		return (free(node), NULL);
	ft_set_type_flags(node, st);
	if (node->is_exe_or_link == 2)
	{
		ft_bzero(node->link_file, PATH_MAX);
		ft_strcpy(full_path, prnt_dir);
		ft_strcat(full_path, "/");
		ft_strcat(full_path, data->files.file[i]);
		data->i = readlink(full_path, node->link_file, PATH_MAX - 1);
		if (data->i != -1)
			node->link_file[data->i] = '\0';
		else
			node->link_file[0] = '\0';
	}
	else
		node->link_file[0] = '\0';
	return (node);
}
