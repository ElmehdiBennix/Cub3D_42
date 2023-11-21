/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fields_analyzer.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ebennix <ebennix@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/16 12:59:47 by ebennix           #+#    #+#             */
/*   Updated: 2023/11/21 02:02:26 by ebennix          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/cub3d.h"

static bool fill_colors(char *RGB ,t_RGB *color)
{
	int i = 0;
	int deco[3];

	char **splited = ft_split(RGB, ',');
	if (!splited)
		return (false);
	while (splited[i] && i < 3)
	{
		deco[i] = ft_atoi(splited[i]);
		if (deco[i] < 0 || deco[i] > 255)
			return (false);
		i++;
	}
	color->R = deco[0];
	color->G = deco[1];
	color->B = deco[2];
	return (true);
}

static bool	parse_colors(char *RGB)
{
	int		i = 0;
	int		quote = 0;
	bool	rgb_field = false;

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

static bool	check_fields(t_data *game) // free all if bool returns false
{
	if (game->North.content_Nullable == NULL || init_textures(game->North.content_Nullable ,game->North.texture) == false)
		return (false);
	if (game->South.content_Nullable == NULL || init_textures(game->South.content_Nullable ,game->South.texture) == false)
		return (false);
	if (game->West.content_Nullable == NULL || init_textures(game->West.content_Nullable ,game->West.texture) == false)
		return (false);
	if (game->East.content_Nullable == NULL || init_textures(game->East.content_Nullable ,game->East.texture) == false)
		return (false);
	if (game->C_Floor.content_Nullable == NULL || parse_colors(game->C_Floor.content_Nullable) == false)
		return (false);
	if (game->C_Ceiling.content_Nullable == NULL || parse_colors(game->C_Ceiling.content_Nullable) == false)
		return (false);
	if (fill_colors(game->C_Floor.content_Nullable, &game->C_Ceiling) == false || fill_colors(game->C_Ceiling.content_Nullable, &game->C_Floor) == flase )
		return (false);
	return (true);
}

static bool	elements_collect(char *line, int  *fields, t_data *game)
{
	// printf("line = |%s|\n", line);
	if (line && ft_strncmp(line, "NO ", 3) == 0)
		game->North.content_Nullable = ft_strtrim(&line[2]," ");
	else if (line && ft_strncmp(line, "SO ", 3) == 0)
		game->South.content_Nullable = ft_strtrim(&line[2]," ");
	else if (line && ft_strncmp(line, "WE ", 3) == 0)
		game->West.content_Nullable = ft_strtrim(&line[2]," ");
	else if (line && ft_strncmp(line, "EA ", 3) == 0)
		game->East.content_Nullable = ft_strtrim(&line[2]," ");
	else if (line && ft_strncmp(line, "F ", 2) == 0)
		game->C_Floor.content_Nullable = ft_strtrim(&line[1]," ");
	else if (line && ft_strncmp(line, "C ", 2) == 0)
		game->C_Ceiling.content_Nullable = ft_strtrim(&line[1]," ");
	else if (spaces(line , false) == true)
		return (free(line) ,true);
	else
		return (false);
	// printf("\n");
	free (line);
	(*fields)++;
	return (true);
}

void	free_fields(t_data *game)
{
	free(game->North.content_Nullable);
	game->North.content_Nullable = NULL;
	free(game->South.content_Nullable);
	game->South.content_Nullable = NULL;
	free(game->West.content_Nullable);
	game->West.content_Nullable = NULL;
	free(game->East.content_Nullable);
	game->East.content_Nullable = NULL;
	free(game->C_Floor.content_Nullable);
	game->C_Floor.content_Nullable = NULL;
	free(game->C_Ceiling.content_Nullable);
	game->C_Ceiling.content_Nullable = NULL;
}

char	**world_fields(char **file, t_data  *game) // gets fields alone and retuns head of map
{
	int fields = 0;
	unsigned int i = 0;

	while (file[i] && fields < 6)
	{
		// printf("%d\n",fields);
		if (elements_collect(file[i], &fields, game) == false)
			break; // free fields // break loop
		i++;
	}
	// printf("total fields = %d\n",fields);
	if (check_fields(game) == false)
		return (ft_fprintf(2,"too many fields") ,free2d(&file[i]) ,free_fields(game), exit(1), NULL); // free fields content // and map 
	free_fields(game);
	return (&file[i]);
}

// leak free need error msgs
