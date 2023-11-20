/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free_game.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ebennix <ebennix@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/13 05:11:51 by ebennix           #+#    #+#             */
/*   Updated: 2023/11/21 00:16:02 by ebennix          ###   ########.fr       */
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

void ft_error(void)
{
	perror(mlx_strerror(mlx_errno));
	exit(EXIT_FAILURE);
}