/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_set_exec_and_link_status.c                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tel-bouh <tariqelbouhali039@gmail.com>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/06/03 23:55:19 by tel-bouh          #+#    #+#             */
/*   Updated: 2026/06/04 00:14:37 by tel-bouh         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "./ft_ls.h"

void	ft_set_exec_and_link_status_long(t_long_format *node, struct stat st)
{
	if ((S_ISLNK(st.st_mode)))
		node->is_exe_or_link = 2;
	else if ((st.st_mode & S_IXUSR) || (st.st_mode & S_IXGRP) || (st.st_mode & S_IXOTH))
		node->is_exe_or_link = 1;
	else
		node->is_exe_or_link = 0;

}

void	ft_set_exec_and_link_status_short(t_short_format *node, struct stat st)
{
	if ((S_ISLNK(st.st_mode)))
		node->is_exe_or_link = 2;
	else if ((st.st_mode & S_IXUSR) || (st.st_mode & S_IXGRP) || (st.st_mode & S_IXOTH))
		node->is_exe_or_link = 1;
	else
		node->is_exe_or_link = 0;
}
