/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Cub3d.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hasalam <hasalam@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/29 15:08:12 by hasalam           #+#    #+#             */
/*   Updated: 2023/11/25 01:10:41 by hasalam          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Cub3d.h"
#include "MLX42/include/MLX42/MLX42.h"
#include <limits.h>
#include <math.h>
#include <stdbool.h>
#include <stdint.h>
#include <stdio.h>
#include <sys/wait.h>

void ft_helper(t_Player *player);

void ft_error(void)
{
	perror(mlx_strerror(mlx_errno));
	exit(EXIT_FAILURE);
}
const int map[MAP_NUM_ROWS][MAP_NUM_COLS] = {
	{1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1},
	{1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 1},
	{1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 0, 0, 1},
	{1, 0, 0, 0, 0, 0, 0, 0, 0, 1, 1, 1, 1, 0, 0, 0, 0, 1, 1, 1},
	{1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0, 1},
	{1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0, 0, 1},
	{1, 0, 0, 0, 0, 0, 0, 0, 0, 1, 0, 0, 1, 0, 0, 0, 1, 0, 0, 1},
	{1, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 0, 0, 1},
	{1, 0, 0, 0, 1, 0, 0, 0, 0, 0, 1, 0, 1, 0, 0, 0, 1, 0, 1, 1},
	{1, 0, 1, 0, 0, 0, 0, 0, 1, 0, 1, 0, 0, 1, 0, 0, 1, 0, 0, 1},
	{1, 0, 0, 0, 1, 1, 1, 1, 1, 0, 0, 0, 0, 0, 1, 0, 0, 0, 0, 1},
	{1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1}
	
};

void draw_line(mlx_image_t *img, float x0, float y0, float x1, float y1)
{
	float dx;
	float dy;
	float step;
	float x;
	float y;
	int i ;

	i = 0;

	dx = (x1 - x0);
	dy = (y1 - y0);

	step = fabsf(dx) > fabsf(dy) ? fabsf(dx) : fabsf(dy);

	dx = dx / step;
	dy = dy / step;

	x = x0;
	y = y0;
	while (i < step)
	{
		mlx_put_pixel(img, x, y, 0xFF00B3FF);
		x += dx;
		y += dy;
		i++;
	}
}

void draw_rectangle(mlx_image_t *img, int h, int w, int color, int tile)
{
	int i = h;
	while (i < h + tile)
	{
		int j = w;
		while (j < w + tile)
		{
			mlx_put_pixel(img, j * MINIMAP, i * MINIMAP, color);
			j++;
		}
		i++;
	}
}
void renderMap(t_Player *player)
{
	int i;
	int j;

	i = 0;
	while(i < MAP_NUM_ROWS)
	{
		j = 0;
		while(j < MAP_NUM_COLS)
		{
			if(map[i][j] == 1)
				draw_rectangle(player->img, i * TILE_S, j * TILE_S, 0xFFFFFFFF, 32);
			else if(map[i][j] == 0)
				draw_rectangle(player->img, i * TILE_S, j * TILE_S, 0x000000FF, 32);
			j++;
		}
		i++;
	}
}

void	renderRays(t_Player *player)
{
	int	i;

	i = 0;
	while (i < NUM_RAYS)
	{
		draw_line(player->img, player->x * MINIMAP, player->y * MINIMAP, player->rays[i].wallHitX * MINIMAP, player->rays[i].wallHitY * MINIMAP);
		i++;
	}
}

int get_rgba(int r, int g, int b, int a)
{
    return (r << 24 | g << 16 | b << 8 | a);
}

int ft_get_color(int x, int y, t_Player *player)
{
	int r;
	int g;
	int b;
	int a;

	a = 255;
	r = player->text1->pixels[(y * (player->text1->width * 4)) + (x * 4)];
	g = player->text1->pixels[(y * (player->text1->width * 4)) + (x * 4) + 1];
	b = player->text1->pixels[(y * (player->text1->width * 4)) + (x * 4) + 2];
	// color = &player->text1->pixels[(y * (player->text1->width * 4)) + (x * 4)];
	// printf("%d\n",player);
	// exit(0);
	// return (get_rgba(color[0], color[1], color[2], color[3]));
	return get_rgba(r, g, b, a);
}

void	generate3DMap(t_Player *player)
{
	int i;
	
	i = 0;
	while (i < NUM_RAYS)
	{
		float corrDistance = player->rays[i].distance * cos(player->rays[i].rayAngle - player->rotationA);
		float distanceProj = ((float)WIDTH / 2) / tan(FOV_ANGLE / 2);
		float projectedWAllHeight = (TILE_S / corrDistance) * distanceProj;

		int wallStripHeight = (int)projectedWAllHeight;
		int wallTopPixel = (HEIGHT / 2) - (wallStripHeight / 2);
		wallTopPixel = wallTopPixel < 0 ? 0 : wallTopPixel;
		
		int wallBottomPixel = (HEIGHT / 2) + (wallStripHeight / 2);
		wallBottomPixel = wallBottomPixel > HEIGHT ? HEIGHT : wallBottomPixel;

		int y = 0;
		int textOffsetX;
		while (y < wallTopPixel)
		{
			mlx_put_pixel(player->img, i, y, 0x66FFFFFF);
			y++;
		}

		if (player->rays[i].wasHitVertical)
			textOffsetX = fmodf(player->rays[i].wallHitY, TILE_S) * ((float)player->text1->width / TILE_S);
		else
			textOffsetX = fmodf(player->rays[i].wallHitX, TILE_S) * ((float)player->text1->width / TILE_S) ;
		y = wallTopPixel;
		while (y < wallBottomPixel)
		{
			int distanceFromTop = y + (wallStripHeight / 2) - (HEIGHT / 2);
			int textOffsetY = distanceFromTop * ((float)player->text1->height / wallStripHeight);
  			uint32_t color = ft_get_color(textOffsetX, textOffsetY, player);
			mlx_put_pixel(player->img, i, y, color);
			y++;
		}
		y = wallBottomPixel;
		while (y < HEIGHT)
		{
			mlx_put_pixel(player->img, i, y, 0xCC6600FF);
			y++;
		}
		i++;

	}
}

// void renderPlayer(t_Player *player)
// {
// 	mlx_put_pixel(player->img, player->x, player->y, 0xFF3333FF);
// 	draw_line(player->img, player->x , player->y , player->x + cos(player->rotationA) * 30, player->y + sin(player->rotationA) * 30);
// }

int check_walls1(t_Player *player, float px, float py)
{
	(void)player;
	if (px < 0 || px > WIDTH || py < 0 || py > HEIGHT)
		return 0;
	float mapgridX = floor(px / TILE_S);
	float mapgridY = floor(py / TILE_S);
	if (map[(int)mapgridY][(int)mapgridX] != 0 || (map[(int)mapgridY][(int)(player->x / TILE_S)] && map[(int)(player->y / TILE_S)][(int)mapgridX]))
		return (1);
	return (0);
}
int check_walls2(t_Player *player, float px, float py)
{
	(void)player;
	if (px < 0 || px > WIDTH || py < 0 || py > HEIGHT)
		return 0;
	float mapgridX = floor(px / TILE_S);
	float mapgridY = floor(py / TILE_S);
	return (map[(int)mapgridY][(int)mapgridX] != 0);
}

void ft_update(t_Player *player)
{
	player->rotationA += player->turnD * player->turnS;
	float movestep = player->walkD * player->walkS;
	float newplayerX = cos(player->rotationA) * movestep;
	float newplayerY = sin(player->rotationA) * movestep;
	float px = player->x + newplayerX;
	float py = player->y + newplayerY;
	if (!check_walls1(player, px, py))
	{
		player->x = px;
		player->y = py;
	}
	float tmp = player->rotationA + player->sideW * player->turnS;
	movestep = player->sideW * player->walkS;
	newplayerX = cos(tmp + (90 * (M_PI / 180))) * movestep;
	newplayerY = sin(tmp + (90 * (M_PI / 180))) * movestep;
	px = player->x + newplayerX;
	py = player->y + newplayerY;
	if (!check_walls1(player, px, py))
	{
		player->x = px;
		player->y = py;
	}
}

float	normalizeAngle(float angle)
{
	angle = fmod(angle, (2 * M_PI));
	if (angle < 0)
		angle = (2 * M_PI) + angle;
	return angle;
}

float	distancebetweenPoints(float x1, float y1, float x2, float y2)
{
	return sqrt(((x2 - x1) * (x2 - x1)) + ((y2 - y1) * (y2 - y1)));
}

void	castRay(float rayA, int sId, t_Player *player)
{
	rayA = normalizeAngle(rayA);
	
	int isRayFacingDown = rayA > 0  && rayA < M_PI;
	int isRayFacingUp = !isRayFacingDown;
	int isRayFacingRight = rayA < 0.5 * M_PI || rayA > 1.5 * M_PI;
	int isRayFacingLeft = !isRayFacingRight;

	float xintercept;
	float yintercept;
	float xstep;
	float ystep;

	// HORIZONTAL RAY GRID

	int foundHorzWallHit = false;
	float horzWallHitX = 0;
	float horzWallHitY = 0;
	int horzWallcontent = 0;

	// Find the y coordinate of the closest horizontal
	
	yintercept = floor(player->y / TILE_S) * TILE_S;
	yintercept += isRayFacingDown ? TILE_S : 0;
	
	// Find the x coordinate of the closest horizontal

	xintercept = player->x + (yintercept - player->y) / tan(rayA);

	// Calculate the increment xstep and ystep

	ystep = TILE_S;
	ystep *= isRayFacingUp ? -1 : 1;

	xstep = TILE_S / tan(rayA);
	xstep *= (isRayFacingLeft && xstep > 0) ? -1 : 1;
	xstep *= (isRayFacingRight && xstep < 0) ? -1 : 1;
	
	float nextHorzTouchX = xintercept;
	float nextHorzTouchY = yintercept;

	// Icrement xstep and ystep until we find a wall

	while (nextHorzTouchX >= 0 && nextHorzTouchX <= WINDOW_WIDTH && nextHorzTouchY >= 0 && nextHorzTouchY <= WINDOW_HEIGHT)
	{
		float xToCheck = nextHorzTouchX;
		float yToCheck = nextHorzTouchY + (isRayFacingUp ? -1 : 0);

		if (check_walls2(player, xToCheck, yToCheck))
		{
			// found a wall hit
			horzWallHitX = nextHorzTouchX;
			horzWallHitY = nextHorzTouchY;
			horzWallcontent = map[(int)floor(yToCheck / TILE_S)][(int)floor(xToCheck / TILE_S)];
			foundHorzWallHit = true;
			break;
		}
		else {
			nextHorzTouchX += xstep;
			nextHorzTouchY += ystep;
		}
	}

	// VERTICAL RAY GRID

	int foundVertWallHit = false;
	float vertWallHitX = 0;
	float vertWallHitY = 0;
	int vertWallcontent = 0;

	// Find the x coordinate of the closest horizontal
	
	xintercept = floor(player->x / TILE_S) * TILE_S;
	xintercept += isRayFacingRight ? TILE_S : 0;
	
	// Find the y coordinate of the closest horizontal

	yintercept = player->y + (xintercept - player->x) * tan(rayA);

	// Calculate the increment xstep and ystep

	xstep = TILE_S;
	xstep *= isRayFacingLeft ? -1 : 1;

	ystep = TILE_S * tan(rayA);
	ystep *= (isRayFacingUp && ystep > 0) ? -1 : 1;
	ystep *= (isRayFacingDown && ystep < 0) ? -1 : 1;
	
	float nextVertTouchX = xintercept;
	float nextVertTouchY = yintercept;

	// Icrement xstep and ystep until we find a wall

	while (nextVertTouchX >= 0 && nextVertTouchX <= WINDOW_WIDTH && nextVertTouchY >= 0 && nextVertTouchY <= WINDOW_HEIGHT)
	{
		float xToCheck = nextVertTouchX + (isRayFacingLeft ? -1 : 0);
		float yToCheck = nextVertTouchY;

		if (check_walls2(player, xToCheck, yToCheck))
		{
			// found a wall hit
			vertWallHitX = nextVertTouchX;
			vertWallHitY = nextVertTouchY;
			vertWallcontent = map[(int)floor(yToCheck / TILE_S)][(int)floor(xToCheck / TILE_S)];
			foundVertWallHit = true;
			break;
		}
		else {
			nextVertTouchX += xstep;
			nextVertTouchY += ystep;
		}
	}

	// Calculate both horizontal and vertical hit distances and choose the smallest one
	//t_Ray rays;
	float horzHitDistance = foundHorzWallHit ? distancebetweenPoints(player->x, player->y, horzWallHitX, horzWallHitY) : (float)INT_MAX;
	float vertHitDistance = foundVertWallHit ? distancebetweenPoints(player->x, player->y, vertWallHitX, vertWallHitY) : (float)INT_MAX;

	if (vertHitDistance < horzHitDistance)
	{
		player->rays[sId].distance = vertHitDistance;
		player->rays[sId].wallHitX = vertWallHitX;
		player->rays[sId].wallHitY = vertWallHitY;
		player->rays[sId].wallHitContent = vertWallcontent;
		player->rays[sId].wasHitVertical = true;
	}
	else
	{
		player->rays[sId].distance = horzHitDistance;
		player->rays[sId].wallHitX = horzWallHitX;
		player->rays[sId].wallHitY = horzWallHitY;
		player->rays[sId].wallHitContent = horzWallcontent;
		player->rays[sId].wasHitVertical = false;
	}
	player->rays[sId].rayAngle = rayA;
	player->rays[sId].isRayfacingDown = isRayFacingDown;
	player->rays[sId].isRayfacingUp = isRayFacingUp;
	player->rays[sId].isRayfacingleft = isRayFacingLeft;
	player->rays[sId].isRayfacingRight = isRayFacingRight;
}

void	castAllRays(t_Player *player)
{
	float rayA = player->rotationA - (FOV_ANGLE / 2);
	int	i;

	i = -1;
	while (++i < NUM_RAYS)
	{
		castRay(rayA, i, player);
		rayA += FOV_ANGLE / NUM_RAYS;
	}
}

void	ft_loop(void* param)
{
	(void)param;
	t_Player *player = param;

	mlx_delete_image( player->mlx, player->img);
	player->img = mlx_new_image(player->mlx, WIDTH, HEIGHT);
	castAllRays(player);
	ft_update(player);
	generate3DMap(player);
	renderMap(player);
	renderRays(player);
	if (!player->img || (mlx_image_to_window(player->mlx, player->img, 0, 0) < 0))
		ft_error();
}
void ft_key(mlx_key_data_t keycode, void *param)
{
	t_Player *player = param;

	if(keycode.key == MLX_KEY_ESCAPE)
		exit(1);
	if (keycode.key == MLX_KEY_W && (keycode.action == MLX_PRESS || keycode.action == MLX_REPEAT))
		player->walkD = 1;
	if (keycode.key == MLX_KEY_W && keycode.action == MLX_RELEASE)
		player->walkD = 0;
	if (keycode.key == MLX_KEY_S && (keycode.action == MLX_PRESS || keycode.action == MLX_REPEAT))
		player->walkD = -1;
	if (keycode.key == MLX_KEY_S && keycode.action == MLX_RELEASE)
		player->walkD = 0;
	if (keycode.key == MLX_KEY_RIGHT && (keycode.action == MLX_PRESS || keycode.action == MLX_REPEAT))
		player->turnD = 1;
	if (keycode.key == MLX_KEY_RIGHT && keycode.action == MLX_RELEASE)
		player->turnD = 0;
	if (keycode.key == MLX_KEY_LEFT && (keycode.action == MLX_PRESS || keycode.action == MLX_REPEAT))
		player->turnD = -1;
	if (keycode.key == MLX_KEY_LEFT && keycode.action == MLX_RELEASE)
		player->turnD = 0;
	if (keycode.key == MLX_KEY_D && (keycode.action == MLX_PRESS || keycode.action == MLX_REPEAT))
		player->sideW = 1;
	if (keycode.key == MLX_KEY_D && keycode.action == MLX_RELEASE)
		player->sideW = 0;
	if (keycode.key == MLX_KEY_A && (keycode.action == MLX_PRESS || keycode.action == MLX_REPEAT))
		player->sideW = -1;
	if (keycode.key == MLX_KEY_A && keycode.action == MLX_RELEASE)
		player->sideW = 0;
}

void ft_mouse(void* param)
{
	t_Player *player = param;
	static int i;
	mlx_get_mouse_pos(player->mlx, &player->mouseX, &player->mouseY);
	if (i++ == 0)
		player->mouseX = 500;
	player->rotationA += (float)(player->mouseX - 500) / 500;
	mlx_set_mouse_pos(player->mlx, 500, 500);
}

void setup(t_Player *player)
{
	player->x = 200;
	player->y = 170;
	player->turnD = 0;
	player->mouseX = 0;
	player->walkD = 0;
	player->sideW = 0;
	player->rotationA = M_PI / 2;
	player->walkS = 1;
	player->turnS = 2 * (M_PI / 180);
}

void ft_helper(t_Player *player)
{
	mlx_key_hook(player->mlx, ft_key, player);
	mlx_loop_hook(player->mlx, ft_loop, player);
	mlx_set_cursor_mode(player->mlx, MLX_MOUSE_DISABLED);
	mlx_cursor_hook(player->mlx,(void *)ft_mouse, player);
	mlx_loop(player->mlx);
	mlx_terminate(player->mlx);
}

int	main()
{ 
	t_Player player;
	setup(&player);
	player.mlx = mlx_init(WIDTH, HEIGHT, "Cub3D", false);
	if (!player.mlx)
		ft_error();
	
	player.img = mlx_new_image(player.mlx, WIDTH, HEIGHT);
	player.text1 = mlx_load_png("wall2.png");
	if (!player.text1)
		ft_error();
	ft_helper(&player);
	return (EXIT_SUCCESS);
}