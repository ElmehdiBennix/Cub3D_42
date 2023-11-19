/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ebennix <ebennix@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/01 19:45:35 by ebennix           #+#    #+#             */
/*   Updated: 2023/11/20 00:35:19 by ebennix          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "inc/cub3d.h"

void 	draw_cub(t_data *game, int size , int _x, int _y)
{
	int x = 0;
	int y = 0;
	
	while (y < size)
	{
		while (x < size)
		{
			mlx_put_pixel(game->img, _x + x , _y + y, 0x0FFFFFF);
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
				draw_cub(game,size,_x+x+moves_x,_y+y+moves_y);
			if (game->map[y][x] == game->player_info.direction)
				draw_cub(game,2,_x+x+moves_x,_y+y+moves_y); // center the dot 
			x++;
			moves_x += size;
		}
		moves_x = 0;
		x = 0;
		y++;
		moves_y += size;
	}
}

void	my_drawing(t_data *game)
{
	mlx_delete_image(game->mlx, game->img);
	game->img = mlx_new_image(game->mlx, game->mlx->width, game->mlx->height);
	draw_map(game,20,20,20); // cant resize to a minimun set and maximum set
	mlx_image_to_window(game->mlx, game->img, 0, 0);
}

int	main(int ac, char **av)
{
    t_data	game;
	
    if (ac != 2)
		return (ft_fprintf(2, RED "Error : supply the map file.\n" DEFAULT), 1);
	parser(&game, read_file(*(++av)));
    // init_images(game);
    // open_window(game);

// 	mlx_focus(mlx_t* mlx);
// void mlx_get_monitor_size(int32_t index, int32_t* width, int32_t* height);

	
	game.mlx = mlx_init(WIDTH, HEIGHT, "cuba", true);
	


	// mlx_key_hook(game.mlx, ft_key, game);
	mlx_loop_hook(game.mlx, (void *)my_drawing, &game);

	mlx_loop(game.mlx);
	mlx_terminate(game.mlx);

	// merged 
	// drawing();
	return (0);
}

// must error messeges are generic and not specific to the error

// empty texture file but the file exists

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