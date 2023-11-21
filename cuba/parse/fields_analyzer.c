/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fields_analyzer.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ebennix <ebennix@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/16 12:59:47 by ebennix           #+#    #+#             */
/*   Updated: 2023/11/21 01:24:01 by ebennix          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/cub3d.h"

bool fill_colors(char *RGB ,t_RGB *color)
{
	int i = 0;
	int deco[3];

	char **splited = ft_split(RGB, ',');
	if (!splited)
		return (ft_fprintf(2,"failed split"), exit(1), 1);
	while (splited[i] && i < 3)
	{
		deco[i] = ft_atoi(splited[i]);
		if (deco[i] < 0 || deco[i] > 255)
			return (ft_fprintf(2,"between 0 and 255"), exit(1), 1);
		i++;
	}
	color->R = deco[0];
	color->G = deco[1];
	color->B = deco[2];
	return (true);
}

static bool	parse_colors(char *RGB)
{
	int i = 0;
	int quote = 0;
	bool color_field = false;

	while (RGB[i])
	{
		if (ft_isdigit(RGB[i]) == 1)
			color_field = true;
		else if (RGB[i] == ',' && color_field == true)
		{
			quote++;
			color_field = false;
		}
		else
			return (false);
		i++;
	}
	if (color_field == false || quote != 2 || (i < 5 || i > 11)) // 255,255,255
		return (false);
	
	return (true);
}

static bool	check_fields(t_data *game)
{
	if (game->North.content_Nullable == NULL)
		return (false);
	if (game->South.content_Nullable == NULL)
		return (false);
	if (game->West.content_Nullable == NULL)
		return (false);
	if (game->East.content_Nullable == NULL)
		return (false);
	if (game->C_Floor.content_Nullable == NULL || parse_colors(game->C_Floor.content_Nullable) == false)
		return (false);
	if (game->C_Ceiling.content_Nullable == NULL || parse_colors(game->C_Ceiling.content_Nullable) == false)
		return (false);
	fill_colors(game->C_Floor.content_Nullable, &game->C_Ceiling);
	fill_colors(game->C_Ceiling.content_Nullable, &game->C_Floor);
	return (true);
}


static char	*func(char *str)
{
	char *trimed = ft_strtrim(&str[2]," ");
	
	// ft_fprintf(2 ,"we got it trimed = |%s|\n", trimed);

	return (trimed);
}

static bool	elements_collect(char *line, int  *fields, t_data *game)
{
	// printf("line = |%s|\n", line);
	if (line && ft_strncmp(line, "NO ", 3) == 0)
		game->North.content_Nullable = func(line);
	else if (line && ft_strncmp(line, "SO ", 3) == 0)
		game->South.content_Nullable = func(line);
	else if (line && ft_strncmp(line, "WE ", 3) == 0)
		game->West.content_Nullable = func(line);
	else if (line && ft_strncmp(line, "EA ", 3) == 0)
		game->East.content_Nullable = func(line);
	else if (line && ft_strncmp(line, "F ", 2) == 0)
		game->C_Floor.content_Nullable = func(line);
	else if (line && ft_strncmp(line, "C ", 2) == 0)
		game->C_Ceiling.content_Nullable = func(line);
	else if (spaces(line , false) == true)
		return (true);
	else
		return (false);
	// printf("\n");
	(*fields)++;
	return (true);
}

char	**world_fields(char **file, t_data  *game) // gets fields alone and retuns head of map
{
	int fields = 0;
	unsigned int i = 0;


	while (file[i] && fields < 6)
	{
		// printf("%d\n",fields);
		if (elements_collect(file[i], &fields, game) == false)
			return (ft_fprintf(2," %d wrong fields",fields), exit(1), NULL);
		i++;
	}
	// printf("total fields = %d\n",fields);
	if (check_fields(game) == false)
		return (ft_fprintf(2,"too many fields"), exit(1), NULL);
	return (&file[i]);
}
