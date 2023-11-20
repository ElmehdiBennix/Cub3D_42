/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_images.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ebennix <ebennix@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/08 20:29:40 by ebennix           #+#    #+#             */
/*   Updated: 2023/11/21 00:14:44 by ebennix          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/cub3d.h"


void    init_textures(t_data    *game)
{
    game->South.texture = mlx_load_png(game->South.content_Nullable);
	if (!game->South.texture)
		ft_error();
    game->West.texture = mlx_load_png(game->West.content_Nullable);
	if (!game->West.texture)
		ft_error();
    game->North.texture = mlx_load_png(game->North.content_Nullable);
	if (!game->North.texture)
		ft_error();
    game->East.texture = mlx_load_png(game->East.content_Nullable);
	if (!game->East.texture)
		ft_error();
}