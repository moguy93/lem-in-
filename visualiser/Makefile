# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: gedemais <marvin@42.fr>                    +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2019/05/20 18:40:16 by gedemais          #+#    #+#              #
#    Updated: 2019/09/04 07:37:52 by gedemais         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

CC = gcc

CFLAGS = -Wall -Werror -Wextra -Weveryhting

OFLAGS = -O3 -Ofast -march=native

INC = includes/fractol.h

SRCS_NAME = cross_ant.c\
		draw_circle.c\
		deal_key.c\
		load_line.c\
		main.c\
		make_graph.c\
		mlx_fts_1.c\
		pipes.c\
		read_fd_zero.c\
		render.c\
		states.c\
		count.c\
		utils.c

SRCS_PATH = srcs/

SRCS = $(addprefix $(SRCS_PATH), $(SRCS_NAME))

OBJS = $(SRCS_NAME:.c=.o)

MLX_PATH = minilibx_macos/

MLX = minilibx_macos/libmlx.a

MLX_OBJS_NAME = mlx_init_loop.o\
				mlx_int_str_to_wordtab.o\
				mlx_new_image.o\
				mlx_new_window.o\
				mlx_shaders.o\
				mlx_xpm.o

MLX_OBJS = $(addprefix $(MLX_PATH), $(MLX_OBJS_NAME))

LIB_PATH = ../libft/

LIB = ../libft/libft.a

INC = includes/main.h

NAME = lem_in_visualiser

all : $(MLX_PATH) $(LIB) $(NAME) $(INC)

$(NAME) : $(MLX) $(INC) $(LIB_PATH) $(SRCS)
	@echo "Making $(RED)Visualiser$(DEF)"
	@$(CC) $(FLAGS) $(OFLAGS) -o $(NAME) -I minilibx_macos/ $(SRCS) -L minilibx_macos/ minilibx_macos/libmlx.a -framework OpenGL -framework OpenCL -framework AppKit -lpthread $(LIB)
	@echo "$(GRE)Done !$(DEF)"

$(LIB) :
	@echo "Making $(SOU)Libft$(DEF) :"
	@make -C $(LIB_PATH)

$(MLX) : $(MLX_PATH)
	@echo "Making $(SOU)MinilibX$(DEF) :"
	@make -C $(MLX_PATH)

clean:
	@rm -rf $(OBJS)
	@rm -rf $(MLX_OBJS)
	@make -C $(LIB_PATH) clean

fclean: clean
	@rm -rf $(NAME)
	@rm -rf $(OBJS)
	@rm -rf $(MLX_PATH)/libmlx.a
	@make -C $(LIB_PATH) fclean

re : fclean all
