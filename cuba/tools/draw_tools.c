/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw_tools.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ebennix <ebennix@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/25 01:35:01 by ebennix           #+#    #+#             */
/*   Updated: 2023/12/01 20:02:24 by ebennix          ###   ########.fr       */
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
