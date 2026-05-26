/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_get_files_and_check_errors.c                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tel-bouh <tariqelbouhali039@gmail.com>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/05/12 17:15:00 by tel-bouh          #+#    #+#             */
/*   Updated: 2026/05/26 01:10:30 by tel-bouh         ###   ########.fr       */
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
	int i;
	int len;

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

int ft_add_file(t_data *data, char *av, int index)
{
	char	**new_files;
	int	i;

	if (ft_check_filename_length(av))
		return (ft_display_error(3, av, data, index));
	if (access(av, F_OK) != 0)
		ft_display_error(1, av, data, index);
	new_files = malloc(sizeof(char *) * (data->files.nbr_of_files + 1));
	if (!new_files)
		return (ft_display_error(2, av, data, index));
	i = 0;
	while (i < data->files.nbr_of_files)
	{
		new_files[i] = data->files.file[i];
		i++;
	}
	new_files[i] = ft_strdup(av);
	if (!new_files[i])
	{
		free(new_files);
		return (ft_display_error(2, av, data, index));
	}
	free(data->files.file);
	data->files.file = new_files;
	data->files.nbr_of_files++;
	return (0);
}

int ft_get_files_and_check_errors(char **av, t_data *data)
{
	int i;
	struct stat st;

	i = 0;
	while (av && av[i] != NULL)
	{
		if (av[i][0] != '-')
		{
			if (stat(av[i], &st))
				i -= ft_display_error(1, av[i], data, i);
			else if (!S_ISDIR(st.st_mode))
			{
				i -= ft_add_file(data, av[i], i);
			}
		}
		i++;
	}
	return (0);
} 
