/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ebennix <ebennix@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/01 19:45:35 by ebennix           #+#    #+#             */
/*   Updated: 2023/11/19 04:33:47 by ebennix          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "inc/cub3d.h"

void 	draw_cub(t_data *game)
{
	int x = 0;
	int y = 0;

	const int cube_size = 50;

	while (y < cube_size + 50 )
	{
		while (x < cube_size + 50)
		{
			mlx_put_pixel(game->img, x+20, y+20, 0x00FFFFF);
			printf("x = %d, y = %d\n", x, y);
			x++;
		}
		x = 0;
		y++;
	}
}

int	main(int ac, char **av)
{
    t_data	game;
	
    if (ac != 2)
		return (ft_fprintf(2, RED "Error : supply the map file.\n" DEFAULT), 1);
	// game = (t_data *)ft_calloc(sizeof(t_data), 1);
    // if (!game)
	// {
    // 	ft_fprintf(2, "memory allocation failed.");
	// 	exit(1);
	// }
    // init_images(game);
    // open_window(game);
	parser(&game, read_file(*(++av)));
	game.mlx = mlx_init(WIDTH, HEIGHT, "cuba",false);
	game.img = mlx_new_image(game.mlx, 500, 500);
	mlx_image_to_window(game.mlx, game.img, 0, 0);

	draw_cub(&game);
	// mlx_put_pixel(game.img, 200, 200, 0xFFFFFFFF);

	// // mlx_key_hook(game.mlx, ft_key, game);
	// // mlx_loop_hook(game.mlx, draw, game);

	mlx_loop(game.mlx);
	mlx_terminate(game.mlx);
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
// 	// if (!(mlx = mlx_init(WIDTH, HEIGHT, "MLX42", true)))
// 	// {
// 	// 	puts(mlx_strerror(mlx_errno));
// 	// 	return(EXIT_FAILURE);
// 	// }
// 	// if (!(image = mlx_new_image(mlx, 128, 128)))
// 	// {
// 	// 	mlx_close_window(mlx);
// 	// 	puts(mlx_strerror(mlx_errno));
// 	// 	return(EXIT_FAILURE);
// 	// }
// 	// if (mlx_image_to_window(mlx, image, 0, 0) == -1)
// 	// {
// 	// 	mlx_close_window(mlx);
// 	// 	puts(mlx_strerror(mlx_errno));
// 	// 	return(EXIT_FAILURE);
// 	// }
	
// 	mlx_loop_hook(mlx, ft_randomize, mlx);
// 	mlx_loop_hook(mlx, ft_hook, mlx);

// 	mlx_loop(mlx);
// 	mlx_terminate(mlx);
// 	return (EXIT_SUCCESS);
// }