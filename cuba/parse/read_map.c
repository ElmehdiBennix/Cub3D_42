/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   read_map.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ebennix <ebennix@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/01 00:45:04 by ebennix           #+#    #+#             */
/*   Updated: 2023/11/16 12:07:07 by ebennix          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/cub3d.h"

// bool	white_spaces(char c)
// {
// 	if ()
// 		return (true);
// 	return (false);
// }

bool	directions(char c)
{
	if (c == 'N' || c == 'S' || c == 'E' || c == 'W')
		return (true);
	return (false);
}

int		allowed_units(char c, int *player)
{
	if (c == '1' || c == '0' || c == ' ')
		return (0);
	else if (directions(c) == true)
		return ((*player)++ ,1);
	return (-1);
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

static	void	valid_map(t_data *game, char **file) // leaks left
{
	int i = 0;
	int j = 0;
	int longest = 0;
	int player = 0;
	(void) game;
 // force new map after fields
	while (file[i])
	{
		// printf("file[%d] = |%s|\n",i,file[i]);
		while (file[i][j])
		{
			if (allowed_units(file[i][j], &player) == -1)
				return (ft_fprintf(2,"wrong simbols map"), exit(1));
			if (player == 1)
				game->player_info.direction = file[i][j];
			j++;
		}
		if (longest < j)
			longest = j;
		j = 0;
		i++;
	}
	if (player != 1)
		return (ft_fprintf(2,"wrong player"), exit(1));
	i = 0;
	int buffer = 0;
	while (file[i])
	{
		buffer = longest - ft_strlen(file[i]);
		// printf("buffer %d \n",buffer);
		if (buffer > 0)
			file[i] = ft_strjoin(file[i], repeat_char(' ', buffer));
		printf("line = %d = |%s|\n", i, file[i]);
		i++;
	}
	game->map_width = longest;
	game->map_height = i;
	game->map = file;
}
// ft_strlen(file[i]) > padding ? padding = ft_strlen(file[i]) : 0;


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
	// else if (line && ft_strncmp(line, "\n", 1) == 0)
	// 	;
	else
		return (false);
	// printf("\n");
	(*fields)++;
	return (true);
}


static char	**file_data(int fd) //,t_data *game)
{
	char	*str = NULL; /// loooooollllllllll C never fails to take me sanity away 0_0
	char	*row;

	while (true)
	{
		row = get_next_line(fd);
		if (row == NULL)
			break ;
		str = ft_strjoin(str, row);
		free(row);
	}
	close(fd);
	char **res = ft_split(str, '\n');
	free (str);
	if (!res)
		return (ft_fprintf(2 ,"failed to load map\n"),exit(1),NULL);
	return (res);
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

bool	plus_check(t_data *game, int i, int j)
{
	if (game->map[i][j] == '1' || game->map[i][j] == '0' ||
			game->map[i][j] == game->player_info.direction)
		return (true);
	return (false);
}

bool adbdoul_lewel(char *line)
{
	int i;
	
	i = 0;
	while (line[i])
	{
		if (line[i] != '1' || line[i] != ' ')
			return (false);
		i++;
	}
	return (true);
}

/// @brief what if map has /n and it got merged cuz of split it happening right now

void 	boundary_check(t_data *game)
{
	int i = 1;
	int j = 0;

	// if (adbdoul_lewel(game->map[i]) == false)
		
	while (game->map[i])
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
		i++;
	}
	
}

void	world_fields(char **file, t_data  *game) // gets fields alone and retuns the map
{
	int fields = 0;
	unsigned int i = 0;


	while (file[i] && fields < 6)
	{
		// printf("%d\n",fields);
		if (elements_collect(file[i], &fields, game) == false)
			return (ft_fprintf(2,"wrong fields"), exit(1));
		i++;
	}
	// printf("total fields = %d\n",fields);
	if (check_fields(game) == false)
		return (ft_fprintf(2,"too many fields"), exit(1));
	valid_map(game ,&file[i]); // i expect /n or map elements  // and get map
	// padding for the map is done
	boundary_check(game);
	
}

void	read_map(char *map_name, t_data *game)
{
	int		fd;
	char	*str;
	// char	**file_content;

	str = ft_strnstr(map_name, ".cub", ft_strlen(map_name));
	if (!str || ft_strncmp(str, ".cub", ft_strlen(str)) != 0)
		return (ft_fprintf(2, RED "Error : Map must end with \".cub\" extention." DEFAULT), exit(1));
	fd = open(map_name, O_RDONLY);
	if (fd < 0)
		return (ft_fprintf(2, RED "Error : Failed to open map file." DEFAULT), exit(2));
	world_fields(file_data(fd), game);
	
	(void) game;
	printf(GREEN "DONNNEEEEEEE");
}

// allowed in map 0 1 N S E W 
// map should be closed with 1s empty spaces are allowed it can be eny shape