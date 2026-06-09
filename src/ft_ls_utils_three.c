/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_ls_utils_three.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tel-bouh <tariqelbouhali039@gmail.com>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/06/07 23:35:03 by tel-bouh          #+#    #+#             */
/*   Updated: 2026/06/08 01:12:57 by tel-bouh         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "./ft_ls.h"

static void	ft_get_join_info(char *dir, char *file, t_join_info *info)
{
	info->len_dir = ft_strlen(dir);
	info->len_file = ft_strlen(file);
	info->need_slash = (info->len_dir > 0 && dir[info->len_dir - 1] != '/');
}

static size_t	ft_copy_dir(char *dst, char *src)
{
	size_t	i;

	i = 0;
	while (src[i])
	{
		dst[i] = src[i];
		i++;
	}
	return (i);
}

static size_t	ft_copy_file(char *dst, char *src, size_t i)
{
	size_t	j;

	j = 0;
	while (src[j])
		dst[i++] = src[j++];
	return (i);
}

char	*ft_join_parrent_dir(char *filename, char *parrent_dir)
{
	t_join_info	info;
	char		*res;
	size_t		i;

	if (!filename || !parrent_dir)
		return (NULL);
	ft_get_join_info(parrent_dir, filename, &info);
	res = malloc(info.len_dir + info.need_slash + info.len_file + 1);
	if (!res)
		return (NULL);
	i = ft_copy_dir(res, parrent_dir);
	if (info.need_slash)
		res[i++] = '/';
	i = ft_copy_file(res, filename, i);
	res[i] = '\0';
	return (res);
}

void	*ft_memcpy(void *dest, void *src, size_t n)
{
	size_t				i;
	unsigned char		*d;
	const unsigned char	*s;

	if (!dest && !src)
		return (NULL);
	d = (unsigned char *)dest;
	s = (const unsigned char *)src;
	i = 0;
	while (i < n)
	{
		d[i] = s[i];
		i++;
	}
	return (dest);
}
