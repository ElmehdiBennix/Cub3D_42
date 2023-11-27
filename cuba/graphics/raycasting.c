/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   raycasting.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ebennix <ebennix@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/26 21:47:37 by ebennix           #+#    #+#             */
/*   Updated: 2023/11/27 05:29:00 by ebennix          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/cub3d.h"

// const int map[MAP_NUM_ROWS][MAP_NUM_COLS] = {
// 	{1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1},
// 	{1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 1},
// 	{1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 0, 0, 1},
// 	{1, 0, 0, 0, 0, 0, 0, 0, 0, 1, 1, 1, 1, 0, 0, 0, 0, 1, 1, 1},
// 	{1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0, 1},
// 	{1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0, 0, 1},
// 	{1, 0, 0, 0, 0, 0, 0, 0, 0, 1, 0, 0, 1, 0, 0, 0, 1, 0, 0, 1},
// 	{1, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 0, 0, 1},
// 	{1, 0, 0, 0, 1, 0, 0, 0, 0, 0, 1, 0, 1, 0, 0, 0, 1, 0, 1, 1},
// 	{1, 0, 1, 0, 0, 0, 0, 0, 1, 0, 1, 0, 0, 1, 0, 0, 1, 0, 0, 1},
// 	{1, 0, 0, 0, 1, 1, 1, 1, 1, 0, 0, 0, 0, 0, 1, 0, 0, 0, 0, 1},
// 	{1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1}
	
// };


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

		if (check_walls2(game, xToCheck, yToCheck))
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

		if (check_walls2(game, xToCheck, yToCheck))
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
	float horzHitDistance = foundHorzWallHit ? distancebetweenPoints(game->player.x, game->player.y, horzWallHitX, horzWallHitY) : (float)INT_MAX;
	float vertHitDistance = foundVertWallHit ? distancebetweenPoints(game->player.x, game->player.y, vertWallHitX, vertWallHitY) : (float)INT_MAX;
	if (vertHitDistance < horzHitDistance)
	{
		game->rays[sId].distance = vertHitDistance;
		game->rays[sId].wallHitX = vertWallHitX;
		game->rays[sId].wallHitY = vertWallHitY;
		game->rays[sId].wallHitContent = vertWallcontent;
		game->rays[sId].wasHitVertical = true;
		if (game->rays[sId].isRayfacingRight) // recheck for texture directions 
			game->rays[sId].text = game->East.texture; // +
		else
			game->rays[sId].text = game->West.texture; // +
	}
	else
	{
		game->rays[sId].distance = horzHitDistance;
		game->rays[sId].wallHitX = horzWallHitX;
		game->rays[sId].wallHitY = horzWallHitY;
		game->rays[sId].wallHitContent = horzWallcontent;
		game->rays[sId].wasHitVertical = false;
		if (game->rays[sId].isRayfacingUp)
			game->rays[sId].text = game->North.texture; //+
		else
			game->rays[sId].text = game->South.texture; // +
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
	//exit(1);
}
