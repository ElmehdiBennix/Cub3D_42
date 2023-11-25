/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   raycasting.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ebennix <ebennix@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/29 15:08:12 by hasalam           #+#    #+#             */
/*   Updated: 2023/11/25 01:47:26 by ebennix          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/cub3d.h"

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
	// renderMap(player);
	// renderRays(player);
	if (!player->img || (mlx_image_to_window(player->mlx, player->img, 0, 0) < 0))
		ft_error();
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
	// player.text1 = mlx_load_png("wall2.png");
	// if (!player.text1)
	// 	ft_error();
	ft_helper(&player);
	return (EXIT_SUCCESS);
}