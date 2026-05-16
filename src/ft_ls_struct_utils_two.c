/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_ls_struct_utils_two.c                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tel-bouh <tariqelbouhali039@gmail.com>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/05/16 23:24:26 by tel-bouh          #+#    #+#             */
/*   Updated: 2026/05/16 23:32:05 by tel-bouh         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "./ft_ls.h"

t_long_format	*ft_new_long_node(t_data *data, int i, struct stat st)
{
	t_long_format *node;

	node = malloc(sizeof(t_long_format));
	if (!node)
		return (NULL);

	node->links = st.st_nlink;
	node->size = st.st_size;
	node->next = NULL;

	ft_fill_permissions(node->permission, st.st_mode);
	ft_fill_owner(node, &st);
	ft_fill_time(node->time, st.st_mtime);

	ft_strcpy(node->filename, data->files.file[i]);

	node->prnt_dit[0] = '\0';

	return (node);
}

void	ft_long_add_back(t_long_format **lst, t_long_format *new_node)
{
	t_long_format *tmp;

	if (!lst || !new_node)
		return;

	if (!*lst)
	{
		*lst = new_node;
		return;
	}

	tmp = *lst;
	while (tmp->next)
		tmp = tmp->next;

	tmp->next = new_node;
}

void	ft_free_long_format(t_long_format *lst)
{
	t_long_format *tmp;

	while (lst)
	{
		tmp = lst->next;
		free(lst);
		lst = tmp;
	}
}

