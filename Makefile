# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: seunchoi <marvin@42.fr>                    +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2022/12/16 12:18:03 by seunchoi          #+#    #+#              #
#    Updated: 2022/12/16 12:18:32 by seunchoi         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

CC = cc
CFLAGS = -Wall -Wextra -Werror
NAME = minirt

INCLUDE = -I./includes -I./mlx
LIBS = -L./mlx -lmlx

SRCS = main.c ray.c vec1.c vec2.c image.c camera.c color.c
OBJS = $(SRCS:.c=.o)

.c.o :
	$(CC) $(CFLAGS) $(INCLUDE) -c $< -o $@

$(NAME) : $(OBJS)
	$(MAKE) -C./mlx
	$(CC) $(CFLAGS) $(INCLUDE) -o $(NAME) $(OBJS)

all : $(NAME)

clean :
	rm -f $(OBJS)

fclean : clean
	rm -f $(NAME)

re : fclean all

.PHONY : all clean fclean re