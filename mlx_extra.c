#include "cub3D.h"

void	mlx_pixel_draw(t_data *mlx, int x, int y, int color)
{
	char	*dst;

	dst = data->addr + (y * data->sline + x * (data->bpp / 8));
	*(unsigned int*)dst = color;
}

int		mlx_pixel_get(t_data *mlx, int x, int y)//ou t_data *tex ?
{
	char	*color;

	color = data->addr + (x * data->sline + y * (data->bpp / 8));
	return (*(unsigned int*)color);
}
