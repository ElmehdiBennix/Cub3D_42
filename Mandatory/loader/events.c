/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   events.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ebennix <ebennix@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/05 13:53:35 by hasalam           #+#    #+#             */
/*   Updated: 2023/12/06 17:02:02 by ebennix          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/cub3d.h"

void	walk_d_and_turn_d(mlx_key_data_t keycode, t_data *game)
{
	if (keycode.key == MLX_KEY_W && keycode.action == MLX_PRESS)
		game->player.walk_d = 1;
	else if (keycode.key == MLX_KEY_W && keycode.action == MLX_RELEASE)
		game->player.walk_d = 0;
	else if (keycode.key == MLX_KEY_S && keycode.action == MLX_PRESS)
		game->player.walk_d = -1;
	else if (keycode.key == MLX_KEY_S && keycode.action == MLX_RELEASE)
		game->player.walk_d = 0;
	else if (keycode.key == MLX_KEY_RIGHT && keycode.action == MLX_PRESS)
		game->player.turn_d = 1;
	else if (keycode.key == MLX_KEY_RIGHT && keycode.action == MLX_RELEASE)
		game->player.turn_d = 0;
	else if (keycode.key == MLX_KEY_LEFT && keycode.action == MLX_PRESS)
		game->player.turn_d = -1;
	else if (keycode.key == MLX_KEY_LEFT && keycode.action == MLX_RELEASE)
		game->player.turn_d = 0;
}

void	key_events(mlx_key_data_t keycode, t_data *game)
{
	if (keycode.key == MLX_KEY_ESCAPE)
		exit(1);
	walk_d_and_turn_d(keycode, game);
	if (keycode.key == MLX_KEY_D && keycode.action == MLX_PRESS)
		game->player.side_w = 1;
	else if (keycode.key == MLX_KEY_D && keycode.action == MLX_RELEASE)
		game->player.side_w = 0;
	else if (keycode.key == MLX_KEY_A && keycode.action == MLX_PRESS)
		game->player.side_w = -1;
	else if (keycode.key == MLX_KEY_A && keycode.action == MLX_RELEASE)
		game->player.side_w = 0;
}
