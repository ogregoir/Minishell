# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: ogregoir <ogregoir@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2023/06/29 14:53:43 by ogregoir          #+#    #+#              #
#    Updated: 2023/07/01 14:42:35 by ogregoir         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

SRCS	=	main.c \
			utils.c \
			builtins.c \
			variables_environnement.c \

OBJS	=	$(SRCS:.c=.o)

NAME	=	minishell

RM		=	rm -f

CC		=	gcc

CFLAGS	=	-Wall -Werror -Wextra

LIBS	=	-lreadline -L/Users/$(USER)/.brew/opt/readline/lib -I/Users/$(USER)/.brew/opt/readline/include

LIBFT	=	utils/libft/libft.a

#----------------------------------------#

all		:	$(NAME)

$(NAME)	: $(LIBFT) $(OBJS)
	$(CC) $(CFLAGS) $(LIBFT) $(OBJS) ${LIBS} -o $(NAME)

clean	:
	$(RM)   $(OBJS)
	make 	clean -C utils/libft

fclean : clean
	$(RM) $(NAME)
	$(RM) $(LIBFT)
	make fclean -C utils/libft

%.o: %.c
	$(CC) $(CFLAGS) -c $< -o $@

$(LIBFT) :
	make -C utils/libft

re	: fclean all