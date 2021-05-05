#ifndef CUB3D_H
# define CUB3D_H
# include <unistd.h>
# include <fcntl.h>
# include <stdlib.h>
# include <string.h>
# include <errno.h>
# include <stdio.h>
# include <math.h>
# include "Libft/libft.h"

typedef struct s_cub	t_cub;
struct			s_cub
{
	char	*north;
	char	*south;
	char	*east;
	char	*west;
	char	*sprite;
	int		fd;
	int		res_x;
	int 	res_y;
	int		floor[3];
	int		ceiling[3];
	char	dot_cub[19000];
	char 	**map;
	char	*line;
	char	*cub_file;
	int		spr_pos[200];
	int		spawn[2];
};

/*typedef struct s_	t_;
struct			s_
{

};*/

int	mini_gnl(char *map, t_cub *cub, int *j);
void fill_from_dot_cub(t_cub *cub, char *map);
void	display_description(t_cub *cub);
int	check_map(t_cub *cub, char *map);
int    check_first_out_walls(char **mat, int i, int l, int size);
int	get_j(char **mat, int l);
int		get_start_infos(t_cub *cub, char *map_in_1_D);
void	ft_stop(int status, t_cub *cub, char *msg);
void	free_all(t_cub *cub, int i);


#endif
