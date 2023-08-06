# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: skulkamt <skulkamt@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2023/08/06 10:59:15 by skulkamt          #+#    #+#              #
#    Updated: 2023/08/06 10:59:17 by skulkamt         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

SOURCES 		= server.c client.c
DIR_LIBFT 		= ./lib/libft/
LIB_LIBFT 		= ./lib/libft/libft.a

CC = gcc
CFLAGS = -Wall -Wextra -Werror

all: server client
bonus: server_bonus client_bonus

%: %.c ${LIB_LIBFT}
	$(CC) $< $(LIB_LIBFT) -o $@

${LIB_LIBFT}:${DIR_LIBFT} 
	@echo
	make -C ${DIR_LIBFT}

$(DIR_LIBFT):
	@git clone https://github.com/yellowcursus42/libft ${DIR_LIBFT}

clean:
	make -C ${DIR_LIBFT} clean
	
fclean: clean
	rm -f server client
	make -C ${DIR_LIBFT} fclean

re: fclean all

.PHONY: all bonus libft clean fclean re
