#include <stdio.h>
#include "cub3D.h"

int	parse_dot_cub(char *map, t_cub *cub);

void	free_all(t_cub *cub, int i)
{
	if (cub)
	{
		if (cub->north)
			free(cub->north);
		if (cub->west)
			free(cub->west);
		if (cub->south)
			free(cub->south);
		if (cub->east)
			free(cub->east);
		if (cub->sprite)
			free(cub->sprite);
		if (cub->map)
		{
			while (cub->map[i])
				free(cub->map[i++]);
			free(cub->map);
		}
		if (cub->line)
			free(cub->line);
		if (cub->cub_file)
			free(cub->cub_file);
	}
}

void	ft_stop(int status, t_cub *cub, char *msg)
{
	free_all(cub, 0);
	if (status)
		printf("%s\n", msg);
	else
		printf("-----> The game stopped properly. <-----\n");
	exit(status);
}

t_cub	*cub_init(void)
{
	t_cub *cub;

	cub = (t_cub*)malloc(sizeof(t_cub));
	if (cub == NULL)
		return (NULL);
	cub->north = NULL;
	cub->south = NULL;
	cub->east = NULL;
	cub->west = NULL;
	cub->sprite = NULL;
	cub->fd = 0;
	cub->res_x = -1;
	cub->res_y = -1;
	cub->floor[0] = -1;
	cub->ceiling[0] = -1;
	cub->line = NULL;
	cub->cub_file = NULL;
	cub->map = NULL;
	return (cub);
}

int main(int argc, char **argv)
{
	t_cub *cub;

	if (argc != 2)
		ft_stop(EXIT_FAILURE, NULL, "Invalid number of arguments");
	cub = cub_init();
	if (cub == NULL)
		ft_stop(EXIT_FAILURE, cub, "Erreur d'allocation memoire dans la struct t_cub");
	if(!parse_dot_cub(argv[1], cub))
		ft_stop(EXIT_FAILURE, cub, "Map doesn't respect mapping rules");
	return (0);
}
