/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ebennix <ebennix@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/01 19:45:35 by ebennix           #+#    #+#             */
/*   Updated: 2023/12/06 17:25:39 by ebennix          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "inc/cub3d.h"

static void	drawing(t_data *game)
{
	update_state(game);
	cast_all_rays(game);
	generate3d_map(game);
}

static void	gerphec(t_data *game)
{
	game->mlx = mlx_init(WIDTH, HEIGHT, "Cub3D", false);
	if (!game->mlx)
		ft_error();
	init_images(game);
	mlx_loop_hook(game->mlx, (void *)drawing, game);
	mlx_key_hook(game->mlx, (void *)key_events, game);
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
