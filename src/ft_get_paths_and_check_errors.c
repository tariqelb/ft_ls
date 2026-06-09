/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_get_paths_and_check_errors.c                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tel-bouh <tariqelbouhali039@gmail.com>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/05/12 15:32:02 by tel-bouh          #+#    #+#             */
/*   Updated: 2026/06/06 23:05:55 by tel-bouh         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "./ft_ls.h"

static int	ft_display_error(int err, char *av, t_data *data, int i)
{
	if (err == 1)
	{
		ft_putstr_std("ft_ls: cannot access '", 2);
		ft_putstr_std(av, 2);
		ft_putstr_std("': No such file or directory\n", 2);
	}
	else if (err == 2)
		ft_putstr_std("ft_ls: error allocation memory\n", 2);
	else if (err == 3)
	{
		ft_putstr_std("ls: cannot access '", 2);
		ft_putstr_std(av, 2);
		ft_putstr_std("': File name too long\n", 2);
	}
	ft_remove_arg(data, i);
	return (1);
}

int	ft_check_if_its_a_dir(char *av, t_data *data, int i)
{
	struct stat	st;

	if (stat(av, &st) != 0)
	{
		return (ft_display_error(1, av, data, i));
	}
	if (S_ISDIR(st.st_mode))
	{
		if (ft_strlen(av) < 4097)
			return (0);
		else
			return (ft_display_error(3, av, data, i));
		printf("--\n");
	}
	else
		return (-1);
	return (0);
}

void	ft_free_paths(t_data *data)
{
	int	i;

	if (data->paths.path == NULL)
		return ;
	i = 0;
	while (data->paths.path[i] && i < data->paths.nbr_of_paths)
	{
		if (data->paths.path[i])
			free(data->paths.path[i]);
		i++;
	}
	if (data->paths.path)
		free(data->paths.path);
	data->paths.path = NULL;
}

void	ft_free_until(char **arr, int index)
{
	int	i;

	i = 0;
	if (arr == NULL)
		return ;
	while (i < index)
	{
		if (arr[i])
			free(arr[i]);
		i++;
	}
	free(arr);
}

int	ft_get_paths_and_check_errors(char **av, t_data *data)
{
	int	i;
	int	malloc_err;

	malloc_err = 0;
	i = 0;
	while (av && av[i] != NULL)
	{
		if (av[i][0] != '-')
		{
			i -= ft_check_this_arg_is_valid_path(data, av[i], i, &malloc_err);
			if (malloc_err)
				return (1);
		}
		i++;
	}
	return (0);
}
