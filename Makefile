# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: rgreiner <rgreiner@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2023/06/29 14:53:43 by ogregoir          #+#    #+#              #
#    Updated: 2023/11/16 17:18:00 by rgreiner         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

SRCS	=	main.c \
			Builtins/builtins.c \
			Builtins/builtins2.c \
			Builtins/builtins3.c \
			Builtins/cd.c \
			Builtins/export.c \
			Builtins/save_var.c \
			Exec/builtins_exec.c \
			Exec/exec.c \
			Exec/exec_main.c \
			Exec/exec_utils.c \
			Exec/here_doc.c \
			Exec/here_doc_utils.c \
			Exec/pipe.c \
			Exec/pipe2.c \
			Exec/pipe3.c \
			Exec/redi_child.c \
			Lexer/init_token.c \
			Lexer/lexer.c \
			Lexer/lexer2.c \
			Lexer/lexerquotes.c \
			utils/builtins_utils.c \
			utils/dollar_utils.c \
			utils/dollar_lexer.c \
			utils/free.c \
			utils/utils.c \
			utils/utils2.c \
			utils/utils3.c \
			utils/utils4.c \
			controles.c \
			quotes.c \
			utils.c \

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