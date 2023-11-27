/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ebennix <ebennix@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/01 19:45:35 by ebennix           #+#    #+#             */
/*   Updated: 2023/11/27 12:22:34 by ebennix          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "inc/cub3d.h"

static void	mini_map(t_data *game ,double x_vis, double y_vis)
{
	int draw_x = 1408;
	int draw_y = 122;

	int x_distance = (x_vis * 2) * TILE_S + 1407;
	int y_distance = (y_vis * 2) * TILE_S + 122;

	
	float camera_x;
	float camera_y = game->player.y - (y_vis * TILE_S);
	while (draw_y <= y_distance)
	{
		camera_x = game->player.x - (x_vis * TILE_S);
		while (draw_x <= x_distance)
		{
			int x = floor(camera_x / TILE_S);
			int y = floor(camera_y / TILE_S);
			if (x < 0 || y < 0 || x >= (float)game->map_width || y >= (float)game->map_height)
				mlx_put_pixel(game->HUD, draw_x , draw_y, 0x000000FF);
			else if (game->map[y][x] == '1')
				mlx_put_pixel(game->HUD, draw_x , draw_y, 0xFFFFFFFF);
			else if (game->map[y][x] == '0')
				mlx_put_pixel(game->HUD, draw_x , draw_y, 0x66FFFFFF);
			else
				mlx_put_pixel(game->HUD, draw_x , draw_y, 0x000000FF);
			draw_x++;
			camera_x++;
		}
		camera_y++;
		draw_x = 1407;
		if (draw_y == y_distance - 1)
			draw_x = 1408;
		draw_y++;
	}
 	// mlx_put_pixel(game->HUD,draw_x+ ((x_vis * 2) * TILE_S) / 2,draw_y + ((y_vis * 2) * TILE_S) / 2,0x000000FF); // render player
}

// static void draw_gun(t_data *game)
// {
// 	mlx_texture_to_image(game->mlx, game->texs.Gun_animation->content);
// 	mlx_image_to_window(game->mlx, game->texs.Gun_animation->content, 0, 0);
// }

// static void draw_faces(t_data *game)
// {
// 	if (game->player.walkD == 1 || game->player.walkD == -1) // or side walking // move the gun left and right
// 	{
// 		mlx_texture_to_image(game->mlx, game->texs.Faces->content);
// 		mlx_image_to_window(game->mlx, game->texs.Faces->content, 0, 0);
// 	}
// 	else if (game->player.turnD == 1)
// 	{
// 		mlx_texture_to_image(game->mlx, game->texs.Faces->next->next->content);
// 		mlx_image_to_window(game->mlx, game->texs.Faces->next->next->content, 0, 0);
// 	}
// 	else if (game->player.turnD == -1)
// 	{
// 		mlx_texture_to_image(game->mlx, game->texs.Faces->next->next->next->content);
// 		mlx_image_to_window(game->mlx, game->texs.Faces->next->next->next->content, 0, 0);
// 	}
// 	else
// 	{
// 		mlx_texture_to_image(game->mlx, game->texs.Faces->next->next->next->next->content);
// 		mlx_image_to_window(game->mlx, game->texs.Faces->next->next->next->next->content, 0, 0);
// 	}
// }

//ray casted map first
// gun
//hud and all its elemets

static void	drawing(t_data *game)
{
	// t_draw draw = { game->MINI_Map, game->player.x,
	// 				game->player.y,
	// 				game->player.x + (cos(game->player.rotationA) * 30),
	// 				game->player.y + (sin(game->player.rotationA) * 30),
	// 				0x00FF00FF };
	// draw_lines(&draw);

/// #############################################
	// mlx_delete_image(game->mlx, game->HUD);

	update_state(game);
	castAllRays(game);
	game->HUD->enabled = false;
	generate3DMap(game);
	mini_map(game, 3, 3);
	game->HUD->enabled = true;

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

// void huddy(t_data *game)
// {
// 	mlx_delete_image(game->mlx, game->HUD);

// 	game->HUD = mlx_texture_to_image(game->mlx, game->texs.HUD_template);
// 	mini_map(game, 3, 3);

// 	if (!game->HUD || (mlx_image_to_window(game->mlx, game->HUD, 0, 0) < 0))
// 		ft_error();
// }

static void	gerphec(t_data *game)
{
	game->mlx = mlx_init(WIDTH, HEIGHT, "Cub3D", false);
	if (!game->mlx)
		ft_error();

	game->world_3D = mlx_new_image(game->mlx, WIDTH, HEIGHT);
	mlx_image_to_window(game->mlx, game->world_3D, 0, 0);
	game->HUD = mlx_texture_to_image(game->mlx, game->texs.HUD_template);
	mlx_image_to_window(game->mlx, game->HUD, 0, 0);
	game->HUD->enabled = false;
	// castAllRays(game);
	// generate3DMap(game);

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
    // init_images(game); // if we added some textures
	init_textures("./assets/textures/hud.png", &game.texs.HUD_template);
	setup(&game);
	gerphec(&game);

	// atexit(f);
	return (EXIT_SUCCESS);
}
