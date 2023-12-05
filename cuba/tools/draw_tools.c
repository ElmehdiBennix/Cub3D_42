/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw_tools.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hasalam <hasalam@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/25 01:35:01 by ebennix           #+#    #+#             */
/*   Updated: 2023/12/05 20:18:14 by hasalam          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/cub3d.h"

void	draw_line(mlx_image_t *img, struct s_draw_line *arg)
{
	struct s_d_line	draw;

	draw.i = 0;
	draw.dx = (arg->x1 - arg->x0);
	draw.dy = (arg->y1 - arg->y0);
	if (fabsf(draw.dx) > fabsf(draw.dy))
		draw.step = fabsf(draw.dx);
	else
		draw.step = fabsf(draw.dy);
	draw.dx = draw.dx / draw.step;
	draw.dy = draw.dy / draw.step;
	draw.x = arg->x0;
	draw.y = arg->y0;
	while (draw.i < draw.step)
	{
		mlx_put_pixel(img, draw.x, draw.y, 0xFF00B3FF);
		draw.x += draw.dx;
		draw.y += draw.dy;
		draw.i++;
	}
}
