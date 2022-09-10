NAME = cub3D
CC = cc
CFLAGS =
LIBFT = ./libft/libft.a
MLX = ./mlx/libmlx.a
HEADER = ./includes/header.h ./map/map.h ./libft/libft.h ./gnl/get_next_line.h
SRC = main.c \
	./mandatory/moves_of_player.c \
	./mandatory/find_intersections.c \
	./mandatory/horizontal_intersections.c \
	./mandatory/vertical_intersections.c \
	./mandatory/rendering_walls.c \
	./mandatory/walls_texture.c \
	./map/name_checker.c ./map/content_checker.c ./map/map_error.c ./gnl/get_next_line.c ./gnl/get_next_line_utils.c\
	./map/texture_generator.c ./map/utils.c ./map/map.c ./map/valid_textures.c
 
	
OBJ = $(SRC:.c=.o)

all: $(NAME)

$(NAME): $(OBJ) $(LIBFT) $(MLX)
	@$(CC)  $(CFLAGS) -lmlx -framework OpenGL -framework AppKit -lz $(LIBFT) $(MLX)  $^ -o $@

%.o: %.c
	@$(CC) $(CFLAGS) -c $< -o $@
	 
$(LIBFT) :
	@$(MAKE) -C ./libft

$(MLX) :
	@$(MAKE) -C ./mlx

clean :
	@$(MAKE) clean -C ./libft
	@$(MAKE) clean -C ./mlx
	@rm -rf $(OBJ)

fclean : clean
	@$(MAKE) fclean -C ./libft
	@rm -rf $(NAME)

re : fclean all


	