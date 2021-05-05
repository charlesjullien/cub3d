#include "cub3D.h"

int get_big_wall(char **mat, int l, int size)
{
	int i;

	i = 0;
	if (l == size - 1)
	{
		while (l > 1)
		{
			i = 0;
			while (mat[l][i] && ft_strrchr("1 ", mat[l][i]))
				i++;
			if (i != ft_strlen(mat[l]))
				return (l);
			l--;
		}
	}
	while (l < size)
	{
		i = 0;
		while (mat[l][i] && ft_strrchr("1 ", mat[l][i]))
			i++;
		if (i != ft_strlen(mat[l]))
			return (l);
		l++;
	}
	return (l);
}

int	check_first_big_wall(char **mat, int l, int i, int j)
{
	while (ft_strrchr("1 ", mat[l][i]))
		i++;
	j = ft_strlen(mat[l]) - 1;
	while (ft_strrchr("1 ", mat[l][j]))
		j--;
	if (mat[l][j + 1])
		j++;
	if ((i > 0 && mat[l][i - 1] != '1') || mat[l][j] != '1')
		return (0);
	while (ft_strrchr("NSWE021 ", mat[l][i]) && mat[l][i])
	{
		if (ft_strrchr("NSWE02", mat[l][i]) && mat[l - 1][i] && mat[l - 1][i] != '1')
			return (0);
		i++;
	}
	i = 0;
	while (ft_strrchr("1 ", mat[l][i]))
		i++;
	l--;
	while (i < j && (mat[l][i] == '1' || mat[l][i] == ' '))
		i++;
	if (i < j)
		return (0);
	return (1);
}

int	check_last_big_wall(char **mat, int l, int i, int j)
{
	while (ft_strrchr("1 ", mat[l][i]))
		i++;
	j = ft_strlen(mat[l]);
	while (ft_strrchr("1 ", mat[l][j]))
		j--;
	if (mat[l][j + 1])
			j++;
	if ((i > 0 && mat[l][i - 1] != '1') || mat[l][j] != '1')
		return (0);
	while (ft_strrchr("NSWE021 ", mat[l][i]) && mat[l][i])
	{
		if (ft_strrchr("NSWE02", mat[l][i]) && mat[l + 1][i] && mat[l + 1][i] != '1')
			return (0);
		i++;
	}
	i = 0;
	while (ft_strrchr("1 ", mat[l][i]))
		i++;
	l++;
	while (i < j && (mat[l][i] == '1' || mat[l][i] == ' '))
		i++;
	if (i < j)
		return (0);
	return (1);
}


int	checker(char **mat, int size, int i)
{
	int l;

	l = get_big_wall(mat, 0, size);
	if (!check_first_out_walls(mat, 0, 0, size))
		return (0);
	if (!check_first_big_wall(mat, l, 0, 0))
		return (0);
	size = get_big_wall(mat, (size - 1), size) + 1;
	while (l < size)
	{
		i = 0;
		while (ft_strrchr("1 ", mat[l][i]))
			i++;
		if (mat[l][i - 1] && mat[l][i - 1] != '1')
			return (0);
		while (ft_strrchr("1NSWE02", mat[l][i]) && i < get_j(mat, l))
			i++;
		if ((mat[l][i] != '1' || i != get_j(mat, l)) && (l >= get_big_wall(mat, 0, size) && l < size - 1))
			return (0);
		l++;
	}
	if (!check_last_big_wall(mat, (l - 1), 0, 0))
		return (0);
	return (1);
}

int	check_map(t_cub *cub, char *map)
{
	char **mat;
	int i;
	int count;
	int size;

	i = 0;
	count = 0;
	mat = ft_split(map, '\n');
	size = 0;
	while (map[i])
	{
		if (!ft_strrchr("012NSWE \n", map[i]) || (count != 1 && count != 0))
			ft_stop(EXIT_FAILURE, cub, "Map doesn't respect mapping rules");
		if (ft_strrchr("NSWE", map[i]))
			count++;
		i++;
	}
	i = 0;
	while (map[i])
	{
		if (map[i] == '\n')
			size++;
		if (map[i] == '\n' && map[i + 1] == '\n')
			break ;
		i++;
	}
	if (!checker(mat, size, 0))
		ft_stop(EXIT_FAILURE, cub, "Map doesn't respect mapping rules");
	else
		printf("YESSSSSSSSSSSSSSSSSSSSSSSSS\n");
	return (1);
}
