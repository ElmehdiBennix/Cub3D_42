/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map_evaluator.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ebennix <ebennix@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/16 13:09:21 by ebennix           #+#    #+#             */
/*   Updated: 2023/11/24 01:14:30 by ebennix          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/cub3d.h"

static char	*repeat_char(char c, int count)
{
    char*	repeater = malloc(count + 1);
    if (repeater != NULL) {
        memset(repeater, c, count);
        repeater[count] = '\0';
    }
    return repeater;
}

void	map_padding(t_data *game)
{
	int i;

	i = 0;
	int padding = 0;
	while (game->map[i])
	{
		padding = game->map_width - ft_strlen(game->map[i]);
		// printf("padding %d \n",padding);
		if (padding > 0)
			game->map[i] = join_em(game->map[i], repeat_char(' ', padding),3);
		// printf("line = %d = |%s|\n", i, game->map[i]);
		i++;
	}
}

//#######################//#######################//#######################//#######################

//static bool	white_spaces(char c)
// {
// 	if ()
// 		return (true);
// 	return (false);
// }

static bool		allowed_units(t_data *game, int i, int j, int *player)
{
	char c = game->map[i][j];
	if (c == '1' || c == '0' || c == ' ')
		return (true);
	else if (c == 'N' || c == 'S' || c == 'E' || c == 'W')
	{
		game->player_info.direction = c;
		game->player_info.x = j;
		game->player_info.y = i;
		return ((*player)++ ,true);
	}
	return (false);
}

void	valid_map(t_data *game) // leaks left
{
	int i = 0;
	int j = 0;
	int longest = 0;
	int player = 0;

	while (game->map[i])
	{
		// printf("game->map[%d] = |%s|\n",i,game->map[i]);
		while (game->map[i][j])
		{
			if (allowed_units(game, i, j, &player) == false)
				return (ft_fprintf(2,"Error : Wrong symbole '%c' .\n -> Map symboles :'1' '0' 'W','S','N','E'\n",game->map[i][j]),free_texture(game), free2d(game->map), exit(1));
			j++;
		}
		if (longest < j)
			longest = j;
		j = 0;
		i++;
	}
	if (player != 1)
		return (ft_fprintf(2,"Error : One player is allowed .\n  -> Player spawn direction symboles : 'W','S','N','E' .\n"),free_texture(game), free2d(game->map), exit(1));
	game->map_width = longest;
	game->map_height = i;
}

 // destroy the map textures