/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   events.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ebennix <ebennix@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/05 13:53:35 by hasalam           #+#    #+#             */
/*   Updated: 2023/12/05 21:02:41 by ebennix          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/cub3d.h"

void	mouse_event(double x, double y, void *param)
{
	static int	i;
	t_data		*game;

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

void	mouse_click(mouse_key_t b, action_t a, modifier_key_t m, void *p)
{
	t_data	*game;

	game = p;
	(void)m;
	if (b == MLX_MOUSE_BUTTON_LEFT && a == MLX_PRESS)
		game->canvas.gun_shoot = true;
}

void	open_door(t_data *game)
{
	double	p_x;
	double	p_y;
	int		x;
	int		y;

	p_x = game->player.x + (cos(game->player.rotationA) * 20);
	p_y = game->player.y + (sin(game->player.rotationA) * 20);
	x = floor(p_x / TILE_S);
	y = floor(p_y / TILE_S);
	if (game->map[y][x] == 'D')
	{
		game->frames = 0;
		game->map[y][x] = '0';
	}
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

void	key_events(mlx_key_data_t keycode, t_data *game)
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
