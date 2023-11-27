/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_textures.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ebennix <ebennix@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/08 20:29:40 by ebennix           #+#    #+#             */
/*   Updated: 2023/11/27 12:41:22 by ebennix          ###   ########.fr       */
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
}