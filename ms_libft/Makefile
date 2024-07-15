# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: njeanbou <njeanbou@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2023/10/30 16:19:31 by njeanbou          #+#    #+#              #
#    Updated: 2024/06/19 16:39:58 by njeanbou         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

SRCS 				= $(wildcard *.c)

OBJS 				= $(SRCS:.c=.o)

NAME 				= libft.a
CC 					= gcc
CFLAGS 				= -Wall -Wextra -Werror
LIBC 				= ar rcs
RM 					= rm -f

GREEN   = \e[92;118m
YELLOW  = \e[93;226m
RESET   = \e[0m
CURSIVE = \e[33;3m

.c.o: 
					@${CC} ${CFLAGS} -c $< -o ${<:.c=.o}

${NAME}:			${OBJS}
					@printf "$(CURSIVE)- Compiling $(NAME)...$(RESET)\n"
					@${LIBC} ${NAME} ${OBJS}
					@printf "$(GREEN)- Executable $(NAME) ready.$(RESET)\n"

all: 				@${NAME}

clean:				
					@${RM} ${OBJS} ${OBJSB}
					@printf "$(YELLOW)- Object $(NAME) removed.$(RESET)\n"

fclean:				clean
					@${RM} ${NAME} ${bonus}
					@printf "$(YELLOW)- Executable $(NAME) removed.$(RESET)\n"

re:					fclean all

.PHONY : all clean fclean re

