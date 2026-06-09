/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_ls_struct_utils.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tel-bouh <tariqelbouhali039@gmail.com>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/05/16 17:18:11 by tel-bouh          #+#    #+#             */
/*   Updated: 2026/06/08 22:53:36 by tel-bouh         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "./ft_ls.h"

static t_short_format	*ft_create_node(void)
{
	t_short_format	*node;

	node = (t_short_format *)malloc(sizeof(t_short_format));
	if (!node)
	{
		ft_putstr_std("ft_ls: error, fail to allocate memory\n", 2);
		return (NULL);
	}
	return (node);
}

static int	ft_fill_name(t_short_format *node, char *data, size_t size)
{
	size_t	i;

	node->data = malloc(size + 1);
	if (!node->data)
		return (0);
	i = 0;
	while (i < size)
	{
		node->data[i] = data[i];
		i++;
	}
	node->data[i] = '\0';
	return (1);
}

static void	ft_fill_parent_dir(t_short_format *node, char *prnt_dir)
{
	int	j;

	j = 0;
	while (prnt_dir[j])
	{
		node->prnt_dir[j] = prnt_dir[j];
		j++;
	}
	node->prnt_dir[j] = '\0';
}

static void	ft_fill_type(t_short_format *node, struct stat st)
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

t_short_format	*ft_add_new(char *data, size_t size,
			struct stat st, char *prnt_dir)
{
	t_short_format	*node;

	node = ft_create_node();
	if (!node)
		return (NULL);
	if (!ft_fill_name(node, data, size))
	{
		free(node);
		return (NULL);
	}
	node->raw_time = st.st_mtime;
	ft_fill_parent_dir(node, prnt_dir);
	ft_fill_type(node, st);
	node->next = NULL;
	return (node);
}
