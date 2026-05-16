/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_start_listing.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tel-bouh <tariqelbouhali039@gmail.com>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/05/15 23:30:34 by tel-bouh          #+#    #+#             */
/*   Updated: 2026/05/17 00:09:35 by tel-bouh         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "./ft_ls.h"

int	ft_start_listing(t_data *data)
{
	//ls start listing file the dirs
	printf("start start listing -------------------------\n");
	ft_list_files(data);
	printf("end start listing ---------------------------\n");
	return (0);
}
