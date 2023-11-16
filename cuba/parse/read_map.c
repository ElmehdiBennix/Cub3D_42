/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   read_map.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ebennix <ebennix@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/01 00:45:04 by ebennix           #+#    #+#             */
/*   Updated: 2023/11/16 08:54:28 by ebennix          ###   ########.fr       */
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

// static	void	valid_map(t_data *game, char **res)
// {
// 	int		x;
// 	int		len;

// 	x = 0;
// 	len = ft_strlen(res[x]);
// 	ones_row(res[x]);
// 	while (res[++x])
// 		data_loop(game, res, x, len);
// 	ones_row(res[--x]);
// 	game->height = ++x;
// 	game->width = len;
// 	set_check(game);
// }


char	*func(char *str)
{
	char *trimed = ft_strtrim(&str[2]," ");
	
	ft_fprintf(2 ,"we got it = %s\n", trimed);

	return (trimed);
}



bool	elements_collect(char *line, int  *fields, t_data *game)
{
	printf("line = %s\n",line);
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
	else if (line && ft_strncmp(line, "\n", 1) == 0)
		;
	else
		return (false);
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
	printf(RED"str = %s\n"DEFAULT,str);
	char **res = ft_split(str, '\n');
	free (str);
	if (!res)
		return (ft_fprintf(2 ,"failed to load map\n"),exit(1),NULL);
	return (res);
}

// bool	direction(char c)
// {
// 	if (c == 'N' || c == 'S' || c == 'E' || c == 'W')
// 		return (true);
// 	return (false);
// }

void	world_fields(char **file, t_data  *game) // gets fields alone and retuns the map
{
	int fields = 0;
	unsigned int i = 0;


	while (file[i] && fields < 6)
	{
		printf("%d\n",fields);
		if (elements_collect(file[i], &fields, game) == false)
			return (ft_fprintf(2,"wrong fields"), exit(1));
		i++;
	}
	if (fields > 6)
		return (ft_fprintf(2,"too many fields"), exit(1));

	
}

void	read_map(char *map_name, t_data *game)
{
	int		fd;
	char	*str;
	char	**file_content;

	str = ft_strnstr(map_name, ".cub", ft_strlen(map_name));
	if (!str || ft_strncmp(str, ".cub", ft_strlen(str)) != 0)
		return (ft_fprintf(2, RED "Error : Map must end with \".cub\" extention." DEFAULT), exit(1));
	fd = open(map_name, O_RDONLY);
	if (fd < 0)
		return (ft_fprintf(2, RED "Error : Failed to open map file." DEFAULT), exit(2));
	file_content = file_data(fd);
	// world_fields(file_content, game);
	
	(void) game;
	printf(GREEN "DONNNEEEEEEE");
}

// allowed in map 0 1 N S E W 
// map should be closed with 1s empty spaces are allowed it can be eny shape