/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map_evaluator.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hasalam <hasalam@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/16 13:09:21 by ebennix           #+#    #+#             */
/*   Updated: 2023/12/06 01:09:28 by hasalam          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/cub3d.h"

static char	*repeat_char(char c, int count)
{
	char	*repeater;

	repeater = malloc(count + 1);
	if (repeater != NULL)
	{
		ft_memset(repeater, c, count);
		repeater[count] = '\0';
	}
	return (repeater);
}

void	map_padding(t_data *game)
{
	int	i;
	int	padding;

	i = 0;
	padding = 0;
	while (game->map[i])
	{
		padding = game->map_width - ft_strlen(game->map[i]);
		if (padding > 0)
			game->map[i] = join_em(game->map[i], repeat_char(' ', padding), 3);
		i++;
	}
}

static bool	allowed_units(t_data *game, int i, int j, int *player)
{
	char	c;

	c = game->map[i][j];
	if (c == '1' || c == '0' || c == ' ')
		return (true);
	else if (c == 'N' || c == 'S' || c == 'E' || c == 'W')
	{
		game->player_info.direction = c;
		game->player_info.x = j;
		game->player_info.y = i;
		return ((*player)++, true);
	}
	return (false);
}

void	valid_map_helper(t_data *game, struct s_valid_map *var)
{
	while (game->map[var->i])
	{
		while (game->map[var->i][var->j])
		{
			if (allowed_units(game, var->i, var->j, &var->player) == false)
				return (ft_fprintf(2, "Error : Wrong symbole '%c' ->\n\
						-> Map symboles :'1','0',' ','W','S','N','E'\n",
						game->map[var->i][var->j]), free_texture(game),
						free2d(game->map),
					exit(1));
			var->j++;
		}
		if (var->longest < var->j)
			var->longest = var->j;
		var->j = 0;
		var->i++;
	}
	if (var->player != 1)
		return (ft_fprintf(2, "Error : One player is allowed .\n\
				-> Player spawn direction symboles : 'W','S','N','E' .\n"),
			free_texture(game), free2d(game->map), exit(1));
}

void	valid_map(t_data *game)
{
	struct s_valid_map	var;

	var.i = 0;
	var.j = 0;
	var.longest = 0;
	var.player = 0;
	valid_map_helper(game, &var);
	game->map_width = var.longest;
	game->map_height = var.i;
}
