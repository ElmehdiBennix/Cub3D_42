/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ebennix <ebennix@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/01 19:45:35 by ebennix           #+#    #+#             */
/*   Updated: 2023/11/27 15:27:55 by ebennix          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "inc/cub3d.h"

// static void draw_gun(t_data *game)
// {
// 	mlx_texture_to_image(game->mlx, game->texs.Gun_animation->content);
// 	mlx_image_to_window(game->mlx, game->texs.Gun_animation->content, 0, 0);
// }

static void draw_faces(t_data *game)
{
	game->frames++;
	if (game->frames % 80 == 0)
		game->face_idle = !game->face_idle;
	if (game->player.walkD == 1 || game->player.walkD == -1)
	{
		if (game->gun_running == false && game->gun->instances->x < 680)
			game->gun->instances->x += 4;
		else
		{
			game->gun_running = true;
			game->gun->instances->x -= 4;
			if (game->gun->instances->x < 580)
				game->gun_running = false;
		}
		game->Faces = mlx_texture_to_image(game->mlx, game->texs.Faces[2]);
		mlx_image_to_window(game->mlx, game->Faces ,1463, 563);
	}
	else if (game->player.turnD == 1)
	{
		game->Faces = mlx_texture_to_image(game->mlx, game->texs.Faces[4]);
		mlx_image_to_window(game->mlx, game->Faces ,1463, 563);
	}
	else if (game->player.turnD == -1)
	{
		game->Faces = mlx_texture_to_image(game->mlx, game->texs.Faces[3]);
		mlx_image_to_window(game->mlx, game->Faces ,1463, 563);
	}
	else
	{
		if (game->face_idle == false)
			game->Faces = mlx_texture_to_image(game->mlx, game->texs.Faces[0]);
		else
			game->Faces = mlx_texture_to_image(game->mlx, game->texs.Faces[1]);
		mlx_image_to_window(game->mlx, game->Faces ,1463, 563);
	}
	game->Faces->enabled = false;
}

static void	drawing(t_data *game)
{
	// t_draw draw = { game->MINI_Map, game->player.x,
	// 				game->player.y,
	// 				game->player.x + (cos(game->player.rotationA) * 30),
	// 				game->player.y + (sin(game->player.rotationA) * 30),
	// 				0x00FF00FF };
	// draw_lines(&draw);

/// #############################################
	mlx_delete_image(game->mlx, game->Faces);

	draw_faces(game);
	update_state(game);
	game->gun->enabled = false;
	game->HUD->enabled = false;
	castAllRays(game);
	generate3DMap(game);
	game->gun->enabled = true;
	mini_map(game, 3, 3);
	game->HUD->enabled = true;
	game->Faces->enabled = true;

}

static void setup(t_data	*game)
{
	game->player.x = game->player_info.x * TILE_S + (TILE_S / 2);
	game->player.y = game->player_info.y * TILE_S + (TILE_S / 2);
	game->player.turnD = 0;
	game->player.walkD = 0;
	game->player.mouseX = 0;
	game->player.sideW = 0;
	if (game->player_info.direction == 'N')
		game->player.rotationA = M_PI + M_PI_2;
	else if (game->player_info.direction == 'S')
		game->player.rotationA = M_PI_2;
	else if (game->player_info.direction == 'E')
		game->player.rotationA = 0;
	else if (game->player_info.direction == 'W')
		game->player.rotationA = M_PI;
	game->player.walkS = 3.0f;
	game->player.turnS = 1 * (M_PI / 180); // 2 degrees per frame
}

static void	gerphec(t_data *game)
{
	game->mlx = mlx_init(WIDTH, HEIGHT, "Cub3D", false);
	if (!game->mlx)
		ft_error();

    init_images(game);

	mlx_key_hook(game->mlx, (void *)key_events, game);
	mlx_loop_hook(game->mlx, (void *)drawing, game);

	mlx_set_cursor_mode(game->mlx, MLX_MOUSE_DISABLED);
	mlx_cursor_hook(game->mlx,(void *)mouse_event, game);

	mlx_loop(game->mlx);
	mlx_terminate(game->mlx);
}

// void f()
// {
// 	system("leaks cub3d");
// }

int	main(int ac, char **av)
{
    t_data	game;
	
    if (ac != 2)
		return (ft_fprintf(2, RED "Error : supply the map file.\n" DEFAULT), 1);

	parser(&game, read_file(*(++av)));
	setup(&game);
	gerphec(&game);

	// atexit(f);
	return (EXIT_SUCCESS);
}
// flip colors of c and floor
