/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map_evaluator.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ebennix <ebennix@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/16 13:09:21 by ebennix           #+#    #+#             */
/*   Updated: 2023/11/17 18:30:09 by ebennix          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/cub3d.h"

bool	directions(char c)
{
	if (c == 'N' || c == 'S' || c == 'E' || c == 'W')
		return (true);
	return (false);
}

int		allowed_units(char c, int *player, t_data *game)
{
	if (c == '1' || c == '0' || c == ' ')
		return (0);
	else if (directions(c) == true)
	{
		game->player_info.direction = c;
		return ((*player)++ ,1);
	}
	return (-1);
}

bool	plus_check(t_data *game, int i, int j)
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

/// @brief what if map has /n and it got merged cuz of split it happening right now

void 	boundary_check(t_data *game)
{
	int i = 0;
	int j = 0;

	if (adbdoul_lewel(game->map[i]) == false)
		return (ft_fprintf(2,"map not closed at line %d = |%s|\n",i ,game->map[i]), exit(1));
		
	while (game->map[++i])
	{
		while (game->map[i][j])
		{
			if (game->map[i][j] == '0')
			{
				if (plus_check(game, i + 1, j) == false || plus_check(game, i - 1, j) == false ||
					plus_check(game, i, j + 1) == false || plus_check(game, i, j - 1) == false)
					return (ft_fprintf(2,"map not closed at line %d = |%s|\n",i ,game->map[i]), exit(1));
			}
			j++;
		}
		j = 0;
	}
}

char	*repeat_char(char c, int count)
{
    char*	repeater = malloc(count + 1);
    if (repeater != NULL) {
        memset(repeater, c, count);
        repeater[count] = '\0';
    }
    return repeater;
}

void map_padding(t_data *game)
{
	int i;

	i = 0;
	int padding = 0;
	while (game->map[i])
	{
		padding = game->map_width - ft_strlen(game->map[i]);
		// printf("padding %d \n",padding);
		if (padding > 0)
			game->map[i] = ft_strjoin(game->map[i], repeat_char(' ', padding));
		printf("line = %d = |%s|\n", i, game->map[i]);
		i++;
	}
}

void	valid_map(t_data *game) // leaks left
{
	int i = 0;
	int j = 0;
	int longest = 0;
	int player = 0;

	 // force new map after fields
	while (game->map[i])
	{
		// printf("game->map[%d] = |%s|\n",i,game->map[i]);
		while (game->map[i][j])
		{
			if (allowed_units(game->map[i][j], &player, game) == -1)
				return (ft_fprintf(2,"wrong simbols map"), exit(1));
			j++;
		}
		if (longest < j)
			longest = j;
		j = 0;
		i++;
	}
	if (player != 1)
		return (ft_fprintf(2,"wrong player"), exit(1));
	game->map_width = longest;
	game->map_height = i;
}