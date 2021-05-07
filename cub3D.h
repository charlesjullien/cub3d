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
	char	sp_dir;
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

typedef struct s_data	t_data;
struct			s_data
{
	void	*mlx;
	void	*win;
	void	*img;
	char	*addr;
	int		res_x2;
	int		res_y2;
	int		bpp;
	int		sline;//size_line.
	int		endian;
	int		go_up;
	int		go_down;
	int		go_right;
	int		go_left;
	int		right;//de là
	int		left;
	int		rot_left;
	int		rot_right;
	int		left_dir;
	int		right_dir;//à là
};

/*typedef struct s_	t_;
struct			s_
{
	
};*/


typedef struct s_ray	t_ray;
struct			s_ray
{
	double	sp_posx;
	double	sp_posy;
	double	sp_dirx;
	double	sp_diry;
	double	sp_plax;
	double	sp_play;
};

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
