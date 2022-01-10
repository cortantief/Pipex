# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: sharboul <sharboul@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2022/01/04 12:51:05 by sharboul          #+#    #+#              #
#    Updated: 2022/01/10 15:34:23 by sharboul         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

#HEADER=-Wall -Wextra -Werror
NAME=pipex
FILE=main.c utils/err.c

all: ${NAME}

${NAME}:
	gcc -o ${NAME} ${HEADER} -I . ${FILE}
clean:
	rm -rf build/${NAME}

fclean: clean
