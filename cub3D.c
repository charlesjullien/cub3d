#include <stdio.h>
#include "cub3D.h"

int	parse_dot_cub(char *map, t_cub *cub);

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
	return (cub);
}

int main(int argc, char **argv)
{
	t_cub *cub;

	cub = cub_init();
	if (cub == NULL)
		ft_error("Erreur d'allocation memoire dans la struct t_cub");
	if (argc != 2)
		return (ft_error("Invalid number of arguments\n"));
	if(!parse_dot_cub(argv[1], cub))
		return(ft_error("Map doesn't respect mapping rules\n"));
	return (0);
}
