# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: ysushkov <marvin@42.fr>                    +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2018/04/24 14:51:09 by ysushkov          #+#    #+#              #
#    Updated: 2018/08/06 10:15:14 by ysushkov         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME	:=	ft_ssl

CC	:=	clang

FLAG	:=	-Wall -Werror -Wextra

HEAD	:=	./includes

LIB	:=	./libft/libft.a

SRCS	:=	srcs/md5.c srcs/sha224.c srcs/sha256.c srcs/sha384.c srcs/sha512.c \
			srcs/print.c srcs/print64.c srcs/error.c srcs/processing.c \
			srcs/reading.c srcs/sha224256_helper.c srcs/sha384512_helper.c \
			srcs/uint64ops.c srcs/main.c

OBJS	:=	$(SRCS:.c=.o)

all:		$(NAME)

$(NAME):	$(LIB) $(OBJS)
	@$(CC) $(FLAG) $(OBJS) -L libft/ -lft -I libft -o $(NAME)
	@echo "\033[92mDONE\033[0m"
$(LIB):
	@make -C libft/

$(OBJS):	%.o: %.c
	clang $(FLAG) -I $(HEAD) -c $< -o $@

clean:
	@make -C libft clean
	@rm -f $(OBJS)
	@echo "\033[92mObject files have been deleted\033[0m"

fclean: clean
	@make -C libft fclean
	@rm -f $(NAME)
	@echo "\033[92mExecutables have been deleted\033[0m"

re: fclean all

.PHONY:all clean fclean re
