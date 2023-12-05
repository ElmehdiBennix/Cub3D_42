/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   raycasting.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hasalam <hasalam@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/05 13:49:46 by hasalam           #+#    #+#             */
/*   Updated: 2023/12/05 20:19:11 by hasalam          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/cub3d.h"

void	cast_ray_helper6(t_data *game, t_var *var, int sId)
{
	if (var->vertHitDist < var->horzHitDist)
	{
		game->rays[sId].distance = var->vertHitDist;
		game->rays[sId].wallHitX = var->vertWall_Hit_X;
		game->rays[sId].wallHitY = var->vertWall_Hit_Y;
		game->rays[sId].wallHitContent = var->vertWallcontnt;
		game->rays[sId].wasHitVertical = true;
		if (game->rays[sId].isRayfacingRight)
			game->rays[sId].text = game->East.texture;
		else
			game->rays[sId].text = game->West.texture;
	}
	else
	{
		game->rays[sId].distance = var->horzHitDist;
		game->rays[sId].wallHitX = var->horzWall_Hit_X;
		game->rays[sId].wallHitY = var->horzWall_Hit_Y;
		game->rays[sId].wallHitContent = var->horzWallcontnt;
		game->rays[sId].wasHitVertical = false;
		if (game->rays[sId].isRayfacingUp)
			game->rays[sId].text = game->North.texture;
		else
			game->rays[sId].text = game->South.texture;
	}
}

void	cast_ray(float ray_a, int sId, t_data *game)
{
	t_var	var;

	ray_a = normalize_angle(ray_a);
	cast_ray_helper1(game, &var, ray_a);
	if (var.isRayFac_L == true && var.xstep > 0)
		var.xstep *= -1;
	else if (var.isRayFac_R == true && var.xstep < 0)
		var.xstep *= -1;
	var.nxtHorzTouch_X = var.x_intercept;
	var.nxtHorzTouch_Y = var.y_intercept;
	cast_ray_helper2(game, &var);
	cast_ray_helper3(game, &var, ray_a);
	cast_ray_helper4(game, &var);
	cast_ray_helper5(game, &var);
	cast_ray_helper6(game, &var, sId);
	if (game->rays[sId].wallHitContent == 'D')
		game->rays[sId].text = game->door;
	game->rays[sId].ray_angle = ray_a;
	game->rays[sId].isRayfacingDown = var.isRayFac_D;
	game->rays[sId].isRayfacingUp = var.isRayFac_U;
	game->rays[sId].isRayfacingleft = var.isRayFac_L;
	game->rays[sId].isRayfacingRight = var.isRayFac_R;
}

void	cast_all_rays(t_data *game)
{
	float	ray_a;
	int		i;

	ray_a = game->player.rotationA - (FOV_ANGLE / 2);
	i = -1;
	while (++i < NUM_RAYS)
	{
		cast_ray(ray_a, i, game);
		ray_a += FOV_ANGLE / NUM_RAYS;
	}
}
