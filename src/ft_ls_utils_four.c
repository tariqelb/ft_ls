/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_ls_utils_four.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tel-bouh <tariqelbouhali039@gmail.com>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/06/08 00:56:18 by tel-bouh          #+#    #+#             */
/*   Updated: 2026/06/08 01:09:16 by tel-bouh         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "./ft_ls.h"

static size_t	ft_find_last_slash(char *path)
{
	size_t	i;

	i = ft_strlen(path);
	while (i > 0 && path[i - 1] != '/')
		i--;
	return (i);
}

static char	*ft_return_dot(void)
{
	char	*res;

	res = malloc(2);
	if (!res)
		return (NULL);
	res[0] = '.';
	res[1] = '\0';
	return (res);
}

static char	*ft_copy_dir_part(char *filepath, size_t len)
{
	char	*res;
	size_t	i;

	res = malloc(len + 1);
	if (!res)
		return (NULL);
	i = 0;
	while (i < len)
	{
		res[i] = filepath[i];
		i++;
	}
	res[len] = '\0';
	if (len > 1 && res[len - 1] == '/')
		res[len - 1] = '\0';
	return (res);
}

char	*ft_get_dir_path(char *filepath)
{
	size_t	i;

	if (!filepath)
		return (NULL);
	i = ft_find_last_slash(filepath);
	if (i == 0)
		return (ft_return_dot());
	return (ft_copy_dir_part(filepath, i));
}
