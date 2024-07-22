# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: aafounas <aafounas@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2024/07/15 19:09:13 by aafounas          #+#    #+#              #
#    Updated: 2024/07/17 15:52:56 by aafounas         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME	=	pipex
SRCS	=	src/pipex.c src/pipex.utils.c
OBJS	=	${SRCS:.c=.o}

CC		=	cc
CFLAGS	=	-g3 -Wall -Werror -Wextra
RM		=	rm -f

LIBFT_DIR	=	./Libft
LIBFT	=	${LIBFT_DIR}/libft.a
INCLUDE	=	-Iincludes

all:	${NAME}

${NAME}:	${OBJS} ${LIBFT}
	@echo "\033[33m----Compiling ${NAME}----"
	${CC} ${CFLAGS} ${OBJS} ${LIBFT} -o ${NAME}
	@echo "\033[32m${NAME} Compiled!\033[0m"

${LIBFT}:
	@echo "\033[33m----Compiling libft----"
	make -C ${LIBFT_DIR}
	@echo "\033[32mlibft Compiled!\033[0m"

clean:
	@echo "\033[31m----Cleaning object files----\033[0m"
	make -C ${LIBFT_DIR} clean
	${RM} ${OBJS}

fclean: clean
	@echo "\033[31m----Cleaning all generated files----\033[0m"
	make -C ${LIBFT_DIR} fclean
	${RM} ${NAME}

re: fclean all

.PHONY: all clean fclean re
