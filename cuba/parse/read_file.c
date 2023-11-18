/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   read_file.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ebennix <ebennix@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/01 00:45:04 by ebennix           #+#    #+#             */
/*   Updated: 2023/11/18 02:12:09 by ebennix          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/cub3d.h"

bool map_head(char *line)
{
	int i = 0;

	while (line[i])
	{
		if (line[i] != ' ' && line[i] != '1' && line[i] != '0' && line[i] != '\n')
			return(false);
		i++;
	}
	// printf("line = %s char = %c\n", line ,line[i]);
	return(true);
}

bool spaces(char *line , bool new_line)
{
	int i = 0;

	while (line[i] && line[i] == ' ')
		i++;
	if (new_line == true && line[i] == '\n')
		return (true);
	else if (new_line == false && line[i] == '\0')
		return (true);
	return (false);
}

static char	**file_data(int fd) //,t_data *game)
{
	char	*str = NULL; /// loooooollllllllll C never fails to take me sanity away 0_0
	char	*row;
	bool	map_flag = false;

	while (true)
	{
		row = get_next_line(fd);
		if (row == NULL)
			break ;
		if (map_flag == false && spaces(row,true) == false && map_head(row) == true) // there is problem if trigged flasely
			map_flag = true;
		else if (row[0] == '\n' && map_flag == true) // not logical
			return (ft_fprintf(2 ,"new line in map\n"),exit(1),NULL); // or spaces problem field
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

char	**read_file(char *map_name)//, t_data *game)
{
	int		fd;
	char	*str;

	str = ft_strnstr(map_name, ".cub", ft_strlen(map_name));
	if (!str || ft_strncmp(str, ".cub", ft_strlen(str)) != 0)
		return (ft_fprintf(2, RED "Error : Map must end with \".cub\" extention." DEFAULT), exit(1) , NULL);
	fd = open(map_name, O_RDONLY);
	if (fd < 0)
		return (ft_fprintf(2, RED "Error : Failed to open map file." DEFAULT), exit(2) , NULL);
	return (file_data(fd));
	
	// (void) game;
	// printf(GREEN "DONNNEEEEEEE");
}

// allowed in map 0 1 N S E W 
// map should be closed with 1s empty spaces are allowed it can be eny shape