NAME	:=	ft_ssl

CC	:=	clang

FLAG	:=	-Wall -Werror -Wextra

HEAD	:=	./includes

LIB	:=	./libft/libft.a

SRCS	:=	srcs/main.c srcs/md5.c srcs/sha256.c srcs/print.c srcs/error.c

OBJS	:=	$(SRCS:.c=.o)

all:		$(NAME)

$(NAME):	$(LIB) $(OBJS)
	@$(CC) $(FLAG) $(OBJS) -L libft/ -lft -I libft -o $(NAME)
	@echo "\033[92mDONE\033[0m"
$(LIB):
	@make -C libft/

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
