/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ebennix <ebennix@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/29 15:08:12 by hasalam           #+#    #+#             */
/*   Updated: 2023/11/21 16:54:03 by ebennix          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/cub3d.h"

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

void	generate3DMap(t_data *game)
{
	int i;
	
	i = 0;
	while (i < NUM_RAYS)
	{
		float corrDistance = game->rays[i].distance * cos(game->rays[i].rayAngle - game->player.rotationA);
		float distanceProj = ((float)WIDTH / 2) / tan(FOV_ANGLE / 2);
		float projectedWAllHeight = (TILE_S / corrDistance) * distanceProj;

		int wallStripHeight = projectedWAllHeight;
		int wallTopPixel = (HEIGHT / 2) - (wallStripHeight / 2);
		wallTopPixel = wallTopPixel < 0 ? 0 : wallTopPixel;
		
		int wallBottomPixel = (HEIGHT / 2) + (wallStripHeight / 2);
		wallBottomPixel = wallBottomPixel > HEIGHT ? HEIGHT : wallBottomPixel;

		int y = 0;
		int textOffsetX;
		while (y < wallTopPixel)
		{
			mlx_put_pixel(game->HUD_Frame, i, y, 0x66FFFFFF);
			y++;
		}

		if (game->rays[i].wasHitVertical)
			textOffsetX = (int)game->rays[i].wallHitY % TILE_S;
		else
			textOffsetX = (int)game->rays[i].wallHitX % TILE_S;

		y = wallTopPixel;
		while (y < wallBottomPixel)
		{
			int color = 0x0000FFFF;
			color = game->rays[i].wasHitVertical ? 0x0000FFFF : 0x0000CCCC;
			mlx_put_pixel(game->HUD_Frame, i, y, color);
			y++;
		}

		y = wallBottomPixel;
		while (y < HEIGHT)
		{
			mlx_put_pixel(game->HUD_Frame, i, y, 0xCC6600FF);
			y++;
		}
		i++;
	}
}

void renderPlayer(t_data *game)
{
	mlx_put_pixel(game->HUD_Frame, game->player.x, game->player.y, 0xFF3333FF);
	draw_line(game->HUD_Frame, game->player.x , game->player.y , game->player.x + cos(game->player.rotationA) * 30, game->player.y + sin(game->player.rotationA) * 30);
}
int check_walls(t_data *game, float px, float py)
{
	if (px < 0 || px > WINDOW_WIDTH || py < 0 || py > WINDOW_HEIGHT)
		return 0;
	int mapgridX = floor(px / TILE_S);
	int mapgridY = floor(py / TILE_S);
	return game->map[mapgridY][mapgridX] != '0'; // 1 or 0 
}

void ft_update(t_data *game)
{
	game->player.rotationA += game->player.turnD * game->player.turnS;
	float movestep = game->player.walkD * game->player.walkS;
	float newplayerX = cos(game->player.rotationA) * movestep;
	float newplayerY = sin(game->player.rotationA) * movestep;
	float px = game->player.x + newplayerX;
	float py = game->player.y + newplayerY;
	if (!check_walls(game ,px, py))
	{
		game->player.x = px;
		game->player.y = py;
	}
}

float	normalizeAngle(float angle)
{
	angle = remainder(angle, (2 * M_PI));
	if (angle < 0)
		angle = (2 * M_PI) + angle;
	return angle;
}

float	distancebetweenPoints(float x1, float y1, float x2, float y2)
{
	return sqrt(((x2 - x1) * (x2 - x1)) + ((y2 - y1) * (y2 - y1)));
}

void	castRay(float rayA, int sId, t_data *game)
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
	
	yintercept = floor(game->player.y / TILE_S) * TILE_S;
	yintercept += isRayFacingDown ? TILE_S : 0;
	
	// Find the x coordinate of the closest horizontal

	xintercept = game->player.x + (yintercept - game->player.y) / tan(rayA);

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

		if (check_walls(game ,xToCheck, yToCheck))
		{
			// found a wall hit
			horzWallHitX = nextHorzTouchX;
			horzWallHitY = nextHorzTouchY;
			horzWallcontent = game->map[(int)floor(yToCheck / TILE_S)][(int)floor(xToCheck / TILE_S)];
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
	
	xintercept = floor(game->player.x / TILE_S) * TILE_S;
	xintercept += isRayFacingRight ? TILE_S : 0;
	
	// Find the y coordinate of the closest horizontal

	yintercept = game->player.y + (xintercept - game->player.x) * tan(rayA);

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

		if (check_walls(game,xToCheck, yToCheck))
		{
			// found a wall hit
			vertWallHitX = nextVertTouchX;
			vertWallHitY = nextVertTouchY;
			vertWallcontent = game->map[(int)floor(yToCheck / TILE_S)][(int)floor(xToCheck / TILE_S)];
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
	float horzHitDistance = foundHorzWallHit ? distancebetweenPoints(game->player.x, game->player.y, horzWallHitX, horzWallHitY) : (float)INT_MAX;
	float vertHitDistance = foundVertWallHit ? distancebetweenPoints(game->player.x, game->player.y, vertWallHitX, vertWallHitY) : (float)INT_MAX;

	if (vertHitDistance < horzHitDistance)
	{
		game->rays[sId].distance = vertHitDistance;
		game->rays[sId].wallHitX = vertWallHitX;
		game->rays[sId].wallHitY = vertWallHitY;
		game->rays[sId].wallHitContent = vertWallcontent;
		game->rays[sId].wasHitVertical = true;
	}
	else
	{
		game->rays[sId].distance = horzHitDistance;
		game->rays[sId].wallHitX = horzWallHitX;
		game->rays[sId].wallHitY = horzWallHitY;
		game->rays[sId].wallHitContent = horzWallcontent;
		game->rays[sId].wasHitVertical = false;
	}
	game->rays[sId].rayAngle = rayA;
	game->rays[sId].isRayfacingDown = isRayFacingDown;
	game->rays[sId].isRayfacingUp = isRayFacingUp;
	game->rays[sId].isRayfacingleft = isRayFacingLeft;
	game->rays[sId].isRayfacingRight = isRayFacingRight;
}

void	castAllRays(t_data *game)
{
	float rayA = game->player.rotationA - (FOV_ANGLE / 2);
	int	i;

	i = -1;
	while (++i < NUM_RAYS)
	{
		castRay(rayA, i, game);
		rayA += FOV_ANGLE / NUM_RAYS;
	}
}

void	renderRays(t_data *game)
{
	int	i;

	i = 0;
	while (i < NUM_RAYS)
	{
		draw_line(game->HUD_Frame, game->player.x * MINIMAP, game->player.y * MINIMAP, game->rays[i].wallHitX * MINIMAP, game->rays[i].wallHitY * MINIMAP);
		i++;
	}
}

void renderMap(t_data *game)
{
	unsigned int i;
	unsigned int j;

	i = 0;
	while(i < game->map_height)
	{
		j = 0;
		while(j < game->map_width)
		{
			if(game->map[i][j] == 1)
				draw_rectangle(game->HUD_Frame, i * TILE_S, j * TILE_S, 0xFFFFFFFF, 32);
			else if(game->map[i][j] == 0)
				draw_rectangle(game->HUD_Frame, i * TILE_S, j * TILE_S, 0x000000FF, 32);
			j++;
		}
		i++;
	}
}


void	ft_loop(t_data *game)
{
	mlx_delete_image(game->mlx, game->HUD_Frame);
	game->HUD_Frame = mlx_new_image(game->mlx, WIDTH, HEIGHT);
	castAllRays(game);
	// ft_update(game);
	// generate3DMap(game);
	
	// renderMap(game);
	// renderRays(game);
	
	if (!game->HUD_Frame || (mlx_image_to_window(game->mlx, game->HUD_Frame, 0, 0) < 0))
		ft_error();
}

void ft_key(mlx_key_data_t keycode, t_data *game)
{
	if (keycode.key == MLX_KEY_UP && (keycode.action == MLX_PRESS || keycode.action == MLX_REPEAT))
		game->player.walkD = 1;
	else if (keycode.key == MLX_KEY_UP && keycode.action == MLX_RELEASE)
		game->player.walkD = 0;
	else if (keycode.key == MLX_KEY_DOWN && (keycode.action == MLX_PRESS || keycode.action == MLX_REPEAT))
		game->player.walkD = -1;
	else if (keycode.key == MLX_KEY_DOWN && keycode.action == MLX_RELEASE)
		game->player.walkD = 0;
	else if (keycode.key == MLX_KEY_RIGHT && (keycode.action == MLX_PRESS || keycode.action == MLX_REPEAT))
		game->player.turnD = 1;
	else if (keycode.key == MLX_KEY_RIGHT && keycode.action == MLX_RELEASE)
		game->player.turnD = 0;
	else if (keycode.key == MLX_KEY_LEFT && (keycode.action == MLX_PRESS || keycode.action == MLX_REPEAT))
		game->player.turnD = -1;
	else if (keycode.key == MLX_KEY_LEFT && keycode.action == MLX_RELEASE)
		game->player.turnD = 0;
	else if (keycode.key == MLX_KEY_ESCAPE)
		exit(EXIT_SUCCESS);
}

// void setup(t_data *player)
// {
// 	player->x = TILE_S + (TILE_S / 2); // tile size mine 
// 	player->y = TILE_S + (TILE_S / 2); // tile size mine 
// 	player->width = 5;
// 	player->height = 5;
// 	player->turnD = 0;
// 	player->walkD = 0;
// 	player->rotationA = M_PI / 2;
// 	player->walkS = 1;
// 	player->turnS = 2 * (M_PI / 180);
// }

void ft_helper(t_data *player)
{
	mlx_key_hook(player->mlx, (void *)ft_key, player);
	mlx_loop_hook(player->mlx, (void *)ft_loop, player);
	mlx_loop(player->mlx);
	mlx_terminate(player->mlx);
}
