/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw3d.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hasalam <hasalam@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/25 01:35:18 by ebennix           #+#    #+#             */
/*   Updated: 2023/12/06 00:59:35 by hasalam          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/cub3d.h"
#include <stdint.h>

void	generate3d_map_helper2(t_data *game, struct s_draw_3d *var,
	uint32_t color)
{
	var->y = var->wall_bot_pixel - 1;
	while (++(var->y) < var->wall_top_pixel)
		mlx_put_pixel(game->canvas.world_3d, var->i, var->y,
			get_rgba(game->c_floor.r, game->c_floor.g,
				game->c_floor.b, 255));
	if (game->rays[var->i].was_hit_vertical)
		var->txt_offset_x = fmodf(game->rays[var->i].wall_hit_y, TILE_S)
			* ((float)game->rays[var->i].text->width / TILE_S);
	else
		var->txt_offset_x = fmodf(game->rays[var->i].wall_hit_x, TILE_S)
			* ((float)game->rays[var->i].text->width / TILE_S);
	var->y = var->wall_top_pixel - 1;
	while (++var->y < var->wall_bot_pixel)
	{
		var->dist_from_top = var->y + (var->wall_strip_h / 2) - (HEIGHT / 2);
		var->txt_offset_y = var->dist_from_top
			* ((float)game->rays[var->i].text->height / var->wall_strip_h);
		color = ft_get_color(var->i, var->txt_offset_x,
				var->txt_offset_y, game);
		mlx_put_pixel(game->canvas.world_3d, var->i, var->y, color);
	}
	var->y = var->wall_bot_pixel - 1;
}

void	generate3d_map_helper1(t_data *game, struct s_draw_3d *var)
{
	uint32_t	color;

	while (++var->y < var->wall_top_pixel)
		mlx_put_pixel(game->canvas.world_3d, var->i, var->y,
			get_rgba(game->c_floor.r, game->c_floor.g, game->c_floor.b, 255));
	if (game->rays[var->i].was_hit_vertical)
		var->txt_offset_x = fmodf(game->rays[var->i].wall_hit_y, TILE_S)
			* ((float)game->rays[var->i].text->width / TILE_S);
	else
		var->txt_offset_x = fmodf(game->rays[var->i].wall_hit_x, TILE_S)
			* ((float)game->rays[var->i].text->width / TILE_S);
	var->y = var->wall_top_pixel - 1;
	while (++var->y < var->wall_bot_pixel)
	{
		var->dist_from_top = var->y + (var->wall_strip_h / 2) - (HEIGHT / 2);
		var->txt_offset_y = var->dist_from_top
			* ((float)game->rays[var->i].text->height / var->wall_strip_h);
		color = ft_get_color(var->i, var->txt_offset_x,
				var->txt_offset_y, game);
		mlx_put_pixel(game->canvas.world_3d, var->i, var->y, color);
	}
	generate3d_map_helper2(game, var, color);
}

void	generate3d_map(t_data *game)
{
	struct s_draw_3d	var;

	var.i = -1;
	while (++var.i < NUM_RAYS)
	{
		var.corr_dist = game->rays[var.i].distance
			* cos(game->rays[var.i].ray_angle - game->player.rotation_a);
		var.dist_proj = ((float)WIDTH / 2) / tan(game->player.fov_angle / 2);
		var.proj_wall_h = (TILE_S / var.corr_dist) * var.dist_proj;
		var.wall_strip_h = (int)var.proj_wall_h;
		var.wall_top_pixel = (HEIGHT / 2) - (var.wall_strip_h / 2);
		var.wall_bot_pixel = (HEIGHT / 2) + (var.wall_strip_h / 2);
		var.y = -1;
		if (var.wall_top_pixel < 0)
			var.wall_top_pixel = 0;
		if (var.wall_bot_pixel > HEIGHT)
			var.wall_bot_pixel = HEIGHT;
		generate3d_map_helper1(game, &var);
		while (++var.y < HEIGHT)
		{
			mlx_put_pixel(game->canvas.world_3d, var.i, var.y,
				get_rgba(game->c_ceiling.r, game->c_ceiling.g,
					game->c_ceiling.b, 255));
		}
	}
}
