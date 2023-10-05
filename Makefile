# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: rgreiner <rgreiner@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2023/06/29 14:53:43 by ogregoir          #+#    #+#              #
#    Updated: 2023/10/05 13:47:32 by rgreiner         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

SRCS	=	main.c \
			utils.c \
			utils2.c \
			builtins.c \
			builtins2.c \
			lexer.c \
			lexer_2.c \
			lexerquotes.c \
			variables_environnement.c \
			exec.c \
			quotes.c \
			controles.c \
			dollar.c \
			cd.c \
			pipe.c \
			pipe2.c \
			error_cd.c \
			init_token.c \
			
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