/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_get_files_and_check_errors.c                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tel-bouh <tariqelbouhali039@gmail.com>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/05/12 17:15:00 by tel-bouh          #+#    #+#             */
/*   Updated: 2026/06/06 17:24:49 by tel-bouh         ###   ########.fr       */
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

int	ft_check_filename_length(char *av)
{
	int	i;
	int	len;

	i = 0;
	len = 0;
	while (av[i])
		i++;
	while (i > 0 && av[i - 1] != '/')
	{
		len++;
		i--;
	}
	if (len >= 256)
		return (1);
	return (0);
}

void	ft_free_files(t_data *data)
{
	int	i;

	if (data->files.file == NULL)
		return ;
	i = 0;
	while (i < data->files.nbr_of_files)
	{
		if (data->files.file[i])
			free(data->files.file[i]);
		i++;
	}
	free(data->files.file);
	data->files.file = NULL;
}

int	ft_get_files_and_check_errors(char **av, t_data *data)
{
	struct stat	st;
	int			i;
	int			malloc_err;

	malloc_err = 0;
	i = 0;
	while (av && av[i] != NULL)
	{
		if (av[i][0] != '-')
		{
			if (stat(av[i], &st))
				i -= ft_display_error(1, av[i], data, i);
			else if (!S_ISDIR(st.st_mode))
			{
				i -= ft_add_file(data, av[i], i, &malloc_err);
				if (malloc_err)
					return (1);
			}
		}
		i++;
	}
	return (0);
}
