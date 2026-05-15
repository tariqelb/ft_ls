NAME= ft_ls.out

SRCS=	./ft_copy_delete_args.c \
	./ft_get_files_and_check_errors.c \
	./ft_get_options_and_check_errors.c \
	./ft_get_paths_and_check_errors.c \
	./ft_loop_over_options.c \
	./ft_ls.c \
	./ft_ls_utils_one.c \
	./ft_printf_utils.c 


FLAGS= -Werror -Wextra -Wall

all:
	gcc $(FLAGS) -o ${NAME} ${SRCS}

fclean:
	/bin/rm -rf ${NAME}

