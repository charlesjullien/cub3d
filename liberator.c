#include "cub3D.h"

void	free_textures(t_data *data, t_data *tex)
{
	int i;

	i = 0;
	while (i < 8)
	{
		mlx_destroy_image(data->mlx, tex[i].img);
		i++;
	}
	mlx_destroy_image(data->mlx, data->img);
	mlx_clear_window(data->mlx, data->win);
	mlx_destroy_window(data->mlx, data->win);
	mlx_destroy_display(data->mlx);
	free(data->mlx);
	fata->mlx = NULL;
	ft_stop(EXIT_FAILURE, data->cub, "Impossible to get textures.\n");
}
