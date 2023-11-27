/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw3d.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ebennix <ebennix@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/25 01:35:18 by ebennix           #+#    #+#             */
/*   Updated: 2023/11/27 05:13:49 by ebennix          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/cub3d.h"

void	generate3DMap(t_data *game)
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
			textOffsetX = fmodf(player->rays[i].wallHitY, TILE_S) * ((float)player->rays[i].text->width / TILE_S);
		else
			textOffsetX = fmodf(player->rays[i].wallHitX, TILE_S) * ((float)player->rays[i].text->width / TILE_S) ;
		y = wallTopPixel;
		while (y < wallBottomPixel)
		{
			int distanceFromTop = y + (wallStripHeight / 2) - (HEIGHT / 2);
			int textOffsetY = distanceFromTop * ((float)player->rays[i].text->height / wallStripHeight);
  			uint32_t color = ft_get_color(i,textOffsetX, textOffsetY, player);
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