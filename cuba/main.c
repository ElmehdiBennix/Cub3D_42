/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ebennix <ebennix@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/01 19:45:35 by ebennix           #+#    #+#             */
/*   Updated: 2023/11/30 02:47:34 by ebennix          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "inc/cub3d.h"

static void draw_faces(t_data *game)
{
	if (game->frames % 80 == 0)
		game->canvas.face_idle = !game->canvas.face_idle;
	if (game->canvas.gun_shoot == true)
		game->canvas.Faces[5]->enabled = true;
	else if (game->player.walkD == 1 || game->player.walkD == -1)
		game->canvas.Faces[2]->enabled = true;
	else if (game->player.turnD == 1) // || game->player.mouseX - 500 > 10
		game->canvas.Faces[4]->enabled = true;
	else if (game->player.turnD == -1) // moouse face left
		game->canvas.Faces[3]->enabled = true;
	else
	{
		if (game->canvas.face_idle == false)
			game->canvas.Faces[0]->enabled = true;
		else
			game->canvas.Faces[1]->enabled = true;
	}
}

static void draw_gun(t_data *game)
{
	static int play = 0;
	int animation[7] = {1,2,3,4,5,4,3};

	if (game->canvas.gun_shoot == true)
	{
		game->canvas.gun[animation[play]]->enabled = true;
		game->canvas.gun[animation[play]]->instances->x = game->canvas.gun_x;
		if (game->frames % 8 == 0)
		{
			game->canvas.gun[animation[play]]->enabled = true;
			play++;
			if (play == 7)
			{
				play = 0;
				game->canvas.gun_shoot = false;
			}
		}
		return ;
	}
	else if (game->player.walkD == 1 || game->player.walkD == -1)
	{
		if (game->canvas.gun_running == false && game->canvas.gun_x < 680)
			game->canvas.gun_x += 4;
		else
		{
			game->canvas.gun_running = true;
			game->canvas.gun_x -= 4;
			if (game->canvas.gun_x < 580)
				game->canvas.gun_running = false;
		}
		game->canvas.gun[0]->instances->x = game->canvas.gun_x;
	}
	game->canvas.gun[0]->enabled = true;
}

static void	drawing(t_data *game)
{
	game->frames++;

	disable_images(game);
	update_state(game);
	castAllRays(game);
	generate3DMap(game);
	draw_gun(game);
	mini_map(game, 3, 3);
	draw_faces(game);
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
	gerphec(&game);

	// atexit(f);
	return (EXIT_SUCCESS);
}
// flip colors of c and floor
