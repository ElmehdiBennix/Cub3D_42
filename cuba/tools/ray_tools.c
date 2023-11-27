/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ray_tools.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ebennix <ebennix@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/25 01:50:47 by ebennix           #+#    #+#             */
/*   Updated: 2023/11/27 05:11:10 by ebennix          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/cub3d.h"

float	normalizeAngle(float angle)
{
	angle = fmod(angle, (2 * M_PI));
	if (angle < 0)
		angle = (2 * M_PI) + angle;
	return angle;
}

int check_walls1(t_data *game, float px, float py)
{
	if (px < 0 || px > WIDTH || py < 0 || py > HEIGHT)
		return 0;
	float mapgridX = floor(px / TILE_S);
	float mapgridY = floor(py / TILE_S);
	if (game->map[(int)mapgridY][(int)mapgridX] != '0' || (game->map[(int)mapgridY][(int)(game->player.x / TILE_S)] && game->map[(int)(game->player.y / TILE_S)][(int)mapgridX]))
		return (1);
	return (0);
}
int check_walls2(t_data *game, float px, float py)
{
	if (px < 0 || px > WIDTH || py < 0 || py > HEIGHT)
		return 0;
	float mapgridX = floor(px / TILE_S);
	float mapgridY = floor(py / TILE_S);
	if (game->map[(int)mapgridY][(int)mapgridX] != '0')
		return (1);
	return (0);
}

float	distancebetweenPoints(float x1, float y1, float x2, float y2)
{
	return sqrt(((x2 - x1) * (x2 - x1)) + ((y2 - y1) * (y2 - y1)));
}
