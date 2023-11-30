/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_textures.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ebennix <ebennix@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/08 20:29:40 by ebennix           #+#    #+#             */
/*   Updated: 2023/11/30 02:21:07 by ebennix          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/cub3d.h"

bool    init_textures(char *content ,mlx_texture_t   **texture)
{
    *texture = mlx_load_png(content);
	if (!(*texture))
		return (close(2) ,false);
    return (true);
}

void    init_images(t_data *game)
{
    bool   check = true;

    check = init_textures("./assets/textures/hud.png", &game->texs.HUD_template);

    check = init_textures("./assets/textures/faces/face_idle1.png", &game->texs.Faces[0]);
    check = init_textures("./assets/textures/faces/face_idle2.png", &game->texs.Faces[1]);
    check = init_textures("./assets/textures/faces/face_move.png", &game->texs.Faces[2]);
    check = init_textures("./assets/textures/faces/face_left.png", &game->texs.Faces[3]);
    check = init_textures("./assets/textures/faces/face_right.png", &game->texs.Faces[4]);
    check = init_textures("./assets/textures/faces/face_attack.png", &game->texs.Faces[5]);
    
    check = init_textures("./assets/textures/gun/gun1.png", &game->texs.Gun_animation[0]);
    check = init_textures("./assets/textures/gun/gun2.png", &game->texs.Gun_animation[1]);
    check = init_textures("./assets/textures/gun/gun3.png", &game->texs.Gun_animation[2]);
    check = init_textures("./assets/textures/gun/gun4.png", &game->texs.Gun_animation[3]);
    check = init_textures("./assets/textures/gun/gun5.png", &game->texs.Gun_animation[4]);
    check = init_textures("./assets/textures/gun/gun6.png", &game->texs.Gun_animation[5]);

    if (check == false)
        return(ft_error(),exit(1));

/// init world textures :
    game->canvas.world_3D = mlx_new_image(game->mlx, WIDTH, HEIGHT);
    mlx_image_to_window(game->mlx, game->canvas.world_3D, 0, 0);


/// init all gun animations :
	game->canvas.gun[0] = mlx_texture_to_image(game->mlx, game->texs.Gun_animation[0]);
	mlx_image_to_window(game->mlx, game->canvas.gun[0], game->mlx->width / 2 - game->canvas.gun[0]->width / 2, 270);

	game->canvas.gun[1] = mlx_texture_to_image(game->mlx, game->texs.Gun_animation[1]);
	mlx_image_to_window(game->mlx, game->canvas.gun[1], game->mlx->width / 2 - game->canvas.gun[1]->width / 2, 270);

	game->canvas.gun[2] = mlx_texture_to_image(game->mlx, game->texs.Gun_animation[2]);
	mlx_image_to_window(game->mlx, game->canvas.gun[2], game->mlx->width / 2 - game->canvas.gun[2]->width / 2, 270);

	game->canvas.gun[3] = mlx_texture_to_image(game->mlx, game->texs.Gun_animation[3]);
	mlx_image_to_window(game->mlx, game->canvas.gun[3], game->mlx->width / 2 - game->canvas.gun[3]->width / 2, 270);

	game->canvas.gun[4] = mlx_texture_to_image(game->mlx, game->texs.Gun_animation[4]);
	mlx_image_to_window(game->mlx, game->canvas.gun[4], game->mlx->width / 2 - game->canvas.gun[4]->width / 2, 270);

	game->canvas.gun[5] = mlx_texture_to_image(game->mlx, game->texs.Gun_animation[5]);
	mlx_image_to_window(game->mlx, game->canvas.gun[5], game->mlx->width / 2 - game->canvas.gun[5]->width / 2, 270);

    game->canvas.gun_x = game->canvas.gun[0]->instances->x;
    game->canvas.gun_y = game->canvas.gun[0]->instances->y;

/// init HUD :
	game->canvas.HUD = mlx_texture_to_image(game->mlx, game->texs.HUD_template);
	mlx_image_to_window(game->mlx, game->canvas.HUD, -2, 0); // hard codeeee goes brrreee

/// init all faces animations :
	game->canvas.Faces[0] = mlx_texture_to_image(game->mlx, game->texs.Faces[0]);
    mlx_image_to_window(game->mlx, game->canvas.Faces[0] ,1463, 563);

	game->canvas.Faces[1] = mlx_texture_to_image(game->mlx, game->texs.Faces[1]);
    mlx_image_to_window(game->mlx, game->canvas.Faces[1] ,1463, 563);

	game->canvas.Faces[2] = mlx_texture_to_image(game->mlx, game->texs.Faces[2]);
    mlx_image_to_window(game->mlx, game->canvas.Faces[2] ,1463, 563);

	game->canvas.Faces[3] = mlx_texture_to_image(game->mlx, game->texs.Faces[3]);
    mlx_image_to_window(game->mlx, game->canvas.Faces[3] ,1463, 563);

	game->canvas.Faces[4] = mlx_texture_to_image(game->mlx, game->texs.Faces[4]);
    mlx_image_to_window(game->mlx, game->canvas.Faces[4] ,1463, 563);

	game->canvas.Faces[5] = mlx_texture_to_image(game->mlx, game->texs.Faces[5]);
    mlx_image_to_window(game->mlx, game->canvas.Faces[5] ,1463, 563);

    disable_images(game);
}

void    disable_images(t_data *game)
{
    game->canvas.gun[0]->enabled = false;
    game->canvas.gun[1]->enabled = false;
    game->canvas.gun[2]->enabled = false;
    game->canvas.gun[3]->enabled = false;
    game->canvas.gun[4]->enabled = false;
    game->canvas.gun[5]->enabled = false;
    game->canvas.Faces[0]->enabled = false;
    game->canvas.Faces[1]->enabled = false;
    game->canvas.Faces[2]->enabled = false;
    game->canvas.Faces[3]->enabled = false;
    game->canvas.Faces[4]->enabled = false;
    game->canvas.Faces[5]->enabled = false;
    game->canvas.HUD->enabled = false;
}