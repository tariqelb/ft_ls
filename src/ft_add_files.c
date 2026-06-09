/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_add_files.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tel-bouh <tariqelbouhali039@gmail.com>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/06/06 16:55:53 by tel-bouh          #+#    #+#             */
/*   Updated: 2026/06/06 17:24:32 by tel-bouh         ###   ########.fr       */
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

static int	ft_copy_old_files(t_data *data, char **new_files,
			int *malloc_err, char *av)
{
	int	i;
	int	j;

	i = 0;
	while (i < data->files.nbr_of_files)
	{
		new_files[i] = malloc(ft_strlen(data->files.file[i]) + 1);
		if (new_files[i] == NULL)
		{
			ft_free_until(new_files, i);
			ft_free_files(data);
			*malloc_err = 1;
			return (ft_display_error(2, av, data, data->i));
		}
		j = 0;
		while (data->files.file[i][j])
		{
			new_files[i][j] = data->files.file[i][j];
			j++;
		}
		new_files[i][j] = 0;
		i++;
	}
	return (0);
}

static char	**ft_alloc_new_files(t_data *data, int *malloc_err,
			char *av, int index)
{
	char	**new_files;

	new_files = malloc(sizeof(char *) * (data->files.nbr_of_files + 2));
	if (!new_files)
	{
		*malloc_err = 1;
		ft_free_files(data);
		ft_display_error(2, av, data, index);
		return (NULL);
	}
	return (new_files);
}

static char	*ft_dup_file(char *av, t_data *data, int index, int *malloc_err)
{
	char	*temp;

	temp = ft_strdup(av);
	if (temp == NULL)
	{
		*malloc_err = 1;
		ft_free_files(data);
		ft_display_error(2, av, data, index);
		return (NULL);
	}
	return (temp);
}

int	ft_add_file(t_data *data, char *av, int index, int *malloc_err)
{
	char	**new_files;
	char	*temp;
	int		ret;

	if (ft_check_filename_length(av))
		return (ft_display_error(3, av, data, index));
	if (access(av, F_OK) != 0)
		ft_display_error(1, av, data, index);
	temp = ft_dup_file(av, data, index, malloc_err);
	if (!temp)
		return (1);
	new_files = ft_alloc_new_files(data, malloc_err, av, index);
	if (!new_files)
		return (1);
	data->i = index;
	ret = ft_copy_old_files(data, new_files, malloc_err, av);
	if (ret != 0)
		return (ret);
	new_files[data->files.nbr_of_files] = temp;
	new_files[data->files.nbr_of_files + 1] = NULL;
	ft_free_files(data);
	data->files.file = new_files;
	data->files.nbr_of_files++;
	return (0);
}
