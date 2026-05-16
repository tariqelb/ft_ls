/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_fill_permisions.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tel-bouh <tariqelbouhali039@gmail.com>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/05/16 23:53:45 by tel-bouh          #+#    #+#             */
/*   Updated: 2026/05/16 23:56:38 by tel-bouh         ###   ########.fr       */
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
    perm[1] = (mode & S_IRUSR) ? 'r' : '-';
    perm[2] = (mode & S_IWUSR) ? 'w' : '-';
    perm[3] = (mode & S_IXUSR) ? 'x' : '-';
}

void	ft_perm_group(char *perm, mode_t mode)
{
    perm[4] = (mode & S_IRGRP) ? 'r' : '-';
    perm[5] = (mode & S_IWGRP) ? 'w' : '-';
    perm[6] = (mode & S_IXGRP) ? 'x' : '-';
}

void	ft_perm_other(char *perm, mode_t mode)
{
    perm[7] = (mode & S_IROTH) ? 'r' : '-';
    perm[8] = (mode & S_IWOTH) ? 'w' : '-';
    perm[9] = (mode & S_IXOTH) ? 'x' : '-';
}

void	ft_fill_permissions(char *perm, mode_t mode)
{
    ft_perm_type(perm, mode);
    ft_perm_user(perm, mode);
    ft_perm_group(perm, mode);
    ft_perm_other(perm, mode);
    perm[10] = '\0';
}
