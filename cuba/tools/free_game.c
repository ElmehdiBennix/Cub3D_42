/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free_game.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ebennix <ebennix@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/13 05:11:51 by ebennix           #+#    #+#             */
/*   Updated: 2023/12/02 02:34:41 by ebennix          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/cub3d.h"

void	free_fields(t_data *game)
{
	if (game->North.content_Nullable)
		free(game->North.content_Nullable);
	if (game->South.content_Nullable)
		free(game->South.content_Nullable);
	if (game->West.content_Nullable)
		free(game->West.content_Nullable);
	if (game->East.content_Nullable)
		free(game->East.content_Nullable);
	if (game->C_Floor.content_Nullable)
		free(game->C_Floor.content_Nullable);
	if (game->C_Ceiling.content_Nullable)
		free(game->C_Ceiling.content_Nullable);
}

void	free_texture(t_data *game)
{
	// if (game->North.texture)
		mlx_delete_texture(game->North.texture);
	// if (game->South.texture)
		mlx_delete_texture(game->South.texture);
	// if (game->West.texture)
		mlx_delete_texture(game->West.texture);
	// if (game->East.texture)
		mlx_delete_texture(game->East.texture);
}

void	ft_error(void)
{
	perror(mlx_strerror(mlx_errno));
	exit(EXIT_FAILURE);
}