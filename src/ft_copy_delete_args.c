/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_copy_delete_args.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tel-bouh <tariqelbouhali039@gmail.com>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/05/15 15:40:28 by tel-bouh          #+#    #+#             */
/*   Updated: 2026/06/04 16:53:59 by tel-bouh         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "./ft_ls.h"

int ft_remove_arg(t_data *data, int index)
{
	int i;

	if (!data->args || index < 0)
		return (1);
	if (!data->args[index])
		return (1);
	free(data->args[index]);
	i = index;
	while (data->args[i])
	{
		data->args[i] = data->args[i + 1];
		i++;
	}
	return (0);
}

int ft_copy_args(int ac, char **av, t_data *data)
{
	int i;

	data->args = NULL;
	if (ac == 1)
	{
		data->args = malloc(sizeof(char *) * 2);
		if (!data->args)
			return (1);
		data->args[0] = ft_strdup(".");
		data->args[1] = NULL;
		return (0);
	}
	data->args = malloc(sizeof(char *) * ac);
	if (!data->args)
		return (1);

	i = 1;
	while (i < ac)
	{
		data->args[i - 1] = ft_strdup(av[i]);
		if (!data->args[i - 1])
			return (1);
		i++;
	}
	data->args[i - 1] = NULL;
	if (ft_add_cwd_if_needed(data))
		return (1);
	return (0);
}
