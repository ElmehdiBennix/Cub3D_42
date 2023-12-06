/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fields_analyzer.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hasalam <hasalam@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/16 12:59:47 by ebennix           #+#    #+#             */
/*   Updated: 2023/12/06 00:33:22 by hasalam          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/cub3d.h"

bool	fill_colors(char *RGB, t_RGB *color)
{
	int		i;
	int		deco[3];
	char	**splited;

	i = 0;
	splited = ft_split(RGB, ',');
	if (!splited)
		return (false);
	while (splited[i] && i < 3)
	{
		deco[i] = ft_atoi(splited[i]);
		if (deco[i] < 0 || deco[i] > 255)
			return (free2d(splited), free(splited), false);
		i++;
	}
	color->r = deco[0];
	color->g = deco[1];
	color->b = deco[2];
	free2d(splited);
	free(splited);
	return (true);
}

bool	parse_colors(char *RGB)
{
	int		i;
	int		quote;
	bool	rgb_field;

	i = 0;
	quote = 0;
	rgb_field = false;
	while (RGB[i])
	{
		if (ft_isdigit(RGB[i]) == 1)
			rgb_field = true;
		else if (RGB[i] == ',' && rgb_field == true)
		{
			quote++;
			rgb_field = false;
		}
		else
			return (false);
		i++;
	}
	if (rgb_field == false || quote != 2 || (i < 5 || i > 11))
		return (false);
	return (true);
}

bool	check_fields_helper(t_data *game)
{
	if (game->north.content_nullable == NULL
		|| init_textures(game->north.content_nullable,
			&(game->north.texture)) == false)
		return (ft_fprintf(2, "Error : Failed to read north texture.\n"),
			false);
	if (game->south.content_nullable == NULL
		|| init_textures(game->south.content_nullable,
			&(game->south.texture)) == false)
		return (ft_fprintf(2, "Error : Failed to read south texture.\n"),
			false);
	if (game->west.content_nullable == NULL
		|| init_textures(game->west.content_nullable,
			&(game->west.texture)) == false)
		return (ft_fprintf(2, "Error : Failed to read west texture.\n"), false);
	if (game->east.content_nullable == NULL
		|| init_textures(game->east.content_nullable,
			&(game->east.texture)) == false)
		return (ft_fprintf(2, "Error : Failed to read east texture.\n"), false);
	return (true);
}

bool	check_fields(t_data *game)
{
	if (check_fields_helper(game) == false)
		return (false);
	if (game->c_floor.content_nullable == NULL
		|| parse_colors(game->c_floor.content_nullable) == false)
		return (ft_fprintf(2, "Error : Failed to parse Floor color.\n"), false);
	if (game->c_ceiling.content_nullable == NULL
		|| parse_colors(game->c_ceiling.content_nullable) == false)
		return (ft_fprintf(2, "Error : Failed to parse ceiling color.\n"),
			false);
	if (fill_colors(game->c_floor.content_nullable, &game->c_ceiling) == false
		|| fill_colors(game->c_ceiling.content_nullable,
			&game->c_floor) == false)
		return (ft_fprintf(2, "Error : RGB values between 0 && 255.\n"), false);
	return (true);
}

bool	collect_fields(char *line, int *fields, t_data *game)
{
	if (line && ft_strncmp(line, "NO ", 3) == 0)
		game->north.content_nullable = ft_strtrim(&line[2], " ");
	else if (line && ft_strncmp(line, "SO ", 3) == 0)
		game->south.content_nullable = ft_strtrim(&line[2], " ");
	else if (line && ft_strncmp(line, "WE ", 3) == 0)
		game->west.content_nullable = ft_strtrim(&line[2], " ");
	else if (line && ft_strncmp(line, "EA ", 3) == 0)
		game->east.content_nullable = ft_strtrim(&line[2], " ");
	else if (line && ft_strncmp(line, "F ", 2) == 0)
		game->c_floor.content_nullable = ft_strtrim(&line[1], " ");
	else if (line && ft_strncmp(line, "C ", 2) == 0)
		game->c_ceiling.content_nullable = ft_strtrim(&line[1], " ");
	else if (spaces(line, false) == true)
		return (free(line), true);
	else
		return (ft_fprintf(2, "Error : Fields must start with 'NO' , 'SO' ,\
				'WE' , 'EA' , 'F' or 'C'."), close(2), false);
	free(line);
	(*fields)++;
	return (true);
}
