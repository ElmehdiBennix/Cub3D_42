/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   raycasting.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ebennix <ebennix@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/05 13:49:46 by hasalam           #+#    #+#             */
/*   Updated: 2023/12/06 17:04:57 by ebennix          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/cub3d.h"

void	cast_ray_helper6(t_data *game, struct s_cast_ray *var, int sId)
{
	if (var->vert_hit_dist < var->horz_hit_dist)
	{
		game->rays[sId].distance = var->vert_hit_dist;
		game->rays[sId].wall_hit_x = var->vert_wall_hit_x;
		game->rays[sId].wall_hit_y = var->vert_wall_hit_y;
		game->rays[sId].wall_hit_content = var->vert_wall_contnt;
		game->rays[sId].was_hit_vertical = true;
		if (game->rays[sId].is_ray_facing_right)
			game->rays[sId].text = game->east.texture;
		else
			game->rays[sId].text = game->west.texture;
	}
	else
	{
		game->rays[sId].distance = var->horz_hit_dist;
		game->rays[sId].wall_hit_x = var->horz_wall_hit_x;
		game->rays[sId].wall_hit_y = var->horz_wall_hit_y;
		game->rays[sId].wall_hit_content = var->horz_wall_contnt;
		game->rays[sId].was_hit_vertical = false;
		if (game->rays[sId].is_ray_facing_up)
			game->rays[sId].text = game->north.texture;
		else
			game->rays[sId].text = game->south.texture;
	}
}

void	cast_ray(float ray_a, int sId, t_data *game)
{
	struct s_cast_ray	var;

	ray_a = normalize_angle(ray_a);
	cast_ray_helper1(game, &var, ray_a);
	if (var.is_ray_fac_l == true && var.xstep > 0)
		var.xstep *= -1;
	else if (var.is_ray_fac_r == true && var.xstep < 0)
		var.xstep *= -1;
	var.nxt_horz_touch_x = var.x_intercept;
	var.nxt_horz_touch_y = var.y_intercept;
	cast_ray_helper2(game, &var);
	cast_ray_helper3(game, &var, ray_a);
	cast_ray_helper4(game, &var);
	cast_ray_helper5(game, &var);
	cast_ray_helper6(game, &var, sId);
	game->rays[sId].ray_angle = ray_a;
	game->rays[sId].is_ray_facing_down = var.is_ray_fac_d;
	game->rays[sId].is_ray_facing_up = var.is_ray_fac_u;
	game->rays[sId].is_ray_facing_left = var.is_ray_fac_l;
	game->rays[sId].is_ray_facing_right = var.is_ray_fac_r;
}

void	cast_all_rays(t_data *game)
{
	float	ray_a;
	int		i;

	ray_a = game->player.rotation_a - (game->player.fov_angle / 2);
	i = -1;
	while (++i < NUM_RAYS)
	{
		cast_ray(ray_a, i, game);
		ray_a += game->player.fov_angle / NUM_RAYS;
	}
}
