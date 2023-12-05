/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ebennix <ebennix@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/01 19:45:35 by ebennix           #+#    #+#             */
/*   Updated: 2023/12/05 21:14:07 by ebennix          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "inc/cub3d.h"

static void	add_door(t_data *game, int i, int j)
{
	if (game->map[i + 1][j] == '1' && game->map[i - 1][j] == '1'
		&& game->map[i][j + 1] == '0' && game->map[i][j - 1] == '0')
		game->map[i][j] = 'D';
	if (game->map[i + 1][j] == '0' && game->map[i - 1][j] == '0'
		&& game->map[i][j + 1] == '1' && game->map[i][j - 1] == '1')
		game->map[i][j] = 'D';
}

void	close_doors(t_data *game, int frame)
{
	int	i;
	int	j;
	int	player_X;
	int	player_Y;

	i = 0;
	j = 0;
	if (frame == 0 || game->frames % frame == 0)
	{
		player_X = floor(game->player.x / TILE_S);
		player_Y = floor(game->player.y / TILE_S);
		while (game->map[++i] && (unsigned int)i < game->map_height - 1)
		{
			while (game->map[i][++j] && (unsigned int)j < game->map_width - 2)
			{
				if (player_X == j && player_Y == i)
					j++;
				else if (game->map[i][j] == '0')
					add_door(game, i, j);
			}
			j = 0;
		}
	}
}

static void	drawing(t_data *game)
{
	game->frames++;
	close_doors(game, 200);
	disable_images(game);
	update_state(game);
	cast_all_rays(game);
	generate3d_map(game);
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
	close_doors(game, 0);
	mlx_loop_hook(game->mlx, (void *)drawing, game);
	mlx_key_hook(game->mlx, (void *)key_events, game);
	mlx_set_cursor_mode(game->mlx, MLX_MOUSE_DISABLED);
	mlx_cursor_hook(game->mlx, mouse_event, game);
	mlx_mouse_hook(game->mlx, mouse_click, game);
	mlx_loop(game->mlx);
	mlx_terminate(game->mlx);
}

static void	parser(t_data *game, char **file)
{
	ft_bzero(game, sizeof(t_data));
	game->map = world_fields(file, game);
	valid_map(game);
	map_padding(game);
	boundary_check(game);
	game->map[game->player_info.y][game->player_info.x] = '0';
	setup(game);
}

int	main(int ac, char **av)
{
	t_data	game;

	if (ac != 2)
		return (ft_fprintf(2, RED "Error : supply the map file.\n" DEFAULT), 1);
	parser(&game, read_file(*(++av)));
	gerphec(&game);
	return (EXIT_SUCCESS);
}

// optimize this function mini_map
// change gimp ui
// add player in minimap and change colors of it
// add door getting close without closing on th players face
// fix door texture
// fix big map not rendering