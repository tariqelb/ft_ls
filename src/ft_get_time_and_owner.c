/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_get_time_and_owner.c                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tel-bouh <tariqelbouhali039@gmail.com>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/05/16 23:47:41 by tel-bouh          #+#    #+#             */
/*   Updated: 2026/06/08 16:06:57 by tel-bouh         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "./ft_ls.h"

static char	*ft_get_time_year(char *dest, char *tmp, int j, int i)
{
	i = 20;
	dest[j++] = ' ';
	dest[j++] = tmp[i++];
	dest[j++] = tmp[i++];
	dest[j++] = tmp[i++];
	dest[j++] = tmp[i++];
	dest[j++] = 0;
	return (dest);
}

void	ft_fill_time(char *dest, time_t t)
{
	time_t	now;
	char	*tmp;
	int		i;
	int		j;

	now = time(NULL);
	tmp = ctime(&t);
	if (!tmp)
		return ;
	i = 4;
	j = 0;
	if (t > now || now - t > 15768000)
	{
		while (j < 7)
			dest[j++] = tmp[i++];
		dest = ft_get_time_year(dest, tmp, j, i);
	}
	else
	{
		while (j < 12)
			dest[j++] = tmp[i++];
		dest[j] = '\0';
	}
}

void	ft_fill_owner(t_long_format *fmt, struct stat *st)
{
	struct passwd	*pw;
	struct group	*gr;

	pw = getpwuid(st->st_uid);
	gr = getgrgid(st->st_gid);
	if (pw)
		ft_strcpy(fmt->user, pw->pw_name);
	else
		ft_strcpy(fmt->user, "unknown");
	if (gr)
		ft_strcpy(fmt->grop, gr->gr_name);
	else
		ft_strcpy(fmt->grop, "unknown");
}
