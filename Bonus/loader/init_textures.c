/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_textures.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hasalam <hasalam@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/08 20:29:40 by ebennix           #+#    #+#             */
/*   Updated: 2023/12/06 01:18:07 by hasalam          ###   ########.fr       */
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

static void	load_image_to_screen(t_data *game, char *content,
		mlx_image_t **img_adrs, int32_t *cordenates)
{
	mlx_texture_t	*texs;

	if (init_textures(content, &texs) == false)
		return (free2d(game->map), free_texture(game), exit(1));
	*img_adrs = mlx_texture_to_image(game->mlx, texs);
	if (!(*img_adrs) || mlx_image_to_window(game->mlx, *img_adrs, cordenates[0],
			cordenates[1]) == -1)
		return (free2d(game->map), free_texture(game), ft_error());
	mlx_delete_texture(texs);
}

void	init_gun_animations(t_data *game, struct s_init_image *var)
{
	var->path = "./assets/textures/gun/gun1.png";
	load_image_to_screen(game, var->path, &game->canvas.gun[0],
		(int32_t[2]){624, 270});
	var->path = "./assets/textures/gun/gun2.png";
	load_image_to_screen(game, var->path, &game->canvas.gun[1],
		(int32_t[2]){624, 270});
	var->path = "./assets/textures/gun/gun3.png";
	load_image_to_screen(game, var->path, &game->canvas.gun[2],
		(int32_t[2]){624, 270});
	var->path = "./assets/textures/gun/gun4.png";
	load_image_to_screen(game, var->path, &game->canvas.gun[3],
		(int32_t[2]){624, 270});
	var->path = "./assets/textures/gun/gun5.png";
	load_image_to_screen(game, var->path, &game->canvas.gun[4],
		(int32_t[2]){624, 270});
	var->path = "./assets/textures/gun/gun6.png";
	load_image_to_screen(game, var->path, &game->canvas.gun[5],
		(int32_t[2]){624, 270});
}

void	init_faces_animations(t_data *game, struct s_init_image *var)
{
	var->path = "./assets/textures/faces/face_idle1.png";
	load_image_to_screen(game, var->path, &game->canvas.faces[0],
		(int32_t[2]){1463, 563});
	var->path = "./assets/textures/faces/face_idle2.png";
	load_image_to_screen(game, var->path, &game->canvas.faces[1],
		(int32_t[2]){1463, 563});
	var->path = "./assets/textures/faces/face_move.png";
	load_image_to_screen(game, var->path, &game->canvas.faces[2],
		(int32_t[2]){1463, 563});
	var->path = "./assets/textures/faces/face_left.png";
	load_image_to_screen(game, var->path, &game->canvas.faces[3],
		(int32_t[2]){1463, 563});
	var->path = "./assets/textures/faces/face_right.png";
	load_image_to_screen(game, var->path, &game->canvas.faces[4],
		(int32_t[2]){1463, 563});
	var->path = "./assets/textures/faces/face_attack.png";
	load_image_to_screen(game, var->path, &game->canvas.faces[5],
		(int32_t[2]){1463, 563});
}

void	init_images(t_data *game)
{
	struct s_init_image	var;

	game->canvas.world_3d = mlx_new_image(game->mlx, WIDTH, HEIGHT);
	if (!game->canvas.world_3d || mlx_image_to_window(game->mlx,
			game->canvas.world_3d, 0, 0) == -1)
		return (free2d(game->map), free_texture(game), ft_error());
	var.path = "./assets/textures/walls/door.png";
	if (init_textures(var.path, &game->door) == false)
		return (free2d(game->map), free_texture(game), exit(1));
	init_gun_animations(game, &var);
	game->canvas.gun_x = game->canvas.gun[0]->instances->x;
	game->canvas.gun_y = game->canvas.gun[0]->instances->y;
	var.path = "./assets/textures/hud.png";
	load_image_to_screen(game, var.path, &game->canvas.hud, (int32_t[2]){-2,
		0});
	init_faces_animations(game, &var);
	disable_images(game);
}
