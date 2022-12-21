NAME = cub3D

LIBFT = ../libft/libft.a

MAP = map/content_checker.c map/map.c map/map_error.c map/texture_generator.c map/valid_textures.c map/is_player.c map/name_checker.c map/utils.c 

SRC = main.c raycaster.c mlx_put_pixel.c put_txtr.c hooks.c mouse_hook.c find_hv_point.c shortest_dist.c draw_tools.c fire_anim.c \
		../gnl/get_next_line.c ../gnl/get_next_line_utils.c 

HDR = cub.h map/map.h ../gnl/get_next_line.h

all: $(NAME)

$(NAME): $(SRC) $(LIBFT) $(MAP) $(HDR)
	@echo "\033[1m\033[32mBuilding EXEC FILE...\033[0m"
	@cc -Wall -Werror -Wextra $(SRC) $(LIBFT) $(MAP) -lmlx -framework OpenGL -framework AppKit -o $(NAME)


$(LIBFT): ../libft/libft.h
	@echo "\033[1m\033[32mBuilding LIBFT...\033[0m"
	@make -C ../libft

clean:
	@echo "\033[1m\033[31mCleaning...\033[0m"
	@rm -f $(NAME)
	@make clean -C ../libft

fclean: clean
	@make fclean -C ../libft

re: fclean all
