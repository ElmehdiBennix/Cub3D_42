/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ebennix <ebennix@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/01 19:45:35 by ebennix           #+#    #+#             */
/*   Updated: 2023/11/24 23:09:50 by ebennix          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "inc/cub3d.h"

static void 	draw(t_draw	*draw)
{
	while (draw->y1 < draw->y2)
	{
		while (draw->x1 < draw->x2)
		{
			mlx_put_pixel(draw->canva, draw->x1 , draw->y1, draw->color);
			draw->x1++;
		}
		draw->x1 = 0;
		draw->y2++;
	}
}

void draw_lines(t_draw *draw)
{
	printf("x1 = %u y1 = %u x2 = %u y2 = %u\n", draw->x1, draw->y1, draw->x2, draw->y2);
	double deltaX = draw->x2 - draw->x1;
	double deltaY = draw->y2 - draw->y1;

	int pixels = fabs(deltaX) > fabs(deltaY) ? fabs(deltaX) : fabs(deltaY);

	deltaX /= pixels;
	deltaY /= pixels;

	double pixelX = draw->x1;
	double pixelY = draw->y1;
	
	while (pixels)
	{
	    mlx_put_pixel(draw->canva, pixelX , pixelY, draw->color);
	    pixelX += deltaX;
	    pixelY += deltaY;
	    --pixels;
	}
}

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



// static void render_player()
// {
	
// }

static void	my_drawing(t_data *game)
{
	mlx_delete_image(game->mlx, game->HUD_Frame);
	game->HUD_Frame = mlx_new_image(game->mlx, game->mlx->width, game->mlx->height);

	// mini_map(game, 5, 5); // segs becouse of window size
	t_draw draw = {game->HUD_Frame, 50, 50, 100, 0, 0x00FF00FF};
	// draw_lines(&draw);
	
	if (!game->HUD_Frame || (mlx_image_to_window(game->mlx, game->HUD_Frame, 0, 0)) < 0)
		ft_error();
}

void key_events(mlx_key_data_t keycode, t_data *game)
{
	if (keycode.key == MLX_KEY_UP && (keycode.action == MLX_PRESS || keycode.action == MLX_REPEAT))
		game->player.walkD = 1;
	else if (keycode.key == MLX_KEY_UP && keycode.action == MLX_RELEASE)
		game->player.walkD = 0;
	else if (keycode.key == MLX_KEY_DOWN && (keycode.action == MLX_PRESS || keycode.action == MLX_REPEAT))
		game->player.walkD = -1;
	else if (keycode.key == MLX_KEY_DOWN && keycode.action == MLX_RELEASE)
		game->player.walkD = 0;
	else if (keycode.key == MLX_KEY_RIGHT && (keycode.action == MLX_PRESS || keycode.action == MLX_REPEAT))
		game->player.turnD = 1;
	else if (keycode.key == MLX_KEY_RIGHT && keycode.action == MLX_RELEASE)
		game->player.turnD = 0;
	else if (keycode.key == MLX_KEY_LEFT && (keycode.action == MLX_PRESS || keycode.action == MLX_REPEAT))
		game->player.turnD = -1;
	else if (keycode.key == MLX_KEY_LEFT && keycode.action == MLX_RELEASE)
		game->player.turnD = 0;
	else if (keycode.key == MLX_KEY_ESCAPE)
		exit(EXIT_SUCCESS);
}

static void setup(t_data	*game)
{
	game->player.x = game->player_info.x * TILE_S + (TILE_S / 2);
	game->player.y = game->player_info.y * TILE_S + (TILE_S / 2);
	printf("player location -> x = %f y = %f\n/n", game->player.x, game->player.y);

	game->player.turnD = 0;
	game->player.walkD = 0;
	game->player.rotationA = M_PI / 2; // setup this to be the direction of the player
	game->player.walkS = 1.0f;
	game->player.turnS = 2 * (M_PI / 180);
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
	// atexit(f);
	parser(&game, read_file(*(++av)));
    // init_images(game); // if we added some textures
    // open_window(game);
	// game.map[game.player_info.y][game.player_info.x] = '0';
	setup(&game);
	game.mlx = mlx_init(WIDTH, HEIGHT, "Cub3D", false);
	if (!game.mlx)
		ft_error();
	mlx_key_hook(game.mlx, (void *)key_events, &game);
	mlx_loop_hook(game.mlx, (void *)my_drawing, &game);
	mlx_loop(game.mlx);
	mlx_terminate(game.mlx);

	// ft_helper(&game);

	return (EXIT_SUCCESS);
}


// empty texture file but the file exist























// #define WIDTH 512
// #define HEIGHT 512

// static mlx_image_t* image;

// // -----------------------------------------------------------------------------

// int32_t ft_pixel(int32_t r, int32_t g, int32_t b, int32_t a)
// {
//     return (r << 24 | g << 16 | b << 8 | a);
// }

// void ft_randomize(void* param)
// {
// 	for (int32_t i = 0; i < image->width; ++i)
// 	{
// 		for (int32_t y = 0; y < image->height; ++y)
// 		{
// 			uint32_t color = ft_pixel(
// 				rand() % 0xFF, // R
// 				rand() % 0xFF, // G
// 				rand() % 0xFF, // B
// 				rand() % 0xFF  // A
// 			);
// 			mlx_put_pixel(image, i, y, color);
// 		}
// 	}
// }

// void ft_hook(void* param)
// {
// 	mlx_t* mlx = param;

// 	if (mlx_is_key_down(mlx, MLX_KEY_ESCAPE))
// 		mlx_close_window(mlx);
// 	if (mlx_is_key_down(mlx, MLX_KEY_UP))
// 		image->instances[0].y -= 5;
// 	if (mlx_is_key_down(mlx, MLX_KEY_DOWN))
// 		image->instances[0].y += 5;
// 	if (mlx_is_key_down(mlx, MLX_KEY_LEFT))
// 		image->instances[0].x -= 5;
// 	if (mlx_is_key_down(mlx, MLX_KEY_RIGHT))
// 		image->instances[0].x += 5;
// }

// // -----------------------------------------------------------------------------

// int32_t main(int32_t argc, const char* argv[])
// {
// 	mlx_t* mlx;

// 	// Gotta error check this stuff
// 	if (!(mlx = mlx_init(WIDTH, HEIGHT, "MLX42", true)))
// 	{
// 		puts(mlx_strerror(mlx_errno));
// 		return(EXIT_FAILURE);
// 	}
// 	if (!(image = mlx_new_image(mlx, 128, 128)))
// 	{
// 		mlx_close_window(mlx);
// 		puts(mlx_strerror(mlx_errno));
// 		return(EXIT_FAILURE);
// 	}
// 	if (mlx_image_to_window(mlx, image, 0, 0) == -1)
// 	{
// 		mlx_close_window(mlx);
// 		puts(mlx_strerror(mlx_errno));
// 		return(EXIT_FAILURE);
// 	}
	
// 	mlx_loop_hook(mlx, ft_randomize, mlx);
// 	mlx_loop_hook(mlx, ft_hook, mlx);

// 	mlx_loop(mlx);
// 	mlx_terminate(mlx);
// 	return (EXIT_SUCCESS);
// }