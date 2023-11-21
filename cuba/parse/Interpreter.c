/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Interpreter.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ebennix <ebennix@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/16 12:49:33 by ebennix           #+#    #+#             */
/*   Updated: 2023/11/21 02:32:42 by ebennix          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/cub3d.h"

static bool	plus_check(t_data *game, int i, int j)
{
	if (game->map[i][j] == '1' || game->map[i][j] == '0' || game->map[i][j] == game->player_info.direction)
		return (true);
	return (false);
}

static bool adbdoul_lewel(char *line)
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

	if (adbdoul_lewel(game->map[i]) == false)
		return (ft_fprintf(2,"Error : map must be surrounded by walls."), exit(1));
	while (game->map[++i] && (unsigned int)i < game->map_height - 1)
	{
		if (game->map[i][0] == '0')
			return (ft_fprintf(2,"Error : map must be surrounded by walls."), exit(1));
		while (game->map[i][j])
		{
			if (game->map[i][j] == '0' || game->map[i][j] == game->player_info.direction)
			{
				if (plus_check(game, i + 1, j) == false || plus_check(game, i - 1, j) == false ||
						plus_check(game, i, j + 1) == false || plus_check(game, i, j - 1) == false)
					return (ft_fprintf(2,"Error : map must be surrounded by walls."), exit(1));
			}
			j++;
		}
		j = 1;
	}
	if (adbdoul_lewel(game->map[i]) == false)
		return (ft_fprintf(2,"Error : map must be surrounded by walls."), exit(1));
}

//#######################//#######################//#######################//#######################

void	parser(t_data   *game, char **file)
{
    ft_bzero(game, sizeof(t_data));
	game->map = world_fields(file, game);
	valid_map(game);
	map_padding(game);
	boundary_check(game);
	
	// printf(GREEN "DDONE \n");
	// while(1);
}
