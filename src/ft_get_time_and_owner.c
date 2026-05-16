/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_get_long_ls_data.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tel-bouh <tariqelbouhali039@gmail.com>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/05/16 23:47:41 by tel-bouh          #+#    #+#             */
/*   Updated: 2026/05/17 00:39:43 by tel-bouh         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "./ft_ls.h"

#include <time.h>

/*
** Extract formatted time from ctime
** Format: "Mmm dd hh:mm"
*/

void	ft_fill_time(char *dest, time_t t)
{
	char    *tmp;
	int     i;
	int     j;

	tmp = ctime(&t);
	if (!tmp)
		return;

	i = 4;   // skip day name
	j = 0;

	while (tmp[i] && j < 12)
	{
		dest[j] = tmp[i];
		j++;
		i++;
	}
	dest[j] = '\0';
}

/*
** Fill user and group names from uid/gid
*/

void ft_fill_owner(t_long_format *fmt, struct stat *st)
{
	struct passwd *pw;
	struct group  *gr;

	pw = getpwuid(st->st_uid);
	gr = getgrgid(st->st_gid);

	// copy user name if exists
	if (pw)
	    ft_strcpy(fmt->user, pw->pw_name);
	else
	    ft_strcpy(fmt->user, "unknown");

	// copy group name if exists
	if (gr)
	    ft_strcpy(fmt->grop, gr->gr_name);
	else
	    ft_strcpy(fmt->grop, "unknown");
}
