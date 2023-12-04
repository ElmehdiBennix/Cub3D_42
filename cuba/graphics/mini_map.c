/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mini_map.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ebennix <ebennix@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/21 16:05:00 by ebennix           #+#    #+#             */
/*   Updated: 2023/12/04 04:10:13 by ebennix          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/cub3d.h"

void	mini_map(t_data *game ,double x_vis, double y_vis)
{
	int draw_x = 1408;
	int draw_y = 122;

	int x_distance = (x_vis * 2) * TILE_S + 1407;
	int y_distance = (y_vis * 2) * TILE_S + 122;

	
	float camera_x;
	float camera_y = game->player.y - (y_vis * TILE_S);
	while (draw_y <= y_distance)
	{
		camera_x = game->player.x - (x_vis * TILE_S);
		while (draw_x <= x_distance)
		{
			int x = floor(camera_x / TILE_S);
			int y = floor(camera_y / TILE_S);
			if (x < 0 || y < 0 || x >= (float)game->map_width || y >= (float)game->map_height)
				mlx_put_pixel(game->canvas.HUD, draw_x , draw_y, 0x000000FF);
			else if (game->map[y][x] == '1')
				mlx_put_pixel(game->canvas.HUD, draw_x , draw_y, 0xFFFFFFFF);
			else if (game->map[y][x] == '0')
				mlx_put_pixel(game->canvas.HUD, draw_x , draw_y, 0x66FFFFFF);
			else if (game->map[y][x] == 'D')
				mlx_put_pixel(game->canvas.HUD, draw_x , draw_y, 0xFF0FF00F);
			else
				mlx_put_pixel(game->canvas.HUD, draw_x , draw_y, 0x000000FF);
			draw_x++;
			camera_x++;
		}
		camera_y++;
		draw_x = 1407;
		if (draw_y == y_distance - 1)
			draw_x = 1408;
		draw_y++;
	}
	game->canvas.HUD->enabled = true;
}
