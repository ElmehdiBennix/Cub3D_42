/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sprites.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ebennix <ebennix@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/01 00:07:35 by ebennix           #+#    #+#             */
/*   Updated: 2023/12/01 19:53:47 by ebennix          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/cub3d.h"

void draw_faces(t_data *game)
{
	if (game->frames % 80 == 0)
		game->canvas.face_idle = !game->canvas.face_idle;
	if (game->canvas.gun_shoot == true)
		game->canvas.Faces[5]->enabled = true;
	else if (game->player.turnD == 1 || game->player.mouseX > 520)
		game->canvas.Faces[4]->enabled = true;
	else if (game->player.turnD == -1 || game->player.mouseX < 480)
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

void draw_gun(t_data *game)
{
	static int play = 0;
	int animation[7] = {1,2,3,4,5,4,3};

	if (game->canvas.gun_shoot == true)
	{
		game->canvas.gun[animation[play]]->enabled = true;
		game->canvas.gun[animation[play]]->instances->x = game->canvas.gun_x;
		if (game->frames % 8 == 0)
		{
			game->canvas.gun[animation[play]]->enabled = true;
			play++;
			if (play == 7)
			{
				play = 0;
				game->canvas.gun_shoot = false;
			}
		}
		return ;
	}
	else if (game->player.walkD == 1 || game->player.walkD == -1 || game->player.sideW == 1 || game->player.sideW == -1)
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
	game->canvas.gun[0]->enabled = true;
}
