/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_ls_utils_one.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tel-bouh <tariqelbouhali039@gmail.com>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/05/12 16:13:19 by tel-bouh          #+#    #+#             */
/*   Updated: 2026/05/20 22:32:44 by tel-bouh         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "./ft_ls.h"

size_t	ft_strlen(char *s)
{
	size_t	i;

	i = 0;
	while (s[i])
		i++;
	return (i);
}

char	*ft_strdup(char *s)
{
	size_t	i;
	char	*dup;
 
	dup = malloc(ft_strlen(s) + 1);
	if (!dup)
		return (NULL);
	i = 0;  
	while (s[i])
	{
		dup[i] = s[i];
		i++;
	}
	dup[i] = '\0';
	return (dup);
}

char	*ft_strcpy(char *dest, const char *src)
{
	int	i;

	i = 0;
	while (src[i])
	{
		dest[i] = src[i];
		i++;
	}
	dest[i] = '\0';
	return (dest);
}

char    *ft_path_join(char *dir, char *name)
{
	size_t  len_dir = ft_strlen(dir);
	size_t  len_name = ft_strlen(name);
	char    *path;
	size_t  i = 0;
	size_t  j = 0;

	path = malloc(len_dir + len_name + 2); // + '/' + '\0'
	if (!path)
	    return (NULL);

	while (dir[i])
	{
	    path[i] = dir[i];
	    i++;
	}

	// add '/' only if not already there
	if (i > 0 && dir[i - 1] != '/')
	    path[i++] = '/';

	while (name[j])
	    path[i++] = name[j++];

	path[i] = '\0';
	return (path);
}

int	ft_strcmp(char *s1, char *s2)
{
	int i;

	i = 0;
	while (s1[i] && s2[i] && s1[i] == s2[i])
	    i++;
	return ((unsigned char)s1[i] - (unsigned char)s2[i]);
}

char	*ft_join_parrent_dir(char *filename, char *parrent_dir)
{
	size_t	len_dir;
	size_t	len_file;
	int		need_slash;
	char	*res;
	size_t	i;
	size_t	j;

	if (!filename || !parrent_dir)
		return (NULL);

	len_dir = ft_strlen(parrent_dir);
	len_file = ft_strlen(filename);
	need_slash = (len_dir > 0 && parrent_dir[len_dir - 1] != '/');

	res = malloc(len_dir + need_slash + len_file + 1);
	if (!res)
		return (NULL);

	i = 0;
	while (i < len_dir)
	{
		res[i] = parrent_dir[i];
		i++;
	}

	if (need_slash)
		res[i++] = '/';

	j = 0;
	while (j < len_file)
		res[i++] = filename[j++];

	res[i] = '\0';
	return (res);
}

char	*ft_get_dir_path(char *filepath)
{
	size_t	i;
	char	*res;

	if (!filepath)
		return (NULL);

	i = ft_strlen(filepath);

	// find last '/'
	while (i > 0 && filepath[i - 1] != '/')
		i--;

	// no '/' found → return "."
	if (i == 0)
	{
		res = malloc(2);
		if (!res)
			return (NULL);
		res[0] = '.';
		res[1] = '\0';
		return (res);
	}

	// allocate path up to '/'
	res = malloc(i + 1);
	if (!res)
		return (NULL);

	for (size_t j = 0; j < i; j++)
		res[j] = filepath[j];

	res[i] = '\0';

	// remove trailing '/' if it's not root "/"
	if (i > 1 && res[i - 1] == '/')
		res[i - 1] = '\0';

	return (res);
}

void	*ft_memcpy(void *dest, void *src, size_t n)
{
	size_t			i;
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
