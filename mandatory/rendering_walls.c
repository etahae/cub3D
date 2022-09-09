#include "../includes/header.h"


void return_y(t_player *p)
{
    int x;
    int y;

    p->wall.distance_project_plane = (WINDOW_WIDTH / 2) / tan(p->fov_angle / 2);
    p->wall.wall_strip_height = (TILE_SIZE / p->distance[p->wall.i]) * p->wall.distance_project_plane; // calc wall height in screen
    if (p->wall.x % p->wall.wall_strip_width == 0  && p->wall.x != 0)
        p->wall.i++;
    p->wall.wall_top_px = (int)(WINDOW_HEIGHT / 2 - p->wall.wall_strip_height / 2);   // calc start of wall_strip_height start
    p->wall.wall_top_px = p->wall.wall_top_px < 0 ? 0 : p->wall.wall_top_px;// if is negative assagne it the top of screen    
    p->wall.wall_bottom_px =   (WINDOW_HEIGHT / 2 + p->wall.wall_strip_height / 2); 
    p->wall.wall_bottom_px = p->wall.wall_bottom_px  > WINDOW_HEIGHT ? WINDOW_HEIGHT : p->wall.wall_bottom_px;// protection
     
    // here we calc the start and the end of wall_strip_height (wall on the screen)
    // return p->wall.wall_top_px;
}

static int init_rend(t_player *p)
{
    int x;
    int y;
    int x2;
    int y2; 

    p->wall.wall_strip_width = WINDOW_WIDTH / p->num_of_rays;

    p->mlx.img = mlx_new_image(p->mlx.mlx, WINDOW_WIDTH, WINDOW_HEIGHT);
    p->mlx.addr = mlx_get_data_addr(p->mlx.img, &p->mlx.bits_per_pixel, &p->mlx.line_length, &p->mlx.endian);
    
    p->mlx.img_px = mlx_xpm_file_to_image(p->mlx.mlx,"./images/bruh.xpm", &x, &y);
	p->mlx.addr_px = mlx_get_data_addr(p->mlx.img_px, &p->mlx.bpp, &p->mlx.sl, &p->mlx.l);

     
    // p->mlx.img_px_2 = mlx_xpm_file_to_image(p->mlx.mlx,"./mossy.xpm", &x2, &y2);
	// p->mlx.addr_px_2 = mlx_get_data_addr(p->mlx.img_px_2, &p->mlx.bpp2, &p->mlx.sl2, &p->mlx.l2);
    

    p->width = x2;
    p->wall.i = 0;
    p->wall.x = 0;
    return (x);
}

	 


void normalize_(t_player *p)
{
    if (p->rotation_angle >= 2 * PI)
        p->rotation_angle -= 2 * PI; 
    if (p->rotation_angle <= 0)
        p->rotation_angle += 2 * PI;
}
void rendering_walls(t_player *p)
{
    int     y;
    int     width;
    int     x_offset;
    int     y_offset;
   
    int     distance_from_top; 

    char	*dst;
    char	*src;
    width = init_rend(p);  
    while (p->wall.x < WINDOW_WIDTH)
    {
        return_y(p);
        y = p->wall.wall_top_px;
        
        normalize_(p);
        while (y <  p->wall.wall_bottom_px)
        { 
            if(p->if_is_vertical[p->wall.i])
                x_offset = (fmod(p->py[p->wall.i], TILE_SIZE)) * (width / TILE_SIZE);
            else
                x_offset = (fmod(p->px[p->wall.i], TILE_SIZE)) * (width / TILE_SIZE);
                
            distance_from_top = (y + (p->wall.wall_strip_height / 2) - (WINDOW_HEIGHT / 2));
            y_offset = distance_from_top * ( (width / p->wall.wall_strip_height)); // height instead od width
            dst = p->mlx.addr + (y * p->mlx.line_length + p->wall.x * (p->mlx.bits_per_pixel / 8));
            src = p->mlx.addr_px + (y_offset * p->mlx.sl + x_offset * (p->mlx.bpp / 8));
            *(int*)dst =  *(int*)src; 
            y++;
        }
        draw_floor_roof(p);
        p->wall.x++;
    }
    mlx_put_image_to_window(p->mlx.mlx, p->mlx.mlx_win, p->mlx.img, 0, 0);

}

 
            // if(!p->if_is_vertical[p->wall.i])
            //     x_offset = fmod(p->px[p->wall.i] , TILE_SIZE) *( p->mlx.sl / TILE_SIZE);
            // else
            //     x_offset = fmod(p->py[p->wall.i] , TILE_SIZE) * (p->mlx.sl / TILE_SIZE);
            
            // y_offset = fmod(p->py[p->wall.i]  , (p->wall.wall_top_px - p->wall.wall_bottom_px)) * (p->mlx.sl / (p->wall.wall_top_px - p->wall.wall_bottom_px));

	        // // dst = data->mlx.addr + (y * data->mlx.line_length + x * (data->mlx.bits_per_pixel / 8));

            // src = p->mlx.addr_px + (y_offset * p->mlx.sl + x_offset * (p->mlx.bpp / 8));
             
            
            // my_mlx_pixel_put(p, p->wall.x , y, *(unsigned int*)src); 