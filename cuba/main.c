/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ebennix <ebennix@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/01 19:45:35 by ebennix           #+#    #+#             */
/*   Updated: 2023/11/20 05:04:46 by ebennix          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "inc/cub3d.h"


// #define red 0xFFFF0000
// #define green 0xFF00FF00
// #define blue 0xFF0000FF
// #define yellow 0xFFFFFF00
// #define white 0xFFFFFFFF
// #define black 0xFF000000

void 	draw_cub(t_data *game, int size , int _x, int _y, uint32_t color)
{
	int x = 0;
	int y = 0;
	
	while (y < size)
	{
		while (x < size)
		{
			mlx_put_pixel(game->img, _x + x , _y + y, color);
			x++;
		}
		x = 0;
		y++;
	}
}

 // proportional to the size of the map and move the map with keys
// instead of the player
void	draw_map(t_data *game, int size ,int _x, int _y)
{
	int x = 0;
	int y = 0;

	int moves_x = 0;
	int moves_y = 0;

	while (game->map[y])
	{
		while (game->map[y][x])
		{
			if (game->map[y][x] == '1')
				draw_cub(game,size,_x+x+moves_x,_y+y+moves_y,0x00FF00FF);
			else if (game->map[y][x] == '0')
				draw_cub(game,size,_x+x+moves_x,_y+y+moves_y,0x000000FF);
			// if (game->map[y][x] == game->player_info.direction)
			// 	draw_cub(game,2,_x+x+moves_x,_y+y+moves_y); // center the dot draw a cercle
			x++;
			moves_x += size;
		}
		moves_x = 0;
		x = 0;
		y++;
		moves_y += size;
	}
}

void	mini_map(t_data *game ,int x_vis, int y_vis) // impaire   /// 5 // 5  // drawing is all fucked up
{
	int x_distance = x_vis * 2 + 1;
	int y_distance = y_vis * 2 + 1;

	int x = game->player_info.x - x_vis;
	int y = game->player_info.y - y_vis;

	printf("PLAYER X = %d PLAYER Y = %d\n", game->player_info.x, game->player_info.y);
	printf("X = %d Y = %d\n", x ,y);
	printf("h = %d w = %d\n", game->map_height ,game->map_width);
	printf("##############################\n");

	const int size = 20;

	int draw_x = 0;
	int draw_y = 0;
	
	int count = 0;
	
	while (y_distance)
	{
		printf("line %d = ", count);
		while (x_distance)
		{
			if (x < 0 || y < 0 || (unsigned int) x >= game->map_width || (unsigned int) y >= game->map_height)
			{
				printf("*");
				draw_cub(game,size,draw_x,draw_y,0x000000FF);
				// printf("red");
			}
			else if (game->map[y][x] == '1')
			{
				printf("1");
				draw_cub(game,size,draw_x,draw_y,0xFFFFFFFF);
				// printf("green");
			}
			else if (game->map[y][x] == '0')
			{
				printf("0");
				draw_cub(game,size,draw_x,draw_y,0x66FFFFFF);
				// printf("blue");
			}
			else if (game->map[y][x] == game->player_info.direction)
			{
				printf("P");
				draw_cub(game,size,draw_x,draw_y,0xCC6600FF);
				// printf("black");
			}
			x++;
			draw_x += size;
			x_distance--;
		}
		printf(" || x = %d y = %d", x, y);
		printf("\n");
		count++;
		x = game->player_info.x - x_vis;
		y++;
		draw_x = 0;
		draw_y += size;
		x_distance = x_vis * 2 + 1;
		y_distance--;
	}
	
}

void	my_drawing(t_data *game)
{
	mlx_delete_image(game->mlx, game->img);
	game->img = mlx_new_image(game->mlx, game->mlx->width, game->mlx->height);
	// draw_map(game,16,20,20); // cant resize to a minimun set and maximum set
	mini_map(game, 5, 10); // segs becouse of window size

	// draw_cub(game,20,0,0,0xFFFFFFFF); //0x000000FF // 0x66FFFFFF // 0x0000CCCC // 0xCC6600FF

	mlx_image_to_window(game->mlx, game->img, 0, 0);
	// while(1);
}

void key_hooks(mlx_key_data_t keycode, t_data *game)
{
	if (keycode.key == MLX_KEY_UP && keycode.action == MLX_PRESS && game->map[game->player_info.y - 1][game->player_info.x] == '0')
	{
		game->map[game->player_info.y][game->player_info.x] = '0';
		game->player_info.y += -1;
		game->map[game->player_info.y][game->player_info.x] = game->player_info.direction;
	}
	else if (keycode.key == MLX_KEY_DOWN && keycode.action == MLX_PRESS && game->map[game->player_info.y + 1][game->player_info.x] == '0')
	{
		game->map[game->player_info.y][game->player_info.x] = '0';
		game->player_info.y += +1;
		game->map[game->player_info.y][game->player_info.x] = game->player_info.direction;
	}
	else if (keycode.key == MLX_KEY_RIGHT && keycode.action == MLX_PRESS && game->map[game->player_info.y][game->player_info.x + 1] == '0')
	{
		game->map[game->player_info.y][game->player_info.x] = '0';
		game->player_info.x += 1;
		game->map[game->player_info.y][game->player_info.x] = game->player_info.direction;
	}
	else if (keycode.key == MLX_KEY_LEFT && keycode.action == MLX_PRESS && game->map[game->player_info.y][game->player_info.x - 1] == '0')
	{
		game->map[game->player_info.y][game->player_info.x] = '0';
		game->player_info.x += -1;
		game->map[game->player_info.y][game->player_info.x] = game->player_info.direction;
	}
	else if (keycode.key == MLX_KEY_ESCAPE)
		exit(EXIT_SUCCESS);
}

int	main(int ac, char **av)
{
    t_data	game;
	
    if (ac != 2)
		return (ft_fprintf(2, RED "Error : supply the map file.\n" DEFAULT), 1);
	parser(&game, read_file(*(++av)));
    // init_images(game);
    // open_window(game);


	game.mlx = mlx_init(WIDTH, HEIGHT, "cuba", true);

	mlx_key_hook(game.mlx, (void *)key_hooks, &game);
	mlx_loop_hook(game.mlx, (void *)my_drawing, &game);

	mlx_loop(game.mlx);
	mlx_terminate(game.mlx);

	// merged 
	// drawing();
	return (0);
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