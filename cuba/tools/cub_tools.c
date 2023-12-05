/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub_tools.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ebennix <ebennix@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/25 01:34:24 by ebennix           #+#    #+#             */
/*   Updated: 2023/12/05 18:44:34 by ebennix          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/cub3d.h"

int	get_rgba(int r, int g, int b, int a)
{
	return (r << 24 | g << 16 | b << 8 | a);
}

int	ft_get_color(int i, int x, int y, t_data *game)
{
	int	r;
	int	g;
	int	b;
	int	a;

	a = 255;
	r = game->rays[i].text->pixels[(y * (game->rays[i].text->width * 4)) + (x
			* 4)];
	g = game->rays[i].text->pixels[(y * (game->rays[i].text->width * 4)) + (x
			* 4) + 1];
	b = game->rays[i].text->pixels[(y * (game->rays[i].text->width * 4)) + (x
			* 4) + 2];
	// color = &game.text1->pixels[(y * (game.text1->width * 4)) + (x * 4)];
	// printf("%d\n",player);
	// exit(0);
	// return (get_rgba(color[0], color[1], color[2], color[3]));
	return (get_rgba(r, g, b, a));
}

void	update_state(t_data *game)
{
	t_var	var;

	game->player.rotationA += game->player.turnD * game->player.turnS;
	var.move_step = game->player.walkD * game->player.walkS;
	var.newp_x = cos(game->player.rotationA) * var.move_step;
	var.newp_y = sin(game->player.rotationA) * var.move_step;
	var.px = game->player.x + var.newp_x;
	var.py = game->player.y + var.newp_y;
	if (!check_walls(game, var.px, var.py, 0))
	{
		game->player.x = var.px;
		game->player.y = var.py;
	}
	var.tmp = game->player.rotationA + game->player.sideW * game->player.turnS;
	var.move_step = game->player.sideW * game->player.walkS;
	var.newp_x = cos(var.tmp + (90 * (M_PI / 180))) * var.move_step;
	var.newp_y = sin(var.tmp + (90 * (M_PI / 180))) * var.move_step;
	var.px = game->player.x + var.newp_x;
	var.py = game->player.y + var.newp_y;
	if (!check_walls(game, var.px, var.py, 0))
	{
		game->player.x = var.px;
		game->player.y = var.py;
	}
}
