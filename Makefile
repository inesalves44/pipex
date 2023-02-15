# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: idias-al <idias-al@student.42porto.com>    +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2022/11/12 19:02:37 by idias-al          #+#    #+#              #
#    Updated: 2023/01/12 00:02:33 by idias-al         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

OBJS_LIBFT		=	ft_printf/libft/ft_isalnum.o ft_printf/libft/ft_isalpha.o ft_printf/libft/ft_isascii.o ft_printf/libft/ft_isdigit.o \
					ft_printf/libft/ft_isprint.o ft_printf/libft/ft_memcmp.o ft_printf/libft/ft_putchar_fd.o ft_printf/libft/ft_split.o\
					ft_printf/libft/ft_strlcat.o ft_printf/libft/ft_strncmp.o ft_printf/libft/ft_substr.o ft_printf/libft/ft_atoi.o \
					ft_printf/libft/ft_itoa.o ft_printf/libft/ft_memcpy.o ft_printf/libft/ft_putendl_fd.o ft_printf/libft/ft_strchr.o \
					ft_printf/libft/ft_strlcpy.o \
					ft_printf/libft/ft_strnstr.o ft_printf/libft/ft_tolower.o ft_printf/libft/ft_bzero.o  ft_printf/libft/ft_strmapi.o\
					ft_printf/libft/ft_memmove.o ft_printf/libft/ft_putnbr_fd.o ft_printf/libft/ft_strdup.o ft_printf/libft/ft_strlen.o\
					 ft_printf/libft/ft_strrchr.o\
					ft_printf/libft/ft_toupper.o ft_printf/libft/ft_calloc.o ft_printf/libft/ft_memchr.o ft_printf/libft/ft_memset.o \
					ft_printf/libft/ft_putstr_fd.o ft_printf/libft/ft_strjoin.o ft_printf/libft/ft_strtrim.o \
					ft_printf/libft/ft_striteri.o

BONUS			=	ft_printf/libft/ft_lstadd_back.o ft_printf/libft/ft_lstadd_front.o ft_printf/libft/ft_lstclear.o \
					ft_printf/libft/ft_lstdelone.o ft_printf/libft/ft_lstiter.o ft_printf/libft/ft_lstlast.o \
					ft_printf/libft/ft_lstmap.o ft_printf/libft/ft_lstnew.o ft_printf/libft/ft_lstsize.o
OBJS_PRINTF		=	ft_printf/srcs/ft_printf.o ft_printf/srcs/ft_printhexa.o ft_printf/srcs/ft_print_simple.o\
				 	ft_printf/srcs/ft_printunsigned.o ft_printf/srcs/ft_pointer.o
OBJS_PIPEX		=	mandatory/main.o mandatory/error_free.o mandatory/do_cmd.o
OBJS_BONUS_PIPEX = bonus/main_bonus.o bonus/do_fork_bonus.o bonus/get_path_bonus.o bonus/error_free_bonus.o \
					bonus/here_doc_bonus.o gnl/get_next_line.o gnl/get_next_line_utils.o 
CC				= cc
RM				= rm -f
INCLUDES		= incs/
CFLAGS			= -Wall -Wextra -Werror
NAME			= pipex

all:			$(NAME)

$(NAME):		$(OBJS_PIPEX) $(OBJS_PRINTF) $(OBJS_LIBFT) $(BONUS)
				$(MAKE) bonus -C ft_printf/libft
				$(MAKE)	all -C ft_printf
				$(CC) $(CFLAGS) -o $(NAME) $(BONUS) $(OBJS_LIBFT) $(OBJS_PRINTF) $(OBJS_PIPEX)

bonus:			$(NAME) $(OBJS_BONUS_PIPEX) $(OBJS_PRINTF) $(OBJS_LIBFT) $(BONUS)
				$(CC) $(CFLAGS) -o $(NAME) $(BONUS) $(OBJS_LIBFT) $(OBJS_PRINTF) $(OBJS_BONUS_PIPEX) 

clean:
				$(MAKE) clean -C ft_printf/libft
				$(MAKE) clean -C ft_printf
				$(RM) $(OBJS_PIPEX) $(OBJS_BONUS_PIPEX)

fclean:			clean
				$(MAKE) fclean -C ft_printf/libft
				$(MAKE) fclean -C ft_printf
				$(RM) $(NAME)

re:				fclean all

rebonus:		fclean bonus

