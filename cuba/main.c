/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ebennix <ebennix@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/01 19:45:35 by ebennix           #+#    #+#             */
/*   Updated: 2023/11/27 11:19:50 by ebennix          ###   ########.fr       */
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

// static bool collision(t_data *game, float x, float y) // working in the dark
// {
// 	int mapX = floor(x / TILE_S);
// 	int mapY = floor(y / TILE_S);
// 	if (mapX <= 0 || mapY <= 0 || mapX >= (int)game->map_width || mapY >= (int)game->map_height || game->map[mapY][mapX] == '1')
// 	{
// 		printf("---------------> collision\n");
// 		return (true);
// 	}
// 	printf("---------------> false collision \n");
// 	return (false);
// }


// static void update(t_data *game)
// {
// 	game->player.rotationA += game->player.turnS * game->player.turnD;

// 	float move = game->player.walkD * game->player.walkS;
// 	// printf("move = %f\n", move);

// 	// check for collisions before updating the player position

// 	if (collision(game, game->player.x + cos(game->player.rotationA) * move, game->player.y + sin(game->player.rotationA) * move) == false)
// 	{
// 		game->player.x += cos(game->player.rotationA) * move;
// 		game->player.y += sin(game->player.rotationA) * move;
// 	}
// 	// printf("x = %f y = %f\n", game->player.x, game->player.y);
// }

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
	mlx_delete_image(game->mlx, game->world_3D);
	game->world_3D = mlx_new_image(game->mlx, WIDTH, HEIGHT);
	castAllRays(game);
	generate3DMap(game);
	mlx_image_to_window(game->mlx, game->world_3D, 0, 0);
	game->HUD = mlx_texture_to_image(game->mlx, game->texs.HUD_template);
	mlx_image_to_window(game->mlx, game->HUD, 0, 0);
	while (1)

	// renderMap(game);
	// renderRays(game);
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
	game->player.turnS = 4 * (M_PI / 180); // 2 degrees per frame
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
	mlx_key_hook(game->mlx, (void *)key_events, game);
	mlx_loop_hook(game->mlx, (void *)drawing, game);
	// mlx_loop_hook(game->mlx, (void *)huddy, game);

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
// seg when i turn without moving a key

// void	ft_loop(void* param)
// {
// 	t_Player *player = param;

// 	mlx_delete_image(player->mlx, player->img);
// 	player->img = mlx_new_image(player->mlx, WIDTH, HEIGHT);
// 	castAllRays(player);
// 	ft_update(player);
// 	generate3DMap(player);
// 	// renderMap(player);
// 	// renderRays(player);
// 	if (!player->img || (mlx_image_to_window(player->mlx, player->img, 0, 0) < 0))
// 		ft_error();
// 	//player->gun= mlx_load_png("ok.png");
// 	// mlx_image_t *ok = mlx_texture_to_image(player->mlx, player->gun);
// 	// mlx_image_to_window(player->mlx, ok, WIDTH / 2, HEIGHT / 2);
// }

// void ft_helper(t_Player *player)
// {
// 	// mlx_key_hook(player->mlx, ft_key, player);
// 	//ft_loop(player);
// 	mlx_loop_hook(player->mlx, ft_loop, player);

// 	// mlx_loop(player->mlx);
// 	// mlx_terminate(player->mlx);
// }

// int	xxxx()
// { 
// 	// player.img = mlx_new_image(player.mlx, WIDTH, HEIGHT);
// 	// player.text1 = mlx_load_png("./assets/textures/wall1.png");
// 	// 	if (!player.text1)
// 	// 		ft_error();
// 	// player.text2 = mlx_load_png("./assets/textures/wall2.png");
// 	// 	if (!player.text2)
// 	// 		ft_error();
// 	// player.text3 = mlx_load_png("./assets/textures/wall3.png");
// 	// 	if (!player.text3)
// 	// 		ft_error();
// 	// player.text4 = mlx_load_png("./assets/textures/wall4.png");
// 	// 	if (!player.text4)
// 	// 		ft_error();
// 	// player.gun = mlx_load_png("/assets/textures/ok.png");
// 	// if (!player.gun)
// 	// 	ft_error();
// 	ft_helper(&player);
// 	return (EXIT_SUCCESS);
// }





















// static void	mini_map(t_data *game ,int x_vis, int y_vis) // impaire   /// 5 // 5  // drawing is all fucked up
// {
// 	int x_distance = x_vis * 2 + 1;
// 	int y_distance = y_vis * 2 + 1;

// 	int x = game->player_info.x - x_vis;
// 	int y = game->player_info.y - y_vis;

// 	printf("PLAYER X = %d PLAYER Y = %d\n", game->player_info.x, game->player_info.y);
// 	printf("X = %d Y = %d\n", x ,y);
// 	printf("h = %d w = %d\n", game->map_height ,game->map_width);
// 	printf("##############################\n");

// 	const int size = 10;

// 	int draw_x = 0;
// 	int draw_y = 0;
	
// 	int count = 0;
	
// 	while (y_distance)
// 	{
// 		printf("line %d = ", count);
// 		while (x_distance)
// 		{
// 			if (x < 0 || y < 0 || (unsigned int) x >= game->map_width || (unsigned int) y >= game->map_height)
// 			{
// 				printf("*");
// 				draw_cub(game,size,draw_x,draw_y,0x000000FF);
// 				// printf("red");
// 			}
// 			else if (game->map[y][x] == '1')
// 			{
// 				printf("1");
// 				draw_cub(game,size,draw_x,draw_y,0xFFFFFFFF);
// 				// printf("green");
// 			}
// 			else if (game->map[y][x] == '0')
// 			{
// 				printf("0");
// 				draw_cub(game,size,draw_x,draw_y,0x66FFFFFF);
// 				// printf("blue");
// 			}
// 			else if (game->map[y][x] == game->player_info.direction)
// 			{
// 				printf("P");
// 				draw_cub(game,size,draw_x,draw_y,0xCC6600FF);
// 				// printf("black");
// 			}
// 			x++;
// 			draw_x += size;
// 			x_distance--;
// 		}
// 		printf(" || x = %d y = %d", x, y);
// 		printf("\n");
// 		count++;
// 		x = game->player_info.x - x_vis;
// 		y++;
// 		draw_x = 0;
// 		draw_y += size;
// 		x_distance = x_vis * 2 + 1;
// 		y_distance--;
// 	}
// }