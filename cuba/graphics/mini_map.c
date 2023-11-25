/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mini_map.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ebennix <ebennix@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/21 16:05:00 by ebennix           #+#    #+#             */
/*   Updated: 2023/11/25 01:38:18 by ebennix          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/cub3d.h"

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

// void renderPlayer(t_Player *player)
// {
// 	mlx_put_pixel(player->img, player->x, player->y, 0xFF3333FF);
// 	draw_line(player->img, player->x , player->y , player->x + cos(player->rotationA) * 30, player->y + sin(player->rotationA) * 30);
// }