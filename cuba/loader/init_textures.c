/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_textures.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ebennix <ebennix@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/08 20:29:40 by ebennix           #+#    #+#             */
/*   Updated: 2023/12/04 04:04:46 by ebennix          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/cub3d.h"

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

bool    init_textures(char *content ,mlx_texture_t   **texture)
{
    *texture = mlx_load_png(content);
	if (!(*texture))
		return (close(2) ,false);
    return (true);
}

void load_image_to_screen(t_data *game, char *content ,mlx_image_t **img_adrs ,int32_t *cordenates)
{
    mlx_texture_t *texs;

    if (init_textures(content , &texs) == false)
        return (free2d(game->map), free_texture(game) ,exit(1));
    *img_adrs = mlx_texture_to_image(game->mlx, texs);
    if (!(*img_adrs) || mlx_image_to_window(game->mlx, *img_adrs, cordenates[0], cordenates[1]) == -1)
        return (free2d(game->map), free_texture(game) ,ft_error());
    mlx_delete_texture(texs);
}

void    init_images(t_data *game)
{
    game->canvas.world_3D = mlx_new_image(game->mlx, WIDTH, HEIGHT);
    if (!game->canvas.world_3D ||mlx_image_to_window(game->mlx, game->canvas.world_3D, 0, 0) == -1)
        return(free2d(game->map), free_texture(game) ,ft_error());
    load_image_to_screen(game ,"./assets/textures/gun/gun1.png", &game->canvas.gun[0], (int32_t[2]){624, 270});
    load_image_to_screen(game ,"./assets/textures/gun/gun2.png", &game->canvas.gun[1], (int32_t[2]){624, 270});
    load_image_to_screen(game ,"./assets/textures/gun/gun3.png", &game->canvas.gun[2], (int32_t[2]){624, 270});
    load_image_to_screen(game ,"./assets/textures/gun/gun4.png", &game->canvas.gun[3], (int32_t[2]){624, 270});
    load_image_to_screen(game ,"./assets/textures/gun/gun5.png", &game->canvas.gun[4], (int32_t[2]){624, 270});
    load_image_to_screen(game ,"./assets/textures/gun/gun6.png", &game->canvas.gun[5], (int32_t[2]){624, 270});
    game->canvas.gun_x = game->canvas.gun[0]->instances->x;
    game->canvas.gun_y = game->canvas.gun[0]->instances->y;

    load_image_to_screen(game ,"./assets/textures/hud.png", &game->canvas.HUD, (int32_t[2]){-2, 0});

    load_image_to_screen(game ,"./assets/textures/faces/face_idle1.png", &game->canvas.Faces[0], (int32_t[2]){1463, 563});
    load_image_to_screen(game ,"./assets/textures/faces/face_idle2.png", &game->canvas.Faces[1], (int32_t[2]){1463, 563});
    load_image_to_screen(game ,"./assets/textures/faces/face_move.png", &game->canvas.Faces[2], (int32_t[2]){1463, 563});
    load_image_to_screen(game ,"./assets/textures/faces/face_left.png", &game->canvas.Faces[3], (int32_t[2]){1463, 563});
    load_image_to_screen(game ,"./assets/textures/faces/face_right.png", &game->canvas.Faces[4], (int32_t[2]){1463, 563});
    load_image_to_screen(game ,"./assets/textures/faces/face_attack.png", &game->canvas.Faces[5], (int32_t[2]){1463, 563});

    disable_images(game);    
}
