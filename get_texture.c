#include "cub3D.h"

void	stock_texture(t_data *data, t_data *tex, int *tab)
{
	int x;
	int y;

	x = 0;
	while (x < 64)
	{
		y = 0;
		while (y < 64)
		{
			tab[(64 * x) + y] = mlx_pixel_get(tex, x, y);
			y++;
		}
		x++;
	}
	mlx_destroy_image(data->mlx, tex->img);
}

void	get_specific_tex(t_data *data, t_ray *ray, t_data *tex, int i)
{
	
	tex[5].img = mlx_xpm_file_to_image(data->mlx, "./dossiertexture/texture.xpm",
			&tex[5].res_x2, &tex[5].res_y2);
	tex[6].img = mlx_xpm_file_to_image(data->mlx, "./dossiertexture/texture.xpm",
			&tex[6].res_x2, &tex[6].res_y2);
	tex[7].img = mlx_xpm_file_to_image(data->mlx, "./dossiertexture/texture.xpm",
			&tex[7].res_x2, &tex[7].res_y2);
	while (i < 8)
	{
		if (tex[i].img == NULL)
			free_textures(data, tex);
		tex[i].addr = mlx_get_data_address(tex[i].img, &tex[i].bpp,
				&tex[i].sline, &tex[i].endian);
		stock_texture(data, &tex[i], ray->tex[i]);
		i++;
	}
}

void	get_texture(t_cub *cub, t_data *data, t_ray *ray)
{
	int i;
	t_data	tex[8];

	i = 0;
	while (i < 8)
	{
		tex[i].img = NULL;
		i++;
	}
	tex[0].img = mlx_xpm_file_to_image(data->mlx, cub->south,
			&tex[0].res_x2, &tex[0].res_y2);
	tex[1].img = mlx_xpm_file_to_image(data->mlx, cub->north,
			&tex[1].res_x2, &tex[1].res_y2);
	tex[2].img = mlx_xpm_file_to_image(data->mlx, cub->west,
			&tex[2].res_x2, &tex[2].res_y2);
	tex[3].img = mlx_xpm_file_to_image(data->mlx, cub->east,
			&tex[3].res_x2, &tex[3].res_y2);
	tex[4].img = mlx_xpm_file_to_image(data->mlx, cub->sprite,
			&tex[4].res_x2, &tex[4].res_y2);
	get_specific_tex(data, ray, tex, 0);
}
