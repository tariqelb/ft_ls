/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_ls.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tel-bouh <tariqelbouhali039@gmail.com>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/05/10 00:24:48 by tel-bouh          #+#    #+#             */
/*   Updated: 2026/06/09 23:36:11 by tel-bouh         ###   ########.fr       */
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
# include <stddef.h>
# include <sys/ioctl.h>
# include <limits.h> 
# include <stddef.h>

typedef struct	s_options
{
	short	op_l_flag;
	short	op_R_flag;
	short	op_a_flag;
	short	op_r_flag;
	short	op_t_flag;
	short	nbr_of_opt;
}		t_options;

typedef struct	s_path
{
	char	**path;
	time_t  *raw_time;
	int	nbr_of_paths;
}		t_path;

typedef struct	s_files
{
	char	**file;
	int	nbr_of_files;
}		t_file;

typedef struct	s_short_format
{
	char			*data;
	char			prnt_dir[256];
	short			is_dir;
	short			is_exe_or_link;
	time_t  		raw_time;
	struct s_short_format	*next;
}		t_short_format;

typedef struct	s_long_format
{
	char			permission[11];
	size_t			links;
	char			user[33];
	char			grop[33];
	size_t			size;
	time_t  		raw_time;
	char			time[13];
	char			filename[256];
	char			link_file[PATH_MAX];
	char			prnt_dir[256];
	short			is_dir;
	short			is_exe_or_link;
	size_t			total;
	struct s_long_format	*next;
}		t_long_format;

typedef struct	s_data
{
	int		first_dir;
	int		i;
	int		j;
	char		**args;
	t_path		paths;
	t_file		files;
	t_options	opt;
	t_short_format	*shrt_format;
	t_long_format	*lng_format;
}		t_data;

typedef struct s_dir
{
	DIR             *dir;
	struct dirent   *entry;
	struct stat     st;
	char            *path;
	size_t          total;
}		t_dir;

typedef struct s_fol_at
{
	DIR             *dir;
	struct dirent   *entry;
	struct stat     st;
	char            *path;
	size_t          total;
	char            *p_dir_path;
	int             nbr_of_elem;
}		t_fol_at;

typedef struct	s_join_info
{
    size_t  len_dir;
    size_t  len_file;
    int     need_slash;
}		t_join_info;

typedef struct	s_new_node_dir
{
	char *entry_name;
	struct stat st;
	char *prnt_dir;
	size_t total;
}		t_new_node_dir;

typedef struct s_cal_lay
{
        t_short_format  **arr;
        int             count;
        int             term_width;
        int             *col_widths;
        int             *out_rows;
}       t_cal_lay;

typedef struct s_disp_ctx
{
    t_short_format  **arr;
    int             *col_widths;
    int             count;
    int             cols;
    int             rows;
}   t_disp_ctx;

//File : ft_add_cwd_util.c
int     ft_is_an_option(char *arg);

//File : ft_add_cwd.c
int    ft_add_cwd_if_needed(t_data *data);

//File: ft_copy_and_count_args_opt.c
int	ft_count_opt_and_args(t_data *data, int ac, int args);
int	ft_count_args(t_data data);
int	ft_its_only_options(t_data *data);

//File : ft_ls.c
t_data	ft_initialize_data_struct(t_data data);
//main()

//File : ft_check_options_errors.c
int	ft_get_options_and_check_errors(int ac, char **av, t_data *data);

//File : ft_display_errors.c
int     ft_display_help(void);

//File : ft_check_this_arg_is_valid_path.c
int     ft_check_this_arg_is_valid_path(t_data *data, char *av, int index, int *malloc_err);

//File :  ft_get_paths_and_check_errors.c
void    ft_free_paths(t_data *data);
void    ft_free_until(char **arr, int index);
int     ft_check_if_its_a_dir(char *av, t_data *data, int i);
int     ft_check_this_arg_is_valid_path(t_data *data, char *av, int index, int *malloc_err);
int     ft_get_paths_and_check_errors(char **av, t_data *data);

//File: ft_add_files.c
int	ft_add_file(t_data *data, char *av, int index, int *malloc_err); 

//File :  ft_get_files_and_check_errors.c
void    ft_free_files(t_data *data);
int     ft_check_filename_length(char *av);
int     ft_get_files_and_check_errors(char **av, t_data *data);

//File : ft_loop_over_options.c
void    ft_set_flag(short *flag, t_options *opt);
int     ft_free_args(t_data *data);
int     ft_parse_option_arg(char *arg, t_data *data);
int     ft_is_option(char *arg);
int     ft_loop_over_options(int ac, char **av, t_data *data);

//File : ft_ls_utils_one.c
char    *ft_path_join(char *dir, char *name);
char    *ft_strdup(char *s);
size_t  ft_strlen(char *s);
char    *ft_strcpy(char *dest, const char *src);
int     ft_strcmp(char *s1, char *s2);

//File : ft_ls_utils_four.c
char    *ft_get_dir_path(char *filepath);

//File : ft_ls_utils_three.c
char    *ft_join_parrent_dir(char *filename, char *parrent_dir);
void    *ft_memcpy(void *dest, void *src, size_t n);

//File : ft_copy_delete_args.c
int ft_copy_args(int ac, char **av, t_data *data);
int ft_remove_arg(t_data *data, int index);


//File: ft_ls_struct_utils.c
t_short_format	*ft_add_new(char *data, size_t size, struct stat st, char *prnt_dir);
void	ft_push_back(t_short_format **head, t_short_format *new_node);
void	ft_delete_all(t_short_format **head);
void    ft_push_back_at(t_short_format **node, t_short_format *new_node, int push_at);


//File: ft_ls_struct_utils_two.c
void    ft_free_long_format(t_long_format *lst);
void	ft_long_add_back(t_long_format **lst, t_long_format *new_node);
t_long_format   *ft_new_long_node(t_data *data, int i, struct stat st, char *prnt_dir);
t_long_format   *ft_new_long_node_dir(t_data *data, t_new_node_dir new_data);
int     ft_count_struct_elem_short(t_data *data);
int     ft_count_struct_elem_long(t_data *data);
void    ft_long_add_back_at(t_long_format **node, t_long_format *new_node, int push_at);


//File : ft_fill_permissions.c
void    ft_perm_type(char *perm, mode_t mode);
void    ft_perm_user(char *perm, mode_t mode);
void    ft_perm_group(char *perm, mode_t mode);
void    ft_perm_other(char *perm, mode_t mode);
void    ft_fill_permissions(char *perm, mode_t mode);

//File: ft_list_files.c
int     ft_get_long_format(t_data *data, int f_index, struct stat st);
int     ft_get_short_format(t_data *data, int f_index, struct stat st);
int     ft_list_single_file(t_data *data, int f_index);
int     ft_list_files(t_data *data);

//File : ft_iter_till_new_data_long_forma.c
int     ft_iterate_recursion_long_format(t_data *data, int we_reach);

//File : ft_iter_till_new_data_short_forma.c
int     ft_iterate_recursion_short_format(t_data *data, int we_reach);

//File: ft_start_listing.c
t_short_format  *ft_iter_till_new_data_short(t_data *data, int we_reach);
t_long_format   *ft_iter_till_new_data_long(t_data *data, int we_reach);
int     ft_start_listing(t_data *data);

//File: ft_get_time_and_owner.c 
void	ft_fill_time(char *dest, time_t t);
void	ft_fill_owner(t_long_format *fmt, struct stat *st);

//File: ft_display_format.c
void	ft_display_long_format(t_data *data);
void    ft_display_short_format(t_data *data);
void	ft_display_long_format_n_data(t_data *data, int len);
void    ft_display_short_format_n_data(t_data *data, int len);
void    ft_display_long_format_n_to_m_data(t_data *data, int start, int end);
void    ft_display_short_format_n_to_m_data(t_data *data, int start, int end);

//File : ft_display_format_column_two.c
int     ft_get_term_width(void);
int     ft_get_max_len(t_short_format *list);
int     ft_list_size(t_short_format *list);
void    ft_display_short_format_column(t_data *data);
t_short_format  **ft_build_array(t_short_format *start, int *count);

//File : ft_display_format_column.c
int     ft_prepare_layout(t_disp_ctx *ctx);
void    ft_print_cell(t_disp_ctx *ctx, int index, int col);
void    ft_print_grid(t_disp_ctx *ctx);
void    ft_display_short_format_n_data_column(t_data *data, int start);

//File: ft_list_directories.c
int     ft_get_long_format_dir(t_data *data, char *entry_name, int d_index, struct stat st);
int     ft_get_short_format_dir(t_data *data, char *entry_name, int d_index, struct stat st);
int     ft_list_dir(t_data *data, int d_index);
int     ft_list_directories(t_data *data);

//File: ft_list_folder_long.c
int     ft_list_folder_long_format_at(t_data *data, char *filename, char *prnt_dir, int i);
int     ft_list_folder_short_format_at(t_data *data, char *filename, char *prnt_dir, int i);


//File: ft_ls_sort_format.c
t_data	*ft_sort_short_format(t_data *data, int len);
t_data	*ft_sort_long_format(t_data *data, int len);

//File : ft_sort_all_data_long_short.c
t_data *ft_sort_long_format_all_data(t_data *data);
t_data *ft_sort_short_format_all_data(t_data *data);

//File : ft_ls_sort_data.c
void    ft_swap_short_data(t_short_format *a, t_short_format *b);
void    ft_swap_long_data(t_long_format *a, t_long_format *b);

//File: ft_print_dir_path_and_total.c
int     ft_print_folder_path(t_data *data, char *path);
size_t   ft_get_total(t_data *data, char *p_dir_path);
int     ft_display_total(t_data *data, size_t total);

//File: ft_ls_utils_two.c
int     ft_numlen(size_t n);
int     ft_get_max_size_width(t_long_format *lst);
void    ft_print_padded_size(size_t size, int max_width);


//File: ft_sort_by_time_short_n_elem.c
int     ft_cmp_time_short(t_data *data, t_short_format *a, t_short_format *b);
int     ft_cmp_time_short_upper_r_flag(t_data *data, t_short_format *a, t_short_format *b);
t_data  *ft_sort_by_time_short_n_elem(t_data *data, int short_len, int file);


//File: ft_sort_by_time_long_n_elem.c
int     ft_cmp_time(t_data *data, t_long_format *a, t_long_format *b);
int     ft_cmp_time_upper_r_flag(t_data *data, t_long_format *a, t_long_format *b);
t_data  *ft_sort_by_time_long_n_elem(t_data *data, int long_len, int file);

//File : ft_sort_by_time_short_all_data.c
t_data	*ft_sort_by_time_long_all_data(t_data *data);
t_data	*ft_sort_by_time_short_all_data(t_data *data);


//File : ft_sort_from_n_to_m_elem_long.c 
t_data	*ft_sort_format_data_from_elem_n_to_m_short(t_data *data, int short_len, int end);
t_data	*ft_sort_format_data_from_elem_n_to_m_long(t_data *data, int long_len, int end);

//File :  ft_sort_by_time_long_n_to_m_elem.c
t_data  *ft_sort_by_time_long_n_to_m_elem(t_data *data, int long_len, int end);


//File :  ft_sort_by_time_short_n_to_m_elem.c
t_data  *ft_sort_by_time_short_n_to_m_elem(t_data *data, int short_len, int end);


//File : ft_sort_dirs_paths_by_time.c 
int     ft_get_path_time(t_data *data, int i);
void    ft_swap_dir_path(t_data *data, int i, int j);
int     ft_cmp_time_dir_path(time_t a, time_t b);
int     ft_sort_array_paths_by_time(t_data *data);
int     ft_allocate_path_time(t_data *data);
int     ft_sort_dirs_paths_by_time(t_data *data);

//File : ft_set_exe_and_link_status.c 
void    ft_set_exec_and_link_status_short(t_short_format *node, struct stat st);
void    ft_set_exec_and_link_status_long(t_long_format *node, struct stat st);


//File : ft_calcule_column_padding.c
int     ft_get_col_max(t_cal_lay *lay, int col, int rows);
int     ft_fill_col_widths(t_cal_lay *lay, int cols, int rows);
int     ft_calculate_layout(t_cal_lay *lay);

//File : ft_free_data_util.c
void ft_free_str_array(char **arr);
void ft_free_str_array_index(char **arr, int index);
void ft_free_paths_data(t_path *paths, int index);
void ft_free_files_data(t_file *files, int index);

//File : ft_free_data.c
void ft_free_data(t_data *data);

//File : ft_get_long_short_format_dir.c
int     ft_get_long_format_dir(t_data *data, char *entry_name, int d_index, struct stat st);
int     ft_get_short_format_dir(t_data *data, char *entry_name, int d_index, struct stat st);

//File : ft_list_dir.c
int	ft_loop_over_dirs(t_data *data, t_dir *dir, int d_index);
int	ft_list_dir(t_data *data, int d_index);

//File : ft_list_directories_utils.c
t_data	*ft_resort_for_recursion(t_data *data, int we_reach);
void	ft_handle_recursion(t_data *data, int we_reach);
int	ft_update_we_reach(t_data *data);


//File : ft_get_long_short_file.c
int     ft_get_short_format(t_data *data, int f_index, struct stat st);
int     ft_get_long_format(t_data *data, int f_index, struct stat st);
char    ft_check_is_hiden_file(char *path_file);

//File : ft_get_long_short_format_folder_at.c
int     ft_get_long_format_folder_at(t_data *data, t_fol_at *f);
int     ft_get_short_format_folder_at(t_data *data, t_fol_at *f);
//File : ft_get_long_short_format_folder.c
int	ft_get_short_format_folder(t_data *data, t_fol_at *f);
int	ft_get_long_format_folder(t_data *data, t_fol_at *f);

//File : ft_sort_format_data_from_elem_n_long.c
t_data  *ft_sort_format_data_from_elem_n_long(t_data *data, int long_len);
t_long_format   *ft_get_start_long(t_long_format *head, int long_len);

//File : ft_sort_format_data_from_elem_n_short.c
t_data  *ft_sort_format_data_from_elem_n_short(t_data *data, int short_len);
t_short_format  *ft_get_start_short(t_short_format *head, int short_len);

//----------------ft_printf

int	ft_put_unsignedint(unsigned int nbr, int std);
int	ft_putint(int nbr,int std);
int	ft_puthex(unsigned int nbr, int flag, int std);
int	ft_putstr_std(char *str, int std);
int     ft_put_size_t(size_t nbr, int std);

//File : ft_strcat.c
char    *ft_strcat(char *dest, const char *src);
void    ft_put_str(char *str);
void    ft_bzero(void *s, size_t n);

#endif
