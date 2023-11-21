/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free_game.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ebennix <ebennix@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/13 05:11:51 by ebennix           #+#    #+#             */
/*   Updated: 2023/11/21 03:37:08 by ebennix          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/cub3d.h"

// static	void	free_lst(t_data *game)
// {
// 	t_list	*tmp;

// 	ft_lstfree(game->componets.tmp);
// 	tmp = game->componets.player -> next;
// 	game->componets.player -> next = NULL;
// 	ft_lstfree(tmp);
// 	tmp = game->componets.collectible -> next;
// 	game->componets.collectible -> next = NULL;
// 	ft_lstfree(tmp);
// 	tmp = game->componets.floor_enemy -> next;
// 	game->componets.floor_enemy -> next = NULL;
// 	ft_lstfree(tmp);
// 	tmp = game->componets.wall_enemy -> next;
// 	game->componets.wall_enemy -> next = NULL;
// 	ft_lstfree(tmp);
// }

// static	void	destroy_images(t_data	*game)
// {
// 	mlx_destroy_image(game->mlx, game->walls.top_v1);
// 	mlx_destroy_image(game->mlx, game->walls.top_v2);
// 	mlx_destroy_image(game->mlx, game->walls.down_v1);
// 	mlx_destroy_image(game->mlx, game->walls.down_v2);
// 	mlx_destroy_image(game->mlx, game->walls.right_v1);
// 	mlx_destroy_image(game->mlx, game->walls.right_v2);
// 	mlx_destroy_image(game->mlx, game->walls.left_v1);
// 	mlx_destroy_image(game->mlx, game->walls.left_v2);
// 	mlx_destroy_image(game->mlx, game->walls.down_right);
// 	mlx_destroy_image(game->mlx, game->walls.down_left);
// 	mlx_destroy_image(game->mlx, game->walls.block_v1);
// 	mlx_destroy_image(game->mlx, game->walls.block_v2);
// 	mlx_destroy_image(game->mlx, game->walls.full);
// 	mlx_destroy_image(game->mlx, game->floors.floor);
// 	mlx_destroy_image(game->mlx, game->floors.bones);
// 	mlx_destroy_image(game->mlx, game->floors.rocks);
// 	mlx_destroy_image(game->mlx, game->floors.head_bone);
// 	mlx_destroy_image(game->mlx, game->floors.web);
// 	free_lst(game);
// }

// void	free_game(t_data *game)
// {
// 	free2d(game->map);
// 	mlx_destroy_window(game->mlx, game->mlx_win);
// 	destroy_images(game);
// 	free(game);
// }

// int	exit_game(t_data *game)
// {
// 	free2d(game->map);
// 	mlx_destroy_window(game->mlx, game->mlx_win);
// 	destroy_images(game);
// 	free(game);
// 	exit_msg(1, "Quit.", YELLOW, 0);
// 	return (0);
// }

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
	if (game->North.texture)
		mlx_delete_texture(game->North.texture);
	if (game->South.texture)
		mlx_delete_texture(game->South.texture);
	if (game->West.texture)
		mlx_delete_texture(game->West.texture);
	if (game->East.texture)
		mlx_delete_texture(game->East.texture);
}

void ft_error(void)
{
	perror(mlx_strerror(mlx_errno));
	exit(EXIT_FAILURE);
}