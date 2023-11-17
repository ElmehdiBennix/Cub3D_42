/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fields_analyzer.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ebennix <ebennix@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/16 12:59:47 by ebennix           #+#    #+#             */
/*   Updated: 2023/11/17 18:29:39 by ebennix          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/cub3d.h"

char	*func(char *str)
{
	char *trimed = ft_strtrim(&str[2]," ");
	
	// ft_fprintf(2 ,"we got it trimed = |%s|\n", trimed);

	return (trimed);
}


bool	elements_collect(char *line, int  *fields, t_data *game)
{
	// printf("before line = |%s|\n",line);
	if (line && ft_strncmp(line, "NO ", 3) == 0)
		game->North.content_Nullable = func(line); // increment field
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
	else
		return (false);
	// printf("\n");
	(*fields)++;
	return (true);
}

bool	check_fields(t_data *game)
{
	if (game->North.content_Nullable == NULL)
		return (false);
	if (game->South.content_Nullable == NULL)
		return (false);
	if (game->West.content_Nullable == NULL)
		return (false);
	if (game->East.content_Nullable == NULL)
		return (false);
	if (game->C_Floor.content_Nullable == NULL)
		return (false);
	if (game->C_Ceiling.content_Nullable == NULL)
		return (false);
	return (true);
}

char	**world_fields(char **file, t_data  *game) // gets fields alone and retuns the map
{
	int fields = 0;
	unsigned int i = 0;


	while (file[i] && fields < 6)
	{
		// printf("%d\n",fields);
		if (elements_collect(file[i], &fields, game) == false)
			return (ft_fprintf(2,"wrong fields"), exit(1), NULL);
		i++;
	}
	// printf("total fields = %d\n",fields);
	if (check_fields(game) == false)
		return (ft_fprintf(2,"too many fields"), exit(1), NULL);
	return (&file[i]);
}