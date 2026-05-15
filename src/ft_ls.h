/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_ls.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tel-bouh <tariqelbouhali039@gmail.com>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/05/10 00:24:48 by tel-bouh          #+#    #+#             */
/*   Updated: 2026/05/15 16:20:20 by tel-bouh         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FT_LS_H
# define FT_LS_H

# include <stdio.h>
# include <unistd.h>
# include <stdlib.h>
# include <sys/types.h>
# include <dirent.h>
# include <sys/stat.h>
# include <pwd.h>
# include <grp.h>
# include <sys/xattr.h>
# include <time.h>
# include <string.h>

typedef struct	s_options
{
	short	op_l_flag;
	short	op_R_flag;
	short	op_a_flag;
	short	op_r_flag;
	short	op_t_flag;
	short	nbr_of_opt;
}		t_options;

typedef struct	s_format
{
	char	permission[11];
	size_t	links;
	char	user[33];//limit 32
	char	grop[33];//limit 32
	size_t	size;
	char	time[13];
	char	filename[256];//limit 255
	char	prnt_dit[256];//limit 255
}		t_format;

typedef struct	s_path
{
		char	**path;
		int	nbr_of_paths;
}		t_path;

typedef struct	s_files
{
		char	**file;
		int	nbr_of_files;
}		t_file;

typedef struct	s_data
{
		char		**args;
		t_path		paths;
		t_file		files;
		t_options	opt;
		t_format	*lng_format;	
}		t_data;

//File : ft_ls.c

//File : ft_check_options_errors.c
int	ft_get_options_and_check_errors(int ac, char **av, t_data *data);

//File : ft_display_errors.c
int     ft_display_help(void);

//File :  ft_get_paths_and_check_errors.c
int     ft_check_this_arg_is_valid_path(t_data *data, char *av, int index);
int     ft_get_paths_and_check_errors(char **av, t_data *data);

//File :  ft_get_files_and_check_errors.c
int	ft_add_file(t_data *data, char *av, int index); 
int     ft_get_files_and_check_errors(char **av, t_data *data);

//File : ft_loop_over_options.c
void    ft_set_flag(short *flag, t_options *opt);
int     ft_free_args(t_data *data);
int     ft_parse_option_arg(char *arg, t_data *data);
int     ft_is_option(char *arg);
int     ft_loop_over_options(int ac, char **av, t_data *data);

//File : ft_ls_utils_one.c
char    *ft_strdup(char *s);
size_t  ft_strlen(char *s);

//File : ft_copy_delete_args.c
int ft_copy_args(int ac, char **av, t_data *data);
int ft_remove_arg(t_data *data, int index);


//----------------ft_printf

int	ft_put_unsignedint(unsigned int nbr, int std);
int	ft_putint(int nbr,int std);
int	ft_puthex(unsigned int nbr, int flag, int std);
int	ft_putstr_std(char *str, int std);
int     ft_put_size_t(size_t nbr, int std);


//
#endif
