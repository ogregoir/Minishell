# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: marvin <marvin@student.42.fr>              +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2023/06/29 14:53:43 by ogregoir          #+#    #+#              #
#    Updated: 2023/10/24 00:45:44 by marvin           ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

SRCS	=	main.c \
			utils/utils.c \
			utils/utils2.c \
			Builtins/builtins.c \
			Builtins/builtins2.c \
			utils/builtins_utils.c \
			Exec/builtins_exec.c \
			Lexer/lexer.c \
			Lexer/lexer_2.c \
			Lexer/lexerquotes.c \
			Exec/exec.c \
			quotes.c \
			controles.c \
			dollar.c \
			Builtins/cd.c \
			Exec/pipe.c \
			Exec/pipe2.c \
			Exec/here_doc.c \
			utils/error_cd.c \
			Lexer/init_token.c \
			Builtins/export.c \
			Builtins/export2.c \
			
OBJS	=	$(SRCS:.c=.o)

NAME	=	minishell

RM		=	rm -f

CC		=	gcc

CFLAGS	=	-Wall -Werror -Wextra

LIBS	=	-lreadline -L/Users/$(USER)/.brew/opt/readline/lib -I/Users/$(USER)/.brew/opt/readline/include

LIBFT	=	utils/libft/libft.a

#----------------------------------------#

all		:	$(NAME)

$(NAME)	:  $(LIBFT) $(OBJS) 
	$(CC) $(CFLAGS) $(OBJS) $(LIBFT) ${LIBS} -o $(NAME) 

%.o: %.c
	$(CC) $(CFLAGS) -c $< -o $@

clean :
	$(RM)   $(OBJS)
	make	clean -C utils/libft

fclean : clean
	$(RM) $(NAME)
	$(RM) $(LIBFT)
	make fclean -C utils/libft

$(LIBFT) :
	make -C utils/libft

re	: fclean all