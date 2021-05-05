# include "libmlx/mlx.h"
# include <unistd.h>
# include <fcntl.h>
# include <stdlib.h>
# include <string.h>
# include <errno.h>
# include <stdio.h>
# include <math.h>

#define mapWidth 24
#define mapHeight 24
#define screenWidth 800
#define screenHeight 800
#define w 800
#define h 800
# define LEFT 65361
# define UP 65362
# define RIGHT 65363
# define DOWN 65364
# define ESCAPE 65307

int worldMap[mapWidth][mapHeight]=
{
  {1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1},
  {1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
  {1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
  {1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
  {1,0,0,0,0,0,2,2,2,2,2,0,0,0,0,3,0,3,0,3,0,0,0,1},
  {1,0,0,0,0,0,2,0,0,0,2,0,0,0,0,0,0,0,0,0,0,0,0,1},
  {1,0,0,0,0,0,2,0,0,0,2,0,0,0,0,3,0,0,0,3,0,0,0,1},
  {1,0,0,0,0,0,2,0,0,0,2,0,0,0,0,0,0,0,0,0,0,0,0,1},
  {1,0,0,0,0,0,2,2,0,2,2,0,0,0,0,3,0,3,0,3,0,0,0,1},
  {1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
  {1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
  {1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
  {1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
  {1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
  {1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
  {1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
  {1,4,4,4,4,4,4,4,4,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
  {1,4,0,4,0,0,0,0,4,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
  {1,4,0,0,0,0,5,0,4,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
  {1,4,0,4,0,0,0,0,4,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
  {1,4,0,4,4,4,4,4,4,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
  {1,4,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
  {1,4,4,4,4,4,4,4,4,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
  {1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1}
};

double posX, posY;  //x and y start position
double dirX, dirY; //initial direction vector
double moveSpeed; //the constant value is in squares/second
double rotSpeed; //the constant value is in radians/second
double planeX, planeY;

typedef struct	s_data {
	void    	*mlx;
	void   		*mlx_win;
	void        *img;
	char        *addr;
	int         bits_per_pixel;
	int         line_length;
	int         endian;
}				t_data;

void            my_mlx_pixel_put(t_data *data, int x, int y, int color)
{
	char    *dst;

	dst = data->addr + (y * data->line_length + x * (data->bits_per_pixel / 8));
	*(unsigned int*)dst = color;
}

int		ver_line(t_data *data, int x, int y1, int y2, int color)
{
	int y;
	if(y2 < y1) {y1 += y2; y2 = y1 - y2; y1 -= y2;} //swap y1 and y2
	if(y2 < 0 || y1 >= h  || x < 0 || x >= w) return 0; //no single point of the line is on screen
	if(y1 < 0) y1 = 0; //clip
	if(y2 >= w) y2 = h - 1; //clip

	for (y = y1; y <= y2; y++)
		my_mlx_pixel_put(data, x, y, color);
	return (1);
}

void	draw(t_data *img)
{
	moveSpeed = 0.5; //the constant value is in squares/second
	rotSpeed = 0.3; //the 2d raycaster version of camera plane
	for(int x = 0; x < w; x++)
	{
		//calculate ray position and direction
		double cameraX = 2 * x / (double)(w) - 1; //x-coordinate in camera space
		double rayDirX = dirX + planeX * cameraX;
		double rayDirY = dirY + planeY * cameraX;
		//which box of the map we're in
		int mapX = (int)(posX);
		int mapY = (int)(posY);

		//length of ray from current position to next x or y-side
		double sideDistX;
		double sideDistY;

		//length of ray from one x or y-side to next x or y-side
		double deltaDistX = (rayDirY == 0) ? 0 : ((rayDirX == 0) ? 1 : fabs(1 / rayDirX));
		double deltaDistY = (rayDirX == 0) ? 0 : ((rayDirY == 0) ? 1 : fabs(1 / rayDirY));
		double perpWallDist;

		//what direction to step in x or y-direction (either +1 or -1)
		int stepX;
		int stepY;

		int hit = 0; //was there a wall hit?
		int side; //was a NS or a EW wall hit?
		//calculate step and initial sideDist
		if (rayDirX < 0)
		{
			stepX = -1;
			sideDistX = (posX - mapX) * deltaDistX;
		}
		else
		{
			stepX = 1;
			sideDistX = (mapX + 1.0 - posX) * deltaDistX;
		}
		if (rayDirY < 0)
		{
			stepY = -1;
			sideDistY = (posY - mapY) * deltaDistY;
		}
		else
		{
			stepY = 1;
			sideDistY = (mapY + 1.0 - posY) * deltaDistY;
		}
		//perform DDA
		while (hit == 0)
		{
			//jump to next map square, OR in x-direction, OR in y-direction
			if (sideDistX < sideDistY)
			{
				sideDistX += deltaDistX;
				mapX += stepX;
				side = 0;
			}
			else
			{
				sideDistY += deltaDistY;
				mapY += stepY;
				side = 1;
			}
			//Check if ray has hit a wall
			if (worldMap[mapX][mapY] > 0) hit = 1;
		}
		//Calculate distance projected on camera direction (Euclidean distance will give fisheye effect!)
		if (side == 0) perpWallDist = (mapX - posX + (1 - stepX) / 2) / rayDirX;
		else           perpWallDist = (mapY - posY + (1 - stepY) / 2) / rayDirY;

		//Calculate height of line to draw on screen
		int lineHeight = (int)(h / perpWallDist);

		//calculate lowest and highest pixel to fill in current stripe
		int drawStart = -lineHeight / 2 + h / 2;
		if(drawStart < 0)drawStart = 0;
		int drawEnd = lineHeight / 2 + h / 2;
		if(drawEnd >= h)drawEnd = h - 1;

		printf("%d %d\n", drawStart, drawEnd);
		//choose wall color
		int color;
		switch(worldMap[mapX][mapY])
		{
			case 1:  color = 0X000000FF;  break; //red
			case 2:  color = 0X0000FF00;  break; //green
			case 3:  color = 0X00FF0000;   break; //blue
			case 4:  color = 0X00FFFFFF;  break; //white
			default: color = 0X00FFFF00; break; //yellow
		}

		//give x and y sides different brightness
		if (side == 1) {color = color / 2;}

		//draw the pixels of the stripe as a vertical line
		//printf("%d, %d, %d", x, drawStart, drawEnd);
		ver_line(img, x, drawStart, drawEnd, color);
	}
}

void mov_up(void)
{
	if(worldMap[(int)(posX + dirX * moveSpeed)][(int)(posY)] == 0) posX += dirX * moveSpeed;
	if(worldMap[(int)(posX)][(int)(posY + dirY * moveSpeed)] == 0) posY += dirY * moveSpeed;
}

void mov_down(void)
{
	if(worldMap[(int)(posX - dirX * moveSpeed)][(int)(posY)] == 0) posX -= dirX * moveSpeed;
	if(worldMap[(int)(posX)][(int)(posY - dirY * moveSpeed)] == 0) posY -= dirY * moveSpeed;
}

void mov_right(void)
{
	//both camera direction and camera plane must be rotated
	double oldDirX = dirX;
	dirX = dirX * cos(-rotSpeed) - dirY * sin(-rotSpeed);
	dirY = oldDirX * sin(-rotSpeed) + dirY * cos(-rotSpeed);
	double oldPlaneX = planeX;
	planeX = planeX * cos(-rotSpeed) - planeY * sin(-rotSpeed);
	planeY = oldPlaneX * sin(-rotSpeed) + planeY * cos(-rotSpeed);
}

void mov_left(void)
{
	 //both camera direction and camera plane must be rotated
	 double oldDirX = dirX;
	 dirX = dirX * cos(rotSpeed) - dirY * sin(rotSpeed);
	 dirY = oldDirX * sin(rotSpeed) + dirY * cos(rotSpeed);
	 double oldPlaneX = planeX;
	 planeX = planeX * cos(rotSpeed) - planeY * sin(rotSpeed);
	 planeY = oldPlaneX * sin(rotSpeed) + planeY * cos(rotSpeed);
}

int		key_hook(int keycode, t_data *img)
{
	t_data new;

	mlx_destroy_image(img->mlx, img->img);
	new.img = mlx_new_image(img->mlx, 800, 800);
	new.addr = mlx_get_data_addr(new.img, &new.bits_per_pixel, &new.line_length, &new.endian);
	if (keycode == ESCAPE)
		exit(EXIT_SUCCESS);
	else if (keycode == UP)
		mov_up();
	else if (keycode == DOWN)
		mov_down();
	else if (keycode == RIGHT)
		mov_right();
	else if (keycode == LEFT)
		mov_left();
	draw(&new);
	img->img = new.img;
	img->addr = mlx_get_data_addr(new.img, &new.bits_per_pixel, &new.line_length, &new.endian);
	mlx_put_image_to_window(img->mlx, img->mlx_win, img->img, 0, 0);
	return (keycode);
}

int             main(void)
{
	t_data  img;

	posX = 13, posY = 7;
	dirX = -1, dirY = 0; //initial direction vector
	planeX = 0, planeY = 0.66;
	img.mlx = mlx_init();
	img.mlx_win = mlx_new_window(img.mlx, 800, 800, "Raycaster");
	img.img = mlx_new_image(img.mlx, 800, 800);
	img.addr = mlx_get_data_addr(img.img, &img.bits_per_pixel, &img.line_length, &img.endian);
	draw(&img);
	mlx_hook(img.mlx_win, 2, 1L<<0, key_hook, &img);
	mlx_put_image_to_window(img.mlx, img.mlx_win, img.img, 0, 0);
	mlx_loop(img.mlx);
	return (0);
}
