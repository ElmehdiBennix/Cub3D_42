/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw3d.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hasalam <hasalam@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/25 01:35:18 by ebennix           #+#    #+#             */
/*   Updated: 2023/12/05 18:30:23 by hasalam          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/cub3d.h"
#include <stdint.h>

void	generate3d_map_helper2(t_data *game, t_var *var, uint32_t color)
{
	var->y = var->wallBotPixel - 1;
	while (++(var->y) < var->wallTopPixel)
		mlx_put_pixel(game->canvas.world_3D, var->i, var->y,
			get_rgba(game->C_Floor.R, game->C_Floor.G, game->C_Floor.B, 255));
	if (game->rays[var->i].wasHitVertical)
		var->txtOffset_X = fmodf(game->rays[var->i].wallHitY, TILE_S)
			* ((float)game->rays[var->i].text->width / TILE_S);
	else
		var->txtOffset_X = fmodf(game->rays[var->i].wallHitX, TILE_S)
			* ((float)game->rays[var->i].text->width / TILE_S);
	var->y = var->wallTopPixel - 1;
	while (++var->y < var->wallBotPixel)
	{
		var->distFromTop = var->y + (var->wallStrip_H / 2) - (HEIGHT / 2);
		var->txtOffset_Y = var->distFromTop
			* ((float)game->rays[var->i].text->height / var->wallStrip_H);
		color = ft_get_color(var->i, var->txtOffset_X, var->txtOffset_Y, game);
		mlx_put_pixel(game->canvas.world_3D, var->i, var->y, color);
	}
	var->y = var->wallBotPixel - 1;
}

void	generate3d_map_helper1(t_data *game, t_var *var)
{
	uint32_t	color;

	while (++var->y < var->wallTopPixel)
		mlx_put_pixel(game->canvas.world_3D, var->i, var->y,
			get_rgba(game->C_Floor.R, game->C_Floor.G, game->C_Floor.B, 255));
	if (game->rays[var->i].wasHitVertical)
		var->txtOffset_X = fmodf(game->rays[var->i].wallHitY, TILE_S)
			* ((float)game->rays[var->i].text->width / TILE_S);
	else
		var->txtOffset_X = fmodf(game->rays[var->i].wallHitX, TILE_S)
			* ((float)game->rays[var->i].text->width / TILE_S);
	var->y = var->wallTopPixel - 1;
	while (++var->y < var->wallBotPixel)
	{
		var->distFromTop = var->y + (var->wallStrip_H / 2) - (HEIGHT / 2);
		var->txtOffset_Y = var->distFromTop
			* ((float)game->rays[var->i].text->height / var->wallStrip_H);
		color = ft_get_color(var->i, var->txtOffset_X, var->txtOffset_Y, game);
		mlx_put_pixel(game->canvas.world_3D, var->i, var->y, color);
	}
	generate3d_map_helper2(game, var, color);
}

void	generate3d_map(t_data *game)
{
	t_var	var;

	var.i = -1;
	while (++var.i < NUM_RAYS)
	{
		var.corrDist = game->rays[var.i].distance
			* cos(game->rays[var.i].ray_angle - game->player.rotationA);
		var.distProj = ((float)WIDTH / 2) / tan(FOV_ANGLE / 2);
		var.projWAll_H = (TILE_S / var.corrDist) * var.distProj;
		var.wallStrip_H = (int)var.projWAll_H;
		var.wallTopPixel = (HEIGHT / 2) - (var.wallStrip_H / 2);
		var.wallBotPixel = (HEIGHT / 2) + (var.wallStrip_H / 2);
		var.y = -1;
		if (var.wallTopPixel < 0)
			var.wallTopPixel = 0;
		if (var.wallBotPixel > HEIGHT)
			var.wallBotPixel = HEIGHT;
		generate3d_map_helper1(game, &var);
		while (++var.y < HEIGHT)
		{
			mlx_put_pixel(game->canvas.world_3D, var.i, var.y,
				get_rgba(game->C_Ceiling.R, game->C_Ceiling.G,
					game->C_Ceiling.B, 255));
		}
	}
}
