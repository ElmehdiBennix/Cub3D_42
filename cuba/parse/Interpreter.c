/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Interpreter.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ebennix <ebennix@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/16 12:49:33 by ebennix           #+#    #+#             */
/*   Updated: 2023/11/18 02:40:57 by ebennix          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/cub3d.h"

static bool	plus_check(t_data *game, int i, int j)
{
	if (game->map[i][j] == '1' || game->map[i][j] == '0' ||
			game->map[i][j] == game->player_info.direction)
		return (true);
	printf("i = %d j = %d, char %c , player = %c\n", i, j,game->map[i][j],game->player_info.direction);
	return (false);
}

bool adbdoul_lewel(char *line)
{
	int i;
	
	i = 0;
	while (line[i])
	{
		if (line[i] != '1' && line[i] != ' ')
		{
			printf("|%d|\n", line[i]);
			return (false);
		}
		i++;
	}
	return (true);
}

void 	boundary_check(t_data *game)
{
	int i = 0;
	int j = 0;

	if (adbdoul_lewel(game->map[i]) == false) // check for 0 in j
		return (ft_fprintf(2,"map not closed at line %d = |%s|\n",i ,game->map[i]), exit(1));
	while (game->map[++i] && (unsigned int)i < game->map_height - 1)
	{
		if (game->map[i][0] == '0')
			return (ft_fprintf(2,"map not closed at line %d = |%s|\n",i ,game->map[i]), exit(1));
		while (game->map[i][j])
		{
			if (game->map[i][j] == '0' || game->map[i][j] == game->player_info.direction)
			{
				if (plus_check(game, i + 1, j) == false || plus_check(game, i - 1, j) == false ||
					plus_check(game, i, j + 1) == false || plus_check(game, i, j - 1) == false)
					return (ft_fprintf(2,"map not closed at line %d = |%s|\n",i ,game->map[i]), exit(1));
			}
			j++;
		}
		j = 1;
	}
	if (adbdoul_lewel(game->map[i]) == false)
		return (ft_fprintf(2,"map not closed at line %d = |%s|\n",i ,game->map[i]), exit(1));
}

//#######################//#######################//#######################//#######################

// ft_strlen(file[i]) > padding ? padding = ft_strlen(file[i]) : 0;

void	parser(t_data   *game, char **file)
{
    ft_bzero(game, sizeof(t_data));
	game->map = world_fields(file, game); // ef eny fail free bool expressions
	valid_map(game); // i expect /n or map elements  // and get map
	map_padding(game);
	boundary_check(game);
	printf(GREEN"DONE\n");
}
