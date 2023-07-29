SRCS = main.c init.c utils.c more_utils.c gnl/get_next_line.c gnl/get_next_line_utils.c \
		file_control.c init_texture.c fill_map.c check_map.c int_map_create.c calc_frame.c \
		move.c free.c
OBJS = $(SRCS:.c=.o)
CC = gcc
MFLAGS = ./mlxlib/libmlx.a
LFLAGS = ./libft/libft.a
AFLAGS =  -Wall -Wextra -Werror -I./mlxlib -I./libft
RM = rm -rf
NAME = cub3d

all :$(MFLAGS) $(LFLAGS) $(NAME)

$(MFLAGS):
	make -C ./mlxlib

$(LFLAGS):
	make -C ./libft

$(NAME): $(OBJS)
	$(CC) $(OBJS) $(MFLAGS) $(LFLAGS) $(AFLAGS) -framework OpenGL -framework AppKit -o $(NAME)

fclean : clean
	make fclean -C ./libft
	$(RM) $(NAME)

clean :
	make clean -C ./mlxlib
	make clean -C ./libft
	$(RM) ./*.o ./gnl/*.o

re : fclean all

.PHONY : all fclean clean re
