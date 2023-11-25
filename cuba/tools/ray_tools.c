/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ray_tools.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ebennix <ebennix@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/25 01:50:47 by ebennix           #+#    #+#             */
/*   Updated: 2023/11/25 01:51:33 by ebennix          ###   ########.fr       */
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

int check_walls1(t_Player *player, float px, float py)
{
	(void)player;
	if (px < 0 || px > WIDTH || py < 0 || py > HEIGHT)
		return 0;
	float mapgridX = floor(px / TILE_S);
	float mapgridY = floor(py / TILE_S);
	if (map[(int)mapgridY][(int)mapgridX] != 0 || (map[(int)mapgridY][(int)(player->x / TILE_S)] && map[(int)(player->y / TILE_S)][(int)mapgridX]))
		return (1);
	return (0);
}
int check_walls2(t_Player *player, float px, float py)
{
	(void)player;
	if (px < 0 || px > WIDTH || py < 0 || py > HEIGHT)
		return 0;
	float mapgridX = floor(px / TILE_S);
	float mapgridY = floor(py / TILE_S);
	return (map[(int)mapgridY][(int)mapgridX] != 0);
}

float	distancebetweenPoints(float x1, float y1, float x2, float y2)
{
	return sqrt(((x2 - x1) * (x2 - x1)) + ((y2 - y1) * (y2 - y1)));
}
