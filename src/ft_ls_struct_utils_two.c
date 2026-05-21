/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_ls_struct_utils_two.c                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tel-bouh <tariqelbouhali039@gmail.com>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/05/16 23:24:26 by tel-bouh          #+#    #+#             */
/*   Updated: 2026/05/21 03:39:15 by tel-bouh         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "./ft_ls.h"

t_long_format   *ft_new_long_node_dir(t_data *data, char *entry_name, struct stat st, char *prnt_dir)
{
//	printf("ft_new_long_node_dir\n");
        t_long_format   *node;
        int             i;
	(void) data;

        node = malloc(sizeof(t_long_format));
        if (!node)
                return (NULL);

        node->links = st.st_nlink;
        node->size = st.st_size;
        node->next = NULL;

        ft_fill_permissions(node->permission, st.st_mode);
        ft_fill_owner(node, &st);
        ft_fill_time(node->time, st.st_mtime);

        ft_strcpy(node->filename, entry_name);
 
        i = 0;
        while (prnt_dir[i])
        {
                node->prnt_dir[i] = prnt_dir[i];
                i++;
        }
        node->prnt_dir[i] = '\0';
//	printf("---> [%s] [%s] [%d]\n", entry_name, prnt_dir, S_ISDIR(st.st_mode));
	if(S_ISDIR(st.st_mode))
		node->is_dir = 1;
	else
		node->is_dir = 0;
        return (node);
}

t_long_format *ft_new_long_node(t_data *data, int i, struct stat st, char *prnt_dir)
{
	printf("ft_new_long_node\n");
	t_long_format *node;
	int j;

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

	j = 0;
	if (!prnt_dir)
		return (free(node), NULL);

	while (prnt_dir[j] && j < 255)
	{
		node->prnt_dir[j] = prnt_dir[j];
		j++;
	}
	node->prnt_dir[j] = '\0';

	node->is_dir = S_ISDIR(st.st_mode);

	return (node);
}

void	ft_long_add_back(t_long_format **node, t_long_format *new_node)
{
//	printf("ft_long_add_back\n");
	t_long_format	*tmp;

	if (!node || !new_node)
		return;

	new_node->next = NULL;

	// ✅ correct empty list check
	if (*node == NULL)
	{
		*node = new_node;
		return;
	}

	tmp = *node;
	while (tmp->next)
	{
		tmp = tmp->next;
	}
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

int	ft_count_struct_elem_long(t_data *data)
{
	int		len;
	t_long_format	*temp;

	if (!data || !data->lng_format)
		return (0);
	temp = data->lng_format;
	len = 0;
	while (temp)
	{
		temp = temp->next;
		len++;
	}
	return (len);
}

int	ft_count_struct_elem_short(t_data *data)
{
	int		len;
	t_short_format	*temp;

	if (!data || !data->shrt_format)
		return (0);
	temp = data->shrt_format;
	len = 0;
	while (temp)
	{
		temp = temp->next;
		len++;
	}
	return (len);
}
