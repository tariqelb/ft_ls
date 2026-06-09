/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_ls_utils_two.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tel-bouh <tariqelbouhali039@gmail.com>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/05/28 21:44:54 by tel-bouh          #+#    #+#             */
/*   Updated: 2026/06/09 01:45:29 by tel-bouh         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "./ft_ls.h"

int	ft_numlen(size_t n)
{
	int	len;

	len = 1;
	while (n >= 10)
	{
		n /= 10;
		len++;
	}
	return (len);
}

int	ft_get_max_size_width(t_long_format *lst)
{
	int	max;
	int	len;

	max = 0;
	while (lst)
	{
		len = ft_numlen(lst->size);
		if (len > max)
			max = len;
		lst = lst->next;
	}
	return (max);
}

void	ft_print_padded_size(size_t size, int max_width)
{
	int	len;
	int	padding;

	len = ft_numlen(size);
	padding = max_width - len;
	while (padding-- > 0)
		write(1, " ", 1);
	ft_put_size_t(size, 1);
}
