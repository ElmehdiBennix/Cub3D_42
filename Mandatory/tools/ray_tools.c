/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ray_tools.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hasalam <hasalam@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/25 01:50:47 by ebennix           #+#    #+#             */
/*   Updated: 2023/12/05 23:33:19 by hasalam          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/cub3d.h"

float	normalize_angle(float angle)
{
	angle = fmod(angle, (2 * M_PI));
	if (angle < 0)
		angle = (2 * M_PI) + angle;
	return (angle);
}

int	check_walls(t_data *game, float px, float py, int flag)
{
	float	mapgrid_x;
	float	mapgrid_y;

	if (px < 0 || px > game->map_width * TILE_S || py < 0
		|| py > game->map_height * TILE_S)
		return (0);
	mapgrid_x = floor(px / TILE_S);
	mapgrid_y = floor(py / TILE_S);
	if (flag == 0)
	{
		if (game->map[(int)mapgrid_y][(int)mapgrid_x] != '0'
			|| (game->map[(int)mapgrid_y][(int)(game->player.x / TILE_S)] == '1'
				&& game->map[(int)(game->player.y
					/ TILE_S)][(int)mapgrid_x] == '1'))
			return (1);
	}
	else if (flag == 1)
	{
		if (game->map[(int)mapgrid_y][(int)mapgrid_x] != '0')
			return (1);
	}
	return (0);
}

float	distancebetween_points(float x1, float y1, float x2, float y2)
{
	return (sqrt(((x2 - x1) * (x2 - x1)) + ((y2 - y1) * (y2 - y1))));
}

void	add_door(t_data *game, int i, int j)
{
	if (game->map[i + 1][j] == '1' && game->map[i - 1][j] == '1'
		&& game->map[i][j + 1] == '0' && game->map[i][j - 1] == '0')
		game->map[i][j] = 'D';
	if (game->map[i + 1][j] == '0' && game->map[i - 1][j] == '0'
		&& game->map[i][j + 1] == '1' && game->map[i][j - 1] == '1')
		game->map[i][j] = 'D';
}
