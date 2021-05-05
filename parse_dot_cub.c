#include <stdio.h>
#include "cub3D.h"

void	get_colors(t_cub *cub, int *tab)
{
	int i;
	int j;

	i = 0;
	j = 0;
	while (ft_isalpha(cub->line[i]))
		i++;
	if (cub->line[i] == ' ')
		i++;
	while (j < 3)
	{
		tab[j] = ft_atoi(&cub->line[i]);
		while (ft_isdigit(cub->line[i]))
			i++;
		if (cub->line[i] == ',' && j != 2)
			i++;
		else if (j == 2)
		{
			while(cub->line[i] == ' ')
				i++;
			if (cub->line[i] != '\0')
				ft_stop(EXIT_FAILURE, cub, "get colors : Elements organized in a wrong way in .cub");
		}
		j++;
	}
}

void	get_texture(t_cub *cub, char **str)//**str = pointeur sur la bonne chaine dans la struct.
{
	int i;

	i = 0;
	while (ft_isalpha(cub->line[i]))
		i++;
	*str = ft_strdup(&cub->line[i + 1]);// *str car pointeur
	if (i > 2 || i == 0 || !*str)
		ft_stop(EXIT_FAILURE, cub, "get texture : Elements organized in a wrong way in .cub");
}

void	get_resolution(t_cub *cub)
{
	int i;

	i = 0;
	if (cub->line[i] == 'R')
		i++;
	while (cub->line[i] == ' ')
		i++;
	cub->res_x = ft_atoi(&cub->line[i]);
	while (ft_isdigit(cub->line[i]))
		i++;
	while (cub->line[i] == ' ')
		i++;
	cub->res_y = ft_atoi(&cub->line[i]);
	while (ft_isdigit(cub->line[i]))
		i++;
	while(cub->line[i] == ' ')
		i++;
	if (cub->line[i] != '\0' || cub->line[0] != 'R')
		ft_stop(EXIT_FAILURE, cub, "get resolution : Elements organized in a wrong way in .cub");
}

void	get_elements(t_cub *cub)
{
	if (ft_strnstr(cub->line, "R ", 2) && cub->res_x == -1 && cub->res_y == -1)
		get_resolution(cub);
	else if (ft_strnstr(cub->line, "NO", 2) && !cub->north)
		get_texture(cub, &cub->north);// on met bien un & car on veut recup un pointeur
	else if (ft_strnstr(cub->line, "SO", 2) && !cub->south)
		get_texture(cub, &cub->south);
	else if (ft_strnstr(cub->line, "WE", 2) && !cub->west)
		get_texture(cub, &cub->west);
	else if (ft_strnstr(cub->line, "EA", 2) && !cub->east)
		get_texture(cub, &cub->east);
	else if (ft_strnstr(cub->line, "S ", 2) && !cub->sprite)
		get_texture(cub, &cub->sprite);
	else if (ft_strnstr(cub->line, "F ", 2) && cub->floor[0] == -1)
		get_colors(cub, cub->floor);
	else if (ft_strnstr(cub->line, "C ", 2) && cub->ceiling[0] == -1)
		get_colors(cub, cub->ceiling);
	else
		ft_stop(EXIT_FAILURE, cub, "Elements organized in a wrong way in .cub");//at line x...
}

int	parse_dot_cub(char *map, t_cub *cub)
{
	int j;
	int elements;

	elements = 0;
	j = 0;
	fill_from_dot_cub(cub, map);
	while (elements < 8)
	{
		if (mini_gnl(&cub->dot_cub[j], cub, &j) ==  0 && elements < 8)
			ft_stop(EXIT_FAILURE, cub, "Elements organized in a wrong way in .cub");//at line x...petit doute sur si c'est bien là qu'il faut mettre ce if de check l du dessus.
		printf("elements = %d et line = %s\n", elements, cub->line);
		if (cub->line)
		{
			get_elements(cub);
			elements++;
		}
	}
	printf(".cub a partir de [j] = :\n%s", &cub->dot_cub[j]);
	if (!check_map(cub, &cub->dot_cub[j]))
		return (0);
	display_description(cub);
	get_start_infos(cub, &cub->dot_cub[j]);
	return (1);
}
