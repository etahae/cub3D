#include "./includes/header.h"



void init_player_attributs(t_player  *p)
{
	p->x = (double)(p->cub_info.player_y * 64);	
	p->y =  (double)(p->cub_info.player_x * 64);	
	p->turn = 0;
	p->walk = 0;
	p->move = 0;
	p->rotation_angle = PI / 2;
	p->walk_speed = 15;
	p->turn_speed = 4 * (PI / 180);// 4 degres
	p->fov_angle = 60 * (PI / 180);
	p->num_of_rays = WINDOW_WIDTH;
} 


 
int main(int argc, char *argv[])
{
	t_player pl;
	t_player  *p = &pl;
 
	p->mlx.mlx = mlx_init();
	p->mlx.mlx_win = mlx_new_window(p->mlx.mlx, WINDOW_WIDTH, WINDOW_HEIGHT, "cub3D");
 	if (argc != 2)
	{
		write(2, "cub3D: Invalid number of arguments", 35);
		return (1);
	}
	name_checker(argv[1]);
	content_checker(argv[1],&p->cub_info);
 	init_player_attributs(p);

	moves_of_player(p);
	mlx_loop(p->mlx.mlx);
	 
 

    return 0;
}