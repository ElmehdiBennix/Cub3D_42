/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Interpreter.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ebennix <ebennix@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/16 12:49:33 by ebennix           #+#    #+#             */
/*   Updated: 2023/11/17 18:30:43 by ebennix          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/cub3d.h"

// bool	white_spaces(char c)
// {
// 	if ()
// 		return (true);
// 	return (false);
// }

// ft_strlen(file[i]) > padding ? padding = ft_strlen(file[i]) : 0;


void	parser(t_data   *game, char **file)
{
    ft_bzero(game, sizeof(t_data));
	game->map = world_fields(file, game);
	valid_map(game); // i expect /n or map elements  // and get map
	map_padding(game);
	// padding for the map is done
	boundary_check(game);
    
}