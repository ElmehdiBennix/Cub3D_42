/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   events.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hasalam <hasalam@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/05 13:53:35 by hasalam           #+#    #+#             */
/*   Updated: 2023/12/05 13:53:37 by hasalam          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/cub3d.h"

void mouse_event(double x, double y, void *param)
{
	static int i;
	t_data *game;

	(void)x;
	(void)y;
	game = param;
	mlx_get_mouse_pos(game->mlx, &game->player.mouseX, &game->player.mouseY);
	if (i++ == 0)
		game->player.mouseX = WIDTH / 2;
	game->player.rotationA += (float)(game->player.mouseX - ((float)WIDTH / 2))
		/ ((float)WIDTH / 2);
	mlx_set_mouse_pos(game->mlx, (WIDTH / 2), (HEIGHT / 2));
}

void	mouse_click(mouse_key_t b, action_t a, modifier_key_t m, void* p)
{
	t_data *game = p;
	(void)m;
	if (b == MLX_MOUSE_BUTTON_LEFT && a == MLX_PRESS)
		game->canvas.gun_shoot = true;
}

void 	update_state(t_data *game)
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
	var.px = game->player.x +var. newp_x;
	var.py = game->player.y + var.newp_y;
	if (!check_walls(game, var.px, var.py, 0))
	{
		game->player.x = var.px;
		game->player.y = var.py;
	}
}

void open_door(t_data *game)
{	
	double p_X = game->player.x + (cos(game->player.rotationA) * 20);
	double p_Y = game->player.y + (sin(game->player.rotationA) * 20);

	int X = floor(p_X / TILE_S);
	int Y = floor(p_Y / TILE_S);
	if (game->map[Y][X] == 'D')
		game->map[Y][X] = '0';
}
void	walk_d_and_turn_d(mlx_key_data_t keycode, t_data *game)
{
	if (keycode.key == MLX_KEY_W && keycode.action == MLX_PRESS)
		game->player.walkD = 1;
	else if (keycode.key == MLX_KEY_W && keycode.action == MLX_RELEASE)
		game->player.walkD = 0;
	else if (keycode.key == MLX_KEY_S && keycode.action == MLX_PRESS)
		game->player.walkD = -1;
	else if (keycode.key == MLX_KEY_S && keycode.action == MLX_RELEASE)
		game->player.walkD = 0;
	else if (keycode.key == MLX_KEY_RIGHT && keycode.action == MLX_PRESS)
		game->player.turnD = 1;
	else if (keycode.key == MLX_KEY_RIGHT && keycode.action == MLX_RELEASE)
		game->player.turnD = 0;
	else if (keycode.key == MLX_KEY_LEFT && keycode.action == MLX_PRESS)
		game->player.turnD = -1;
	else if (keycode.key == MLX_KEY_LEFT && keycode.action == MLX_RELEASE)
		game->player.turnD = 0;
}

void key_events(mlx_key_data_t keycode, t_data *game)
{
	if (keycode.key == MLX_KEY_ESCAPE)
		exit(1);
	walk_d_and_turn_d(keycode, game);
	if (keycode.key == MLX_KEY_D && keycode.action == MLX_PRESS)
		game->player.sideW = 1;
	else if (keycode.key == MLX_KEY_D && keycode.action == MLX_RELEASE)
		game->player.sideW = 0;
	else if (keycode.key == MLX_KEY_A && keycode.action == MLX_PRESS)
		game->player.sideW = -1;
	else if (keycode.key == MLX_KEY_A && keycode.action == MLX_RELEASE)
		game->player.sideW = 0;
	else if (keycode.key == MLX_KEY_LEFT_SHIFT && keycode.action == MLX_PRESS)
		game->canvas.gun_shoot = true;
	else if (keycode.key == MLX_KEY_B && keycode.action == MLX_PRESS)
		open_door(game);
}