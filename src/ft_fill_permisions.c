/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_fill_permisions.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tel-bouh <tariqelbouhali039@gmail.com>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/05/16 23:53:45 by tel-bouh          #+#    #+#             */
/*   Updated: 2026/06/06 22:05:12 by tel-bouh         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "./ft_ls.h"

void	ft_perm_type(char *perm, mode_t mode)
{
	if (S_ISLNK(mode))
		perm[0] = 'l';
	else if (S_ISDIR(mode))
		perm[0] = 'd';
	else
		perm[0] = '-';
}

void	ft_perm_user(char *perm, mode_t mode)
{
	if ((mode & S_IRUSR))
		perm[1] = 'r';
	else
		perm[1] = '-';
	if ((mode & S_IWUSR))
		perm[2] = 'w';
	else
		perm[2] = '-';
	if ((mode & S_IXUSR))
		perm[3] = 'x';
	else
		perm[3] = '-';
}

void	ft_perm_group(char *perm, mode_t mode)
{
	if (mode & S_IRGRP)
		perm[4] = 'r';
	else
		perm[4] = '-';
	if (mode & S_IWGRP)
		perm[5] = 'w';
	else
		perm[5] = '-';
	if (mode & S_IXGRP)
		perm[6] = 'x';
	else
		perm[6] = '-';
}

void	ft_perm_other(char *perm, mode_t mode)
{
	if (mode & S_IROTH)
		perm[7] = 'r';
	else
		perm[7] = '-';
	if (mode & S_IWOTH)
		perm[8] = 'w';
	else
		perm[8] = '-';
	if (mode & S_IXOTH)
		perm[9] = 'x';
	else
		perm[9] = '-';
}

void	ft_fill_permissions(char *perm, mode_t mode)
{
	ft_perm_type(perm, mode);
	ft_perm_user(perm, mode);
	ft_perm_group(perm, mode);
	ft_perm_other(perm, mode);
	perm[10] = '\0';
}
