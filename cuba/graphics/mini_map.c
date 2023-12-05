/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mini_map.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hasalam <hasalam@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/21 16:05:00 by ebennix           #+#    #+#             */
/*   Updated: 2023/12/05 18:21:55 by hasalam          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/cub3d.h"

void	mini_map_helper(t_data *game, t_var *var)
{
	while (++var->draw_x <= var->x_dist)
	{
		var->x = floor(var->cam_x / TILE_S);
		var->y = floor(var->cam_y / TILE_S);
		if (var->x < 0 || var->y < 0 || var->x >= (float)game->map_width
			|| var->y >= (float)game->map_height)
			mlx_put_pixel(game->canvas.HUD, var->draw_x,
				var->draw_y, 0x000000FF);
		else if (game->map[var->y][var->x] == '1')
			mlx_put_pixel(game->canvas.HUD, var->draw_x,
				var->draw_y, 0xFFFFFFFF);
		else if (game->map[var->y][var->x] == '0')
			mlx_put_pixel(game->canvas.HUD, var->draw_x,
				var->draw_y, 0x66FFFFFF);
		else if (game->map[var->y][var->x] == 'D')
			mlx_put_pixel(game->canvas.HUD, var->draw_x,
				var->draw_y, 0xFF0000FF);
		else
			mlx_put_pixel(game->canvas.HUD, var->draw_x,
				var->draw_y, 0x000000FF);
		var->cam_x++;
	}
}

void	render_player(t_data *game)
{
	mlx_put_pixel(game->canvas.HUD, 1503, 217, 0xFF3333FF);
	draw_line(game->canvas.HUD, 1503, 217, 1503
		+ cos(game->player.rotationA) * 30, 217
		+ sin(game->player.rotationA) * 30);
}

void	mini_map(t_data *game, double x_vis, double y_vis)
{
	t_var	var;

	var.x_dist = (x_vis * 2) * TILE_S + 1407;
	var.y_dist = (y_vis * 2) * TILE_S + 122;
	var.draw_x = 1408 - 1;
	var.draw_y = 122 - 1;
	var.cam_y = game->player.y - (y_vis * TILE_S);
	while (++var.draw_y <= var.y_dist)
	{
		var.cam_x = game->player.x - (x_vis * TILE_S);
		mini_map_helper(game, &var);
		var.cam_y++;
		var.draw_x = 1407;
		if (var.draw_y == var.y_dist - 1)
			var.draw_x = 1408;
	}
	render_player(game);
	game->canvas.HUD->enabled = true;
}
