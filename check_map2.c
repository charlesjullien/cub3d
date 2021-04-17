#include "cub3D.h"

int	get_j(char **mat, int l)
{
	int j;

	j = ft_strlen(mat[l]) - 1;
	while (ft_strrchr("1 ", mat[l][j]))
		j--;
	j++;
	return (j);
}

int	verif(char c)
{
	if (c == 'N' || c == 'S' || c == 'W' || c == 'E' || c == '0' || c == '2')
		return (0);
	return (1);
}

int	check_last_line(char **mat, int l, int i, int seg)
{
	while (mat[l][i])
	{
		while (mat[l][i] != '1' && mat[l][i])
			i++;
		if (i == ft_strlen(mat[l]))
			return (1);
		seg = i;
		while (mat[l][seg] == '1')
			seg++;
		while (mat[l - 1][i] != '1' && i < seg && mat[l - 1][i])
			i++;
		if (i == seg)
			return (0);
		while (mat[l][i] == '1')
			i++;
	}
	return (1);
}

int	check_above(char **mat, int l, int i, int l_orig)
{
	int seg;

	while (l > 0)
	{
		while (mat[l][i])
		{
			seg = i;
			while (mat[l][seg] == '1' && mat[l][i])
				seg++;
			if (i != 0)
				i--;
			while (mat[l][i] == '1' && mat[l][i] && i > 0)
				i--;
			if (i != 0)
				i++;
			while (mat[l - 1][i] != '1' && i < seg && mat[l - 1][i])
				i++;
			if (i == seg)
				return (0);
			else
				return (1);
			i = seg;
            while (mat[l][i] != '1' && mat[l][i])
            	i++;
		}
		l--;
	}
	return (1);
}

int    check_first_out_walls(char **mat, int i, int l, int size)
{
    int    seg;
    while (l < (size - 1))
    {
		i = 0;
		while (mat[l][i] != '1')
			i++;
        while (mat[l][i])
        {
            seg = i;
            while (mat[l][seg] == '1')
                seg++;
            while (mat[l + 1][i] != '1' && i < seg && mat[l + 1][i])
                i++;
            if (((i == seg && l == 0) || (i == seg && check_above(mat, l, i, l) == 0)) && verif(mat[l][i]))
                return (0);
            i = seg;
            while (mat[l][i] && mat[l][i] != '1')
                i++;
        }
        l++;
    }
    return (check_last_line(mat, l, 0, 0));
}
