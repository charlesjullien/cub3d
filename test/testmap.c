#include <stdio.h>

int	ft_strlen(const char *str)
{
	int i;

	i = 0;
	while (str[i])
	{
		i++;
	}
	return (i);
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
		{
			printf("la fin ? i = %d, l = %d\n", i, l);
			return (0);
		}
		while (mat[l][i] == '1')
			i++;
	}
	return (1);
}

int	check_above(char **mat, int l, int i, int l_orig)//plutot que de faire un while pour checker touuuuut avant, plutot faire un seul if qui va verifier la ligne du dessus if l > 0. 
{
	printf("l = %d et i = %d\n\n", l, i);
	int seg;

	while (l > 0)
	{
		//if (l != l_orig)
		//	i = get_first_wall(mat, l, 0);
		while (mat[l][i])
		{
			seg = i;
			while (mat[l][seg] == '1' && mat[l][i])
				seg++;
			if (i != 0)
				i--;
			printf("i = %d, seg = %d, l = %d\n\n", i, seg, l);
			while (mat[l][i] == '1' && mat[l][i] && i > 0)
				i--;
			if (i != 0)
				i++;
			while (mat[l - 1][i] != '1' && i < seg && mat[l - 1][i])
				i++;
			if (i == seg)
			{
				printf("ici avec l à %d i à %d et seg à %d?????????????????\n", l, i - 1, seg - 1);
				return (0);
			}
			else
				return (1);
			i = seg;
            while (mat[l][i] != '1' && mat[l][i])
            	i++;
		}
		l--;
	}
	//printf("seg = %d, i = %d, l = %d\n\n", seg, i, (l - 1));
	return (1);
}

int    check_first_out_walls(char **mat, int i, int l)//l doit etre > 0 !
{
    int    seg;

    while (l < 12)
    {
		i = 0;
		while (mat[l][i] != '1')
			i++;
        while (mat[l][i])
        {
            seg = i;
            while (mat[l][seg] == '1')
                seg++;
            while (mat[l + 1][i] != '1' && i < seg && mat[l + 1][i])//à verifier...ouai C LA JCROIS !
                i++;
            if ((i == seg && l == 0) || (i == seg && check_above(mat, l, i, l) == 0))
			{
				//printf("l = %d, i = %d, seg = %d\n\n", l, i, seg);
                return (0);
			}
            i = seg;
            while (mat[l][i] != '1' && mat[l][i])
                i++;
        }
        l++;
    }
    return (check_last_line(mat, l, 0, 0));
}

int main()
{
    char *mat[13];
    mat[0] = "    111 1      1";
    mat[1] = "  1  111111    1";
    mat[2] = "  1  1    111  1";
    mat[3] = " 11 11 1  1  111";
    mat[4] = "11  1  1 1     1";
    mat[5] = " 111111111111111";
	mat[6] = "    1N00000001  ";
	mat[7] = "  111000200001  ";
	mat[8] = "    1200000001  ";
    mat[9] = " 111111111111111";
	mat[10] = "1  1 1     1    ";
	mat[11] = "1  1 1    1111 1";
	mat[12] = "1 11 1  111 1111";
    printf("le resultat est : %d\n", check_first_out_walls(mat, 4, 0));
    return (0);
}
