/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Interpreter.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ebennix <ebennix@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/16 12:49:33 by ebennix           #+#    #+#             */
/*   Updated: 2023/11/30 21:16:03 by ebennix          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/cub3d.h"

// static bool	plus_check(t_data *game, int i, int j) // implement a true + check
// {
// 	if (game->map[i][j] == '1' || game->map[i][j] == '0' || game->map[i][j] == game->player_info.direction)
// 		return (true);
// 	return (false);
// }

static int	plus_check(t_data *game, int i, int j) // implement a true + check
{
	int check = 0;

	if (game->map[i + 1][j] == '1' || game->map[i + 1][j] == '0' || game->map[i + 1][j] == game->player_info.direction)
		check++;
	if (game->map[i - 1][j] == '1' || game->map[i - 1][j] == '0' || game->map[i - 1][j] == game->player_info.direction)
		check++;
	if (game->map[i][j + 1] == '1' || game->map[i][j + 1] == '0' || game->map[i][j + 1] == game->player_info.direction)
		check++;
	if (game->map[i][j - 1] == '1' || game->map[i][j - 1] == '0' || game->map[i][j - 1] == game->player_info.direction)
		check++;
	return (check);
}

static bool first_line(char *line)
{
	int i;
	
	i = 0;
	if (!line || !line[0])
		return (false);
	while (line[i])
	{
		if (line[i] != '1' && line[i] != ' ')
			return (false);
		i++;
	}
	return (true);
}

void 	boundary_check(t_data *game)
{
	int i = 0;
	int j = 0;

	if (first_line(game->map[i]) == false)
		return (ft_fprintf(2,"Error : map must be surrounded by walls."),free_texture(game), free2d(game->map), exit(1));
	while (game->map[++i] && (unsigned int)i < game->map_height - 1)
	{
		if (game->map[i][0] == '0')
			return (ft_fprintf(2,"Error : map must be surrounded by walls."),free_texture(game), free2d(game->map), exit(1));
		while (game->map[i][j])
		{
			if (game->map[i][j] == '0' || game->map[i][j] == game->player_info.direction)
			{
				if (plus_check(game, i , j) != 4)
					return (ft_fprintf(2,"Error : map must be surrounded by walls."), free2d(game->map), exit(1));
			}
			j++;
		}
		j = 1;
	}
	if (first_line(game->map[i]) == false)
		return (ft_fprintf(2,"Error : map must be surrounded by walls."),free_texture(game), free2d(game->map), exit(1));
}

//#######################//#######################//#######################//#######################

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
	game->player.turnS = 1 * (M_PI / 180);
}


void	parser(t_data   *game, char **file)
{
    ft_bzero(game, sizeof(t_data));
	game->map = world_fields(file, game);
	valid_map(game);
	map_padding(game);
	boundary_check(game);
	game->map[game->player_info.y][game->player_info.x] = '0';
	setup(game);
}
