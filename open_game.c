#include "cub3D.h"

void	define_window_size(t_data *data, t_cub *cub)
{
	data->res_x2 = cub->res_x;
	data->res_y2 = cub->res_y;
	mlx_get_screen_size(data->mlx, &cub->res_x, &cub->res_y);
	if (cub->res_x > data->res_x2)
		cub->res_x = data->res_x2;
	if (cub->res_y > data->res_y2)
		cub->res_y = data->res_y2;
	data->res_x2 = cub->res_x;
	data->res_y2 = cub->res_y;
}

void	define_position_we(t_cub *cub, t_data *data, t_ray *ray)
{
	if (cub->sp_dir == 'W')
	{
		ray->sp_dirx = 0;
		ray->sp_diry = -1;
		ray->sp_plax = -0.66;
		ray->sp_play = 0;
	}
	else if (cub->sp_dir == 'E')
	{
		ray->sp_dirx = 0;
		ray->sp_diry = 1;
		ray->sp_plax = 0.66;
		ray->sp_play = 0;
	}
}

void	define_position_ns(t_cub *cub, t_data *data, t_ray *ray)
{
	if (cub->sp_dir == 'N')
	{
		ray->sp_dirx = -1;
		ray->sp_diry = 0;
		ray->sp_plax = 0;
		ray->sp_play = 0.66;
	}
	else if (cub->sp_dir = 'S')
	{
		data->right = 65361;
		data->left = 65363;
		data->right_dir = 97;
		data->left_dir = 100;
		ray->sp_dirx = 1;
		ray->sp_diry = 0;
		ray->sp_plax = 0;
		ray->sp_play = 0.66;
	}
	else
		define_position_we(cub, &data, &ray);
}

void	init_move_and_pos(t_cub *cub, t_data *data, t_ray *ray)
{
	ray->sp_posx = cub->spawn[0] + 0.5;
	ray->sp_posy = cub->spawn[1] + 0.5;
	data->left = 65361;
	data->right = 65363;
	data->left_dir = 97;
	data->right_dir = 100;
	data->go_up = 0;
	data->go_down = 0;
	data->go_right = 0;
	data->go_left = 0;
	data->rot_left = 0;
	data->rot_right = 0;
}

void	open_game(t_cub *cub)
{
	t_data	data;
	t_ray	ray;
	
	//data.ray = &ray; (mettre un ptr sur la struct ray dans data ?)
	data.mlx = mlx_init();
	define_window_size(&data, cub);
	data.win = mlx_new_window(data.mlx, cub->res_x, cub->res_y, "Cub3D");
	data.img = mlx_new_image(data.mlx, cub->res_x, cub->res_y);
	data.addr = mlx_get_data_addr(data.img, &data.bpp, &data.sline, &data.endian);
	//charger textures ici ou après ca va ?
	init_move_and_pos(cub, &data, &ray);
	define_position_ns(cub, &data, &ray);
	get_texture(cub, &data, &ray);
	raycaster(cub, &data, &ray);	
}
