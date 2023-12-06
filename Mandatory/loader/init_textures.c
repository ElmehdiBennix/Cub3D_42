/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_textures.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ebennix <ebennix@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/08 20:29:40 by ebennix           #+#    #+#             */
/*   Updated: 2023/12/06 16:58:32 by ebennix          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/cub3d.h"

bool	init_textures(char *content, mlx_texture_t **texture)
{
	*texture = mlx_load_png(content);
	if (!(*texture))
		return (close(2), false);
	return (true);
}

void	init_images(t_data *game)
{
	game->canvas.world_3d = mlx_new_image(game->mlx, WIDTH, HEIGHT);
	if (!game->canvas.world_3d || mlx_image_to_window(game->mlx,
			game->canvas.world_3d, 0, 0) == -1)
		return (free2d(game->map), free_texture(game), ft_error());
	game->canvas.hud = mlx_new_image(game->mlx, WIDTH, HEIGHT);
	if (!game->canvas.hud || mlx_image_to_window(game->mlx,
			game->canvas.hud, 0, 0) == -1)
		return (free2d(game->map), free_texture(game), ft_error());
	game->canvas.hud->enabled = false;
}
