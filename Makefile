# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: ogregoir <marvin@42.fr>                    +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2023/06/29 14:53:43 by ogregoir          #+#    #+#              #
#    Updated: 2023/06/29 14:53:51 by ogregoir         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

SRCS	= 

OBJS	=	$(SRCS:.c=.o)

NAME	=	minishell

RM		=	rm -f

CC		=	gcc

CFLAGS	=	-Wall -Werror -Wextra

LIBFT	=	utils/libft/libft.a

#----------------------------------------#

all		:	$(NAME)

$(NAME)	: $(LIBFT) $(OBJS)
	$(CC) $(CFLAGS) $(LIBFT) $(OBJS) -o $(NAME)

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