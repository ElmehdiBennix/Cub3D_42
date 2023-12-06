/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   raycast_helper.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hasalam <hasalam@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/05 02:02:09 by hasalam           #+#    #+#             */
/*   Updated: 2023/12/06 01:04:26 by hasalam          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/cub3d.h"

void	cast_ray_helper1(t_data *game, struct s_cast_ray *var, float ray_a)
{
	if (ray_a > 0 && ray_a < M_PI)
		var->is_ray_fac_d = true;
	else
		var->is_ray_fac_d = false;
	var->is_ray_fac_u = !var->is_ray_fac_d;
	if (ray_a < (0.5 * M_PI) || ray_a > (1.5 * M_PI))
		var->is_ray_fac_r = true;
	else
		var->is_ray_fac_r = false;
	var->is_ray_fac_l = !var->is_ray_fac_r;
	var->found_horzw_hit = false;
	var->horz_wall_hit_x = 0;
	var->horz_wall_hit_y = 0;
	var->horz_wall_contnt = 0;
	var->y_intercept = floor(game->player.y / TILE_S) * TILE_S;
	if (var->is_ray_fac_d == true)
		var->y_intercept += TILE_S;
	var->x_intercept = game->player.x + (var->y_intercept - game->player.y)
		/ tan(ray_a);
	var->ystep = TILE_S;
	if (var->is_ray_fac_u == true)
		var->ystep *= -1;
	var->xstep = TILE_S / tan(ray_a);
}

void	cast_ray_helper2(t_data *game, struct s_cast_ray *var)
{
	while (var->nxt_horz_touch_x >= 0
		&& var->nxt_horz_touch_x <= game->map_width * TILE_S
		&& var->nxt_horz_touch_y >= 0
		&& var->nxt_horz_touch_y < game->map_height * TILE_S)
	{
		var->check_x = var->nxt_horz_touch_x;
		if (var->is_ray_fac_u == true)
			var->check_y = var->nxt_horz_touch_y - 1;
		else
			var->check_y = var->nxt_horz_touch_y;
		if (check_walls(game, var->check_x, var->check_y, 1))
		{
			var->horz_wall_hit_x = var->nxt_horz_touch_x;
			var->horz_wall_hit_y = var->nxt_horz_touch_y;
			var->horz_wall_contnt = game->map[(int)floor(var->check_y / TILE_S)]
			[(int)floor(var->check_x / TILE_S)];
			var->found_horzw_hit = true;
			break ;
		}
		else
		{
			var->nxt_horz_touch_x += var->xstep;
			var->nxt_horz_touch_y += var->ystep;
		}
	}
}

void	cast_ray_helper3(t_data *game, struct s_cast_ray *var, float ray_a)
{
	var->found_vertw_hit = false;
	var->vert_wall_hit_x = 0;
	var->vert_wall_hit_y = 0;
	var->vert_wall_contnt = 0;
	var->x_intercept = floor(game->player.x / TILE_S) * TILE_S;
	if (var->is_ray_fac_r == true)
		var->x_intercept += TILE_S;
	var->y_intercept = game->player.y + (var->x_intercept - game->player.x)
		* tan(ray_a);
	var->xstep = TILE_S;
	if (var->is_ray_fac_l == true)
		var->xstep *= -1;
	var->ystep = TILE_S * tan(ray_a);
	if (var->is_ray_fac_u == true && var->ystep > 0)
		var->ystep *= -1;
	else if (var->is_ray_fac_d == true && var->ystep < 0)
		var->ystep *= -1;
	var->nxt_vert_touch_x = var->x_intercept;
	var->nxt_vert_touch_y = var->y_intercept;
}

void	cast_ray_helper4(t_data *game, struct s_cast_ray *var)
{
	while (var->nxt_vert_touch_x >= 0
		&& var->nxt_vert_touch_x <= game->map_width * TILE_S
		&& var->nxt_vert_touch_y >= 0
		&& var->nxt_vert_touch_y < game->map_height * TILE_S)
	{
		if (var->is_ray_fac_l)
			var->check_x = var->nxt_vert_touch_x - 1;
		else
			var->check_x = var->nxt_vert_touch_x;
		var->check_y = var->nxt_vert_touch_y;
		if (check_walls(game, var->check_x, var->check_y, 1))
		{
			var->vert_wall_hit_x = var->nxt_vert_touch_x;
			var->vert_wall_hit_y = var->nxt_vert_touch_y;
			var->vert_wall_contnt = game->map[(int)floor(var->check_y / TILE_S)]
			[(int)floor(var->check_x / TILE_S)];
			var->found_vertw_hit = true;
			break ;
		}
		else
		{
			var->nxt_vert_touch_x += var->xstep;
			var->nxt_vert_touch_y += var->ystep;
		}
	}
}

void	cast_ray_helper5(t_data *game, struct s_cast_ray *var)
{
	if (var->found_horzw_hit == true)
		var->horz_hit_dist = distancebetween_points(game->player.x,
				game->player.y, var->horz_wall_hit_x, var->horz_wall_hit_y);
	else
		var->horz_hit_dist = (float)INT_MAX;
	if (var->found_vertw_hit == true)
		var->vert_hit_dist = distancebetween_points(game->player.x,
				game->player.y, var->vert_wall_hit_x, var->vert_wall_hit_y);
	else
		var->vert_hit_dist = (float)INT_MAX;
}
