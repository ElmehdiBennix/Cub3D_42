/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw_tools.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ebennix <ebennix@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/25 01:35:01 by ebennix           #+#    #+#             */
/*   Updated: 2023/11/27 04:55:03 by ebennix          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/cub3d.h"

void draw_line(mlx_image_t *img, float x0, float y0, float x1, float y1)
{
	float dx;
	float dy;
	float step;
	float x;
	float y;
	int i ;

	i = 0;

	dx = (x1 - x0);
	dy = (y1 - y0);

	step = fabsf(dx) > fabsf(dy) ? fabsf(dx) : fabsf(dy);

	dx = dx / step;
	dy = dy / step;

	x = x0;
	y = y0;
	while (i < step)
	{
		mlx_put_pixel(img, x, y, 0xFF00B3FF);
		x += dx;
		y += dy;
		i++;
	}
}

void draw_rectangle(mlx_image_t *img, int h, int w, int color, int tile)
{
	int i = h;
	while (i < h + tile)
	{
		int j = w;
		while (j < w + tile)
		{
			mlx_put_pixel(img, j * MINIMAP, i * MINIMAP, color);
			j++;
		}
		i++;
	}
}