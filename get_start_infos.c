#include "cub3D.h"

void	get_sprites(t_cub *cub, int i, int j, int *sp_count)
{
	if (*sp_count == 199)
		return ;
	cub->spr_pos[*sp_count] = i;//ligne, soit x
	*sp_count = *sp_count + 1;
	cub->spr_pos[*sp_count] = j;//colonne, soit y
	*sp_count = *sp_count + 1;
}

void	get_spawn_pos(t_cub *cub)
{
	int i;
	int j;
	int	sp_count;

	i = 0;
	sp_count = 0;
	while (cub->map[i])
	{
		j = 0;
		while (cub->map[i][j])
		{
			if (cub->map[i][j] == '2')
				get_sprites(cub, i, j, &sp_count);
			if (ft_strchr("NSWE", cub->map[i][j]))
			{
				cub->spawn[0] = i;//ligne, soit x
				cub->spawn[1] = j;//colonne, soit y
			}
			j++;
		}
		i++;
	}
}

int		get_start_infos(t_cub *cub, char *map_in_1_D)
{
	cub->map = ft_split(map_in_1_D, '\n');
	get_spawn_pos(cub);
	int i = 0;
	while (i < 4)
	{
		printf("sprite pos x = %d et y = %d\n", cub->spr_pos[i], cub->spr_pos[i + 1]);
		i = i + 2;
	}
	printf("\nspawn pos x = %d et y = %d\n\n", cub->spawn[0], cub->spawn[1]);
	i = 0;
	while (cub->map[i])
	{
		printf("%s\n", cub->map[i]);
		i++;
	}
	//open_game(cub);
}
