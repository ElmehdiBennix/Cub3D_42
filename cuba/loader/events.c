/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   events.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ebennix <ebennix@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/21 09:06:02 by ebennix           #+#    #+#             */
/*   Updated: 2023/11/25 01:39:44 by ebennix          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/cub3d.h"

void ft_update(t_Player *player)
{
	player->rotationA += player->turnD * player->turnS;
	float movestep = player->walkD * player->walkS;
	float newplayerX = cos(player->rotationA) * movestep;
	float newplayerY = sin(player->rotationA) * movestep;
	float px = player->x + newplayerX;
	float py = player->y + newplayerY;
	if (!check_walls1(player, px, py))
	{
		player->x = px;
		player->y = py;
	}
	float tmp = player->rotationA + player->sideW * player->turnS;
	movestep = player->sideW * player->walkS;
	newplayerX = cos(tmp + (90 * (M_PI / 180))) * movestep;
	newplayerY = sin(tmp + (90 * (M_PI / 180))) * movestep;
	px = player->x + newplayerX;
	py = player->y + newplayerY;
	if (!check_walls1(player, px, py))
	{
		player->x = px;
		player->y = py;
	}
}

void ft_mouse(void* param)
{
	t_Player *player = param;
	static int i;
	mlx_get_mouse_pos(player->mlx, &player->mouseX, &player->mouseY);
	if (i++ == 0)
		player->mouseX = 500;
	player->rotationA += (float)(player->mouseX - 500) / 500;
	mlx_set_mouse_pos(player->mlx, 500, 500);
}

void ft_key(mlx_key_data_t keycode, void *param)
{
	t_Player *player = param;

	if(keycode.key == MLX_KEY_ESCAPE)
		exit(1);
	if (keycode.key == MLX_KEY_W && (keycode.action == MLX_PRESS || keycode.action == MLX_REPEAT))
		player->walkD = 1;
	if (keycode.key == MLX_KEY_W && keycode.action == MLX_RELEASE)
		player->walkD = 0;
	if (keycode.key == MLX_KEY_S && (keycode.action == MLX_PRESS || keycode.action == MLX_REPEAT))
		player->walkD = -1;
	if (keycode.key == MLX_KEY_S && keycode.action == MLX_RELEASE)
		player->walkD = 0;
	if (keycode.key == MLX_KEY_RIGHT && (keycode.action == MLX_PRESS || keycode.action == MLX_REPEAT))
		player->turnD = 1;
	if (keycode.key == MLX_KEY_RIGHT && keycode.action == MLX_RELEASE)
		player->turnD = 0;
	if (keycode.key == MLX_KEY_LEFT && (keycode.action == MLX_PRESS || keycode.action == MLX_REPEAT))
		player->turnD = -1;
	if (keycode.key == MLX_KEY_LEFT && keycode.action == MLX_RELEASE)
		player->turnD = 0;
	if (keycode.key == MLX_KEY_D && (keycode.action == MLX_PRESS || keycode.action == MLX_REPEAT))
		player->sideW = 1;
	if (keycode.key == MLX_KEY_D && keycode.action == MLX_RELEASE)
		player->sideW = 0;
	if (keycode.key == MLX_KEY_A && (keycode.action == MLX_PRESS || keycode.action == MLX_REPEAT))
		player->sideW = -1;
	if (keycode.key == MLX_KEY_A && keycode.action == MLX_RELEASE)
		player->sideW = 0;
}
