/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   read_map.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ebennix <ebennix@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/01 00:45:04 by ebennix           #+#    #+#             */
/*   Updated: 2023/11/16 10:38:39 by ebennix          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/cub3d.h"

// static	void	data_loop(t_data *game, char **res, int x, int len)
// {
// 	int		y;
// 	int		comp;

// 	y = 0;
// 	comp = ft_strlen(res[x]);
// 	if (res[x][y] != '1')
// 		exit_msg(2, "Map must be surrounded by walls.", RED, 1);
// 	while (res[x][++y] && y < comp - 1)
// 	{
// 		if ((res[x][y] == '1' || res[x][y] == '0' || res[x][y] == 'P'
// 				|| res[x][y] == 'C' || res[x][y] == 'E'
// 				|| res[x][y] == 'T') && len == comp)
// 			collect_data(game, res[x][y], x, y);
// 		else
// 			exit_msg(2, "Unallowed symbole or Map is not Rectangular.", RED, 1);
// 	}
// 	if (res[x][y] != '1')
// 		exit_msg(2, "Map must be surrounded by walls.", RED, 1);
// }

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

int		allowed(char c, int *player)
{
	if (c == '1' || c == '0' || c == ' ')
		return (0);
	else if (directions(c) == true)
		return ((*player)++ ,1);
	return (-1);
}

char	*repeat_char(char c, int count)
{
    char* repeater = malloc(count + 1); // +1 for the null-terminating character
    if (repeater != NULL) {
        memset(repeater, c , count);
        repeater[count] = '\0'; // null-terminating character
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
			if (allowed(file[i][j], &player) == -1)
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
	i = 0;
	int buffer = 0;
	while (file[i])
	{
		buffer = longest - ft_strlen(file[i]);
		// printf("buffer %d \n",buffer);
		if (buffer > 0)
			file[i] = ft_strjoin(file[i], repeat_char(' ', buffer));
		printf("|%s|\n",file[i]);
		i++;
	}
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

void 	boundary_check(t_data *game)
{
	

	
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