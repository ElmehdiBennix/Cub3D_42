/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ebennix <ebennix@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/01 19:45:35 by ebennix           #+#    #+#             */
/*   Updated: 2023/11/25 01:32:55 by ebennix          ###   ########.fr       */
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

static void draw_lines(t_draw *draw)
{
	printf("x1 = %f y1 = %f x2 = %f y2 = %f\n", draw->x1, draw->y1, draw->x2, draw->y2);
	double deltaX = draw->x2 - draw->x1;
	double deltaY = draw->y2 - draw->y1;

	int pixels = fabs(deltaX) > fabs(deltaY) ? fabs(deltaX) : fabs(deltaY);

	deltaX /= pixels;
	deltaY /= pixels;

	double pixelX = draw->x1;
	double pixelY = draw->y1;
	
	while (pixels)
	{
	    mlx_put_pixel(draw->canva, pixelX , pixelY, draw->color); // skip first pixel becouse of the player visual diffect
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

static void update(t_data *game)
{
	game->player.rotationA += game->player.turnS * game->player.turnD;

	float move = game->player.walkD * game->player.walkS;
	printf("move = %f\n", move);
	game->player.x += cos(game->player.rotationA) * move;
	game->player.y += sin(game->player.rotationA) * move;
	printf("x = %f y = %f\n", game->player.x, game->player.y);
}

static void	my_drawing(t_data *game)
{
	mlx_delete_image(game->mlx, game->HUD_Frame);
	game->HUD_Frame = mlx_new_image(game->mlx, game->mlx->width, game->mlx->height);

	// mini_map(game, 5, 5); // segs becouse of window size
	t_draw draw = { game->HUD_Frame, game->player.x,
					game->player.y,
					game->player.x + (cos(game->player.rotationA) * 50),
					game->player.y + (sin(game->player.rotationA) * 50),
					0x00FF00FF };
	draw_lines(&draw);
	update(game);
	
	if (!game->HUD_Frame || (mlx_image_to_window(game->mlx, game->HUD_Frame, 0, 0)) < 0)
		ft_error();
}

static void key_events(mlx_key_data_t keycode, t_data *game) // maybe better controls
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
	printf("player location -> x = %f y = %f\n", game->player.x, game->player.y);

	game->player.turnD = 0;
	game->player.walkD = 0;
	game->player.rotationA = M_PI / 2; // setup this to be the direction of the player
	printf("rotation angle = %f\n\n", game->player.rotationA);
	game->player.walkS = 1.0f;
	game->player.turnS = 2 * (M_PI / 180); // 2 degrees per frame
}

// void f()
// {
// 	system("leaks cub3d");
// }

static void	gerphec(t_data *game)
{
	setup(&game);
	game->mlx = mlx_init(WIDTH, HEIGHT, "Cub3D", false);
	if (!game->mlx)
		ft_error();
	mlx_key_hook(game->mlx, (void *)key_events, &game);
	mlx_loop_hook(game->mlx, (void *)my_drawing, &game);
	mlx_loop(game->mlx);
	mlx_terminate(game->mlx);
}


int	main(int ac, char **av)
{
    t_data	game;
	
    if (ac != 2)
		return (ft_fprintf(2, RED "Error : supply the map file.\n" DEFAULT), 1);

	parser(&game, read_file(*(++av)));
	// gerphec(&game);
	
    // init_images(game); // if we added some textures
    // open_window(game);


	// ft_helper(&game);

	// atexit(f);
	return (EXIT_SUCCESS);
}
