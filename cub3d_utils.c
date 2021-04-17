#include "cub3D.h"

int	ft_error(char *str)
{
	printf("%s", str);
	return (1);
}

void	fill_from_dot_cub(t_cub *cub, char *map)
{
	int rd;
	int i;
	int buf;

	rd = 1;
	i = 0;
	buf = 1;
	cub->fd = open(map, O_RDONLY);
	while (rd == 1)
	{
		rd = read(cub->fd, (char *)&buf, 1);
		cub->dot_cub[i] = buf;
		i++;
	}
	cub->dot_cub[i] = '\0';
	printf("***************\n\n\n%s\n\n\n*****************", cub->dot_cub);
}

int	mini_gnl(char *map, t_cub *cub, int *j)
{
	int i;
	int	i_copy;

	i = 0;
	while (map[i] != '\n' && map[i])
		i++;
	free(cub->line);
	cub->line = malloc(sizeof(char) * (i + 1));
	if (!cub->line)
		return (0);
	i_copy = i;
	i = 0;
	while(i < i_copy && map[i] && map[i] != '\n')
	{
		cub->line[i] = map[i];
		i++;
	}
	cub->line[i] = '\0';
	while(map[i] == '\n' && map[i])
		i++;
	*j = *j + i;
	if (map[i] == '\0' || map[i + 1] == '\0')
		return (0);
	return (1);
}

void	display_description(t_cub *cub)
{
	printf("********* Start of descrption display *********\n");
	printf("Resolution X = %d\n", cub->res_x);
	printf("Resolution Y = %d\n\n", cub->res_y);
	printf("North path = %s\n", cub->north);
	printf("South path = %s\n", cub->south);
	printf("West path = %s\n", cub->west);
	printf("East path = %s\n\n", cub->east);
	printf("Sprite path = %s\n\n", cub->sprite);
	printf("Floor parameters = %d, %d, %d\n", cub->floor[0], cub->floor[1], cub->floor[2]);
	printf("Ceiling parameters = %d, %d, %d\n", cub->ceiling[0], cub->ceiling[1], cub->ceiling[2]);
	printf("********* End of descrption display *********\n");
}
