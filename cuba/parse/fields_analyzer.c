/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fields_analyzer.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hasalam <hasalam@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/16 12:59:47 by ebennix           #+#    #+#             */
/*   Updated: 2023/12/05 19:44:10 by hasalam          ###   ########.fr       */
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
	color->R = deco[0];
	color->G = deco[1];
	color->B = deco[2];
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
	if (game->North.content_Nullable == NULL
		|| init_textures(game->North.content_Nullable,
			&(game->North.texture)) == false)
		return (ft_fprintf(2, "Error : Failed to read North texture.\n"),
			false);
	if (game->South.content_Nullable == NULL
		|| init_textures(game->South.content_Nullable,
			&(game->South.texture)) == false)
		return (ft_fprintf(2, "Error : Failed to read South texture.\n"),
			false);
	if (game->West.content_Nullable == NULL
		|| init_textures(game->West.content_Nullable,
			&(game->West.texture)) == false)
		return (ft_fprintf(2, "Error : Failed to read West texture.\n"), false);
	if (game->East.content_Nullable == NULL
		|| init_textures(game->East.content_Nullable,
			&(game->East.texture)) == false)
		return (ft_fprintf(2, "Error : Failed to read East texture.\n"), false);
	return (true);
}

bool	check_fields(t_data *game)
{
	if (check_fields_helper(game) == false)
		return (false);
	if (game->C_Floor.content_Nullable == NULL
		|| parse_colors(game->C_Floor.content_Nullable) == false)
		return (ft_fprintf(2, "Error : Failed to parse Floor color.\n"), false);
	if (game->C_Ceiling.content_Nullable == NULL
		|| parse_colors(game->C_Ceiling.content_Nullable) == false)
		return (ft_fprintf(2, "Error : Failed to parse ceiling color.\n"),
			false);
	if (fill_colors(game->C_Floor.content_Nullable, &game->C_Ceiling) == false
		|| fill_colors(game->C_Ceiling.content_Nullable,
			&game->C_Floor) == false)
		return (ft_fprintf(2, "Error : RGB values between 0 && 255.\n"), false);
	return (true);
}

bool	collect_fields(char *line, int *fields, t_data *game)
{
	if (line && ft_strncmp(line, "NO ", 3) == 0)
		game->North.content_Nullable = ft_strtrim(&line[2], " ");
	else if (line && ft_strncmp(line, "SO ", 3) == 0)
		game->South.content_Nullable = ft_strtrim(&line[2], " ");
	else if (line && ft_strncmp(line, "WE ", 3) == 0)
		game->West.content_Nullable = ft_strtrim(&line[2], " ");
	else if (line && ft_strncmp(line, "EA ", 3) == 0)
		game->East.content_Nullable = ft_strtrim(&line[2], " ");
	else if (line && ft_strncmp(line, "F ", 2) == 0)
		game->C_Floor.content_Nullable = ft_strtrim(&line[1], " ");
	else if (line && ft_strncmp(line, "C ", 2) == 0)
		game->C_Ceiling.content_Nullable = ft_strtrim(&line[1], " ");
	else if (spaces(line, false) == true)
		return (free(line), true);
	else
		return (ft_fprintf(2, "Error : Fields must start with 'NO' , 'SO' ,\
				'WE' , 'EA' , 'F' or 'C'."), close(2), false);
	free(line);
	(*fields)++;
	return (true);
}
