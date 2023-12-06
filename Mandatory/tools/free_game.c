/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free_game.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ebennix <ebennix@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/13 05:11:51 by ebennix           #+#    #+#             */
/*   Updated: 2023/12/06 16:59:32 by ebennix          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/cub3d.h"

void	free_fields(t_data *game)
{
	if (game->north.content_nullable)
		free(game->north.content_nullable);
	if (game->south.content_nullable)
		free(game->south.content_nullable);
	if (game->west.content_nullable)
		free(game->west.content_nullable);
	if (game->east.content_nullable)
		free(game->east.content_nullable);
	if (game->c_floor.content_nullable)
		free(game->c_floor.content_nullable);
	if (game->c_ceiling.content_nullable)
		free(game->c_ceiling.content_nullable);
}

void	free_texture(t_data *game)
{
	if (game->north.texture)
		mlx_delete_texture(game->north.texture);
	if (game->south.texture)
		mlx_delete_texture(game->south.texture);
	if (game->west.texture)
		mlx_delete_texture(game->west.texture);
	if (game->east.texture)
		mlx_delete_texture(game->east.texture);
}

void	ft_error(void)
{
	perror(mlx_strerror(mlx_errno));
	exit(EXIT_FAILURE);
}
