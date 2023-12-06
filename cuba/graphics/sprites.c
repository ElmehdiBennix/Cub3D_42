/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sprites.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hasalam <hasalam@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/01 00:07:35 by ebennix           #+#    #+#             */
/*   Updated: 2023/12/06 01:07:23 by hasalam          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/cub3d.h"

void	draw_faces(t_data *game)
{
	if (game->frames % 80 == 0)
		game->canvas.face_idle = !game->canvas.face_idle;
	if (game->canvas.gun_shoot == true)
		game->canvas.faces[5]->enabled = true;
	else if (game->player.turn_d == 1
		|| game->player.mouse_x > (WIDTH / 2) + 20)
		game->canvas.faces[4]->enabled = true;
	else if (game->player.turn_d == -1
		|| game->player.mouse_x < (WIDTH / 2) - 20)
		game->canvas.faces[3]->enabled = true;
	else if (game->player.walk_d == 1 || game->player.walk_d == -1)
		game->canvas.faces[2]->enabled = true;
	else
	{
		if (game->canvas.face_idle == false)
			game->canvas.faces[0]->enabled = true;
		else
			game->canvas.faces[1]->enabled = true;
	}
}

void	draw_gun_helper(t_data *game, struct s_draw_gun *var, int flag)
{
	if (flag == 0)
	{
		var->i = -1;
		while (++var->i < 7)
		{
			if (var->i < 5)
				var->animat[var->i] = var->i + 1;
			else
				var->animat[var->i] = 5 - (var->i - 4);
		}
	}
	else
	{
		if (game->canvas.gun_running == false && game->canvas.gun_x < 670)
			game->canvas.gun_x += 4;
		else
		{
			game->canvas.gun_running = true;
			game->canvas.gun_x -= 4;
			if (game->canvas.gun_x < 570)
				game->canvas.gun_running = false;
		}
		game->canvas.gun[0]->instances->x = game->canvas.gun_x;
	}
}

void	draw_gun(t_data *game)
{
	struct s_draw_gun	var;
	static int			play;

	draw_gun_helper(game, &var, 0);
	if (game->canvas.gun_shoot == true)
	{
		game->canvas.gun[var.animat[play]]->enabled = true;
		game->canvas.gun[var.animat[play]]->instances->x = game->canvas.gun_x;
		if (game->frames % 8 == 0)
		{
			game->canvas.gun[var.animat[play]]->enabled = true;
			play++;
			if (play == 7)
			{
				play = 0;
				game->canvas.gun_shoot = false;
			}
		}
		return ;
	}
	else if (game->player.walk_d == 1 || game->player.walk_d == -1
		|| game->player.side_w == 1 || game->player.side_w == -1)
		draw_gun_helper(game, &var, 1);
	game->canvas.gun[0]->enabled = true;
}
