/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_textures.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ebennix <ebennix@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/08 20:29:40 by ebennix           #+#    #+#             */
/*   Updated: 2023/11/27 13:23:26 by ebennix          ###   ########.fr       */
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

void init_images(t_data *game)
{
    bool   check = true;
    
    game->world_3D = mlx_new_image(game->mlx, WIDTH, HEIGHT);
    mlx_image_to_window(game->mlx, game->world_3D, 0, 0); // only need to loop over the drawing

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
        return(ft_error(),exit(1)); // freee all

    game->world_3D = mlx_new_image(game->mlx, WIDTH, HEIGHT);
    mlx_image_to_window(game->mlx, game->world_3D, 0, 0); // only need to loop over the drawing

    game->gun = mlx_texture_to_image(game->mlx, game->texs.Gun_animation[0]);
	mlx_image_to_window(game->mlx, game->gun, game->mlx->width / 2 - game->gun->width / 2, 270); // hard codeeee goes brrreee

	game->HUD = mlx_texture_to_image(game->mlx, game->texs.HUD_template);
	mlx_image_to_window(game->mlx, game->HUD, -2, 0); // hard codeeee goes brrreee

}