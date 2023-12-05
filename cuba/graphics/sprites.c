/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sprites.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hasalam <hasalam@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/01 00:07:35 by ebennix           #+#    #+#             */
/*   Updated: 2023/12/05 18:17:53 by hasalam          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/cub3d.h"

void	draw_faces(t_data *game)
{
	if (game->frames % 80 == 0)
		game->canvas.face_idle = !game->canvas.face_idle;
	if (game->canvas.gun_shoot == true)
		game->canvas.Faces[5]->enabled = true;
	else if (game->player.turnD == 1 || game->player.mouseX > (WIDTH / 2) + 20)
		game->canvas.Faces[4]->enabled = true;
	else if (game->player.turnD == -1 || game->player.mouseX < (WIDTH / 2) - 20)
		game->canvas.Faces[3]->enabled = true;
	else if (game->player.walkD == 1 || game->player.walkD == -1)
		game->canvas.Faces[2]->enabled = true;
	else
	{
		if (game->canvas.face_idle == false)
			game->canvas.Faces[0]->enabled = true;
		else
			game->canvas.Faces[1]->enabled = true;
	}
}

void	draw_gun_helper(t_data *game, t_var *var, int flag)
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
	static int	play;
	t_var		var;

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
	else if (game->player.walkD == 1 || game->player.walkD == -1
		|| game->player.sideW == 1 || game->player.sideW == -1)
		draw_gun_helper(game, &var, 1);
	game->canvas.gun[0]->enabled = true;
}
