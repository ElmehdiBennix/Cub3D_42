/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   raycast_helper.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hasalam <hasalam@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/05 02:02:09 by hasalam           #+#    #+#             */
/*   Updated: 2023/12/05 13:44:03 by hasalam          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/cub3d.h"

void	cast_ray_helper1(t_data *game, t_var *var, float ray_a)
{
	if (ray_a > 0 && ray_a < M_PI)
		var->isRayFac_D = true;
	else
		var->isRayFac_D = false;
	var->isRayFac_U = !var->isRayFac_D;
	if (ray_a < (0.5 * M_PI) || ray_a > (1.5 * M_PI))
		var->isRayFac_R = true;
	else
		var->isRayFac_R = false;
	var->isRayFac_L = !var->isRayFac_R;
	var->foundHorzW_Hit = false;
	var->horzWall_Hit_X = 0;
	var->horzWall_Hit_Y = 0;
	var->horzWallcontnt = 0;
	var->y_intercept = floor(game->player.y / TILE_S) * TILE_S;
	if (var->isRayFac_D == true)
		var->y_intercept += TILE_S;
	var->x_intercept = game->player.x + (var->y_intercept - game->player.y)
		/ tan(ray_a);
	var->ystep = TILE_S;
	if (var->isRayFac_U == true)
		var->ystep *= -1;
	var->xstep = TILE_S / tan(ray_a);
}

void	cast_ray_helper2(t_data *game, t_var *var)
{
	while (var->nxtHorzTouch_X >= 0
		&& var->nxtHorzTouch_X <= game->map_width * TILE_S
		&& var->nxtHorzTouch_Y >= 0
		&& var->nxtHorzTouch_Y < game->map_height * TILE_S)
	{
		var->Check_x = var->nxtHorzTouch_X;
		if (var->isRayFac_U == true)
			var->Check_y = var->nxtHorzTouch_Y - 1;
		else
			var->Check_y = var->nxtHorzTouch_Y;
		if (check_walls(game, var->Check_x, var->Check_y, 1))
		{
			var->horzWall_Hit_X = var->nxtHorzTouch_X;
			var->horzWall_Hit_Y = var->nxtHorzTouch_Y;
			var->horzWallcontnt = game->map[(int)floor(var->Check_y / TILE_S)]
			[(int)floor(var->Check_x / TILE_S)];
			var->foundHorzW_Hit = true;
			break ;
		}
		else
		{
			var->nxtHorzTouch_X += var->xstep;
			var->nxtHorzTouch_Y += var->ystep;
		}
	}
}

void	cast_ray_helper3(t_data *game, t_var *var, float ray_a)
{
	var->foundVertW_Hit = false;
	var->vertWall_Hit_X = 0;
	var->vertWall_Hit_Y = 0;
	var->vertWallcontnt = 0;
	var->x_intercept = floor(game->player.x / TILE_S) * TILE_S;
	if (var->isRayFac_R == true)
		var->x_intercept += TILE_S;
	var->y_intercept = game->player.y + (var->x_intercept - game->player.x)
		* tan(ray_a);
	var->xstep = TILE_S;
	if (var->isRayFac_L == true)
		var->xstep *= -1;
	var->ystep = TILE_S * tan(ray_a);
	if (var->isRayFac_U == true && var->ystep > 0)
		var->ystep *= -1;
	else if (var->isRayFac_D == true && var->ystep < 0)
		var->ystep *= -1;
	var->nxtVertTouch_X = var->x_intercept;
	var->nxtVertTouch_Y = var->y_intercept;
}

void	cast_ray_helper4(t_data *game, t_var *var)
{
	while (var->nxtVertTouch_X >= 0
		&& var->nxtVertTouch_X <= game->map_width * TILE_S
		&& var->nxtVertTouch_Y >= 0
		&& var->nxtVertTouch_Y < game->map_height * TILE_S)
	{
		if (var->isRayFac_L)
			var->Check_x = var->nxtVertTouch_X - 1;
		else
			var->Check_x = var->nxtVertTouch_X;
		var->Check_y = var->nxtVertTouch_Y;
		if (check_walls(game, var->Check_x, var->Check_y, 1))
		{
			var->vertWall_Hit_X = var->nxtVertTouch_X;
			var->vertWall_Hit_Y = var->nxtVertTouch_Y;
			var->vertWallcontnt = game->map[(int)floor(var->Check_y / TILE_S)]
			[(int)floor(var->Check_x / TILE_S)];
			var->foundVertW_Hit = true;
			break ;
		}
		else
		{
			var->nxtVertTouch_X += var->xstep;
			var->nxtVertTouch_Y += var->ystep;
		}
	}
}

void	cast_ray_helper5(t_data *game, t_var *var)
{
	if (var->foundHorzW_Hit == true)
		var->horzHitDist = distancebetweenPoints(game->player.x, game->player.y,
				var->horzWall_Hit_X, var->horzWall_Hit_Y);
	else
		var->horzHitDist = (float)INT_MAX;
	if (var->foundVertW_Hit == true)
		var->vertHitDist = distancebetweenPoints(game->player.x, game->player.y,
				var->vertWall_Hit_X, var->vertWall_Hit_Y);
	else
		var->vertHitDist = (float)INT_MAX;
}
