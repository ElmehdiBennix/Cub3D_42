/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_images_1.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ebennix <ebennix@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/08 20:29:40 by ebennix           #+#    #+#             */
/*   Updated: 2023/11/16 02:41:26 by ebennix          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/cub3d.h"

// void	*protect_image(void *mlx_ptr, char *filename,
// 							int *width, int *height)
// {
// 	void	*p;

// 	p = mlx_xpm_file_to_image(mlx_ptr, filename, width, height);
// 	if (!p)
// 		exit_msg(2, "Texture file not found.", RED, 1);
// 	return (p);
// }

// void	init_images_1(t_data *game)
// {
// 	game->walls.block_v1 = protect_image(game->mlx,
// 			"textures/wall/block_wall_v1.xpm",
// 			&game->walls.img_width, &game->walls.img_height);
// 	game->walls.block_v2 = protect_image(game->mlx,
// 			"textures/wall/block_wall_v2.xpm",
// 			&game->walls.img_width, &game->walls.img_height);
// 	game->walls.down_v1 = protect_image(game->mlx,
// 			"textures/wall/down_wall_v1.xpm",
// 			&game->walls.img_width, &game->walls.img_height);
// 	game->walls.down_v2 = protect_image(game->mlx,
// 			"textures/wall/down_wall_v2.xpm",
// 			&game->walls.img_width, &game->walls.img_height);
// 	game->walls.left_v1 = protect_image(game->mlx,
// 			"textures/wall/left_wall_v1.xpm",
// 			&game->walls.img_width, &game->walls.img_height);
// 	game->walls.left_v2 = protect_image(game->mlx,
// 			"textures/wall/left_wall_v2.xpm",
// 			&game->walls.img_width, &game->walls.img_height);
// 	game->walls.down_left = protect_image(game->mlx,
// 			"textures/wall/down_left_wall.xpm",
// 			&game->walls.img_width, &game->walls.img_height);
// 	game->walls.down_right = protect_image(game->mlx,
// 			"textures/wall/down_right_wall.xpm",
// 			&game->walls.img_width, &game->walls.img_height);
// }

// void	init_images_2(t_data *game)
// {
// 	game->walls.full = protect_image(game->mlx,
// 			"textures/wall/full_wall.xpm",
// 			&game->walls.img_width, &game->walls.img_height);
// 	game->walls.right_v1 = protect_image(game->mlx,
// 			"textures/wall/right_wall_v1.xpm",
// 			&game->walls.img_width, &game->walls.img_height);
// 	game->walls.right_v2 = protect_image(game->mlx,
// 			"textures/wall/right_wall_v2.xpm",
// 			&game->walls.img_width, &game->walls.img_height);
// 	game->walls.top_v1 = protect_image(game->mlx,
// 			"textures/wall/top_wall_v1.xpm",
// 			&game->walls.img_width, &game->walls.img_height);
// 	game->walls.top_v2 = protect_image(game->mlx,
// 			"textures/wall/top_wall_v2.xpm",
// 			&game->walls.img_width, &game->walls.img_height);
// 	game->floors.bones = protect_image(game->mlx,
// 			"textures/decoration/bones.xpm",
// 			&game->floors.img_width, &game->floors.img_height);
// 	game->floors.rocks = protect_image(game->mlx,
// 			"textures/decoration/rocks.xpm",
// 			&game->floors.img_width, &game->floors.img_height);
// 	game->floors.head_bone = protect_image(game->mlx,
// 			"textures/decoration/head_bone.xpm",
// 			&game->floors.img_width, &game->floors.img_height);
// }

// void	init_images_3(t_data *game)
// {
// 	t_list	*last;

// 	game->floors.web = protect_image(game->mlx,
// 			"textures/decoration/web.xpm",
// 			&game->floors.img_width, &game->floors.img_height);
// 	game->floors.floor = protect_image(game->mlx,
// 			"textures/floor/floor.xpm",
// 			&game->floors.img_width, &game->floors.img_height);
// 	game->componets.player = ft_lstnew(protect_image(
// 				game->mlx, "textures/player/skull_1.xpm",
// 				&game->componets.img_width, &game->componets.img_height));
// 	ft_lstcreate_back(&game->componets.player, protect_image(
// 			game->mlx, "textures/player/skull_2.xpm",
// 			&game->componets.img_width, &game->componets.img_height));
// 	ft_lstcreate_back(&game->componets.player, protect_image(
// 			game->mlx, "textures/player/skull_3.xpm",
// 			&game->componets.img_width, &game->componets.img_height));
// 	ft_lstcreate_back(&game->componets.player, protect_image(
// 			game->mlx, "textures/player/skull_4.xpm",
// 			&game->componets.img_width, &game->componets.img_height));
// 	last = ft_lstlast(game->componets.player);
// 	last->next = game->componets.player;
// }

// void	init_images_4(t_data *game)
// {
// 	t_list	*last;

// 	game->componets.collectible = ft_lstnew(protect_image(
// 				game->mlx, "textures/collectible/coin_1.xpm",
// 				&game->componets.img_width, &game->componets.img_height));
// 	ft_lstcreate_back(&game->componets.collectible, protect_image(
// 			game->mlx, "textures/collectible/coin_2.xpm",
// 			&game->componets.img_width, &game->componets.img_height));
// 	ft_lstcreate_back(&game->componets.collectible, protect_image(
// 			game->mlx, "textures/collectible/coin_3.xpm",
// 			&game->componets.img_width, &game->componets.img_height));
// 	ft_lstcreate_back(&game->componets.collectible, protect_image(
// 			game->mlx, "textures/collectible/coin_4.xpm",
// 			&game->componets.img_width, &game->componets.img_height));
// 	last = ft_lstlast(game->componets.collectible);
// 	last->next = game->componets.collectible;
// }
