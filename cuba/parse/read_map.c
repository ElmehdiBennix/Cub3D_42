/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   read_map.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ebennix <ebennix@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/01 00:45:04 by ebennix           #+#    #+#             */
/*   Updated: 2023/11/17 20:31:49 by ebennix          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/cub3d.h"

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
		if (map_flag == false && (row[0] == ' ' || row[0] == '1' || row[0] == '0'))
		{
			// if (!str || str[ft_strlen(str) - 1] != '\n') seg
			// 	return (ft_fprintf(2 ,"%c == xx line in map\n",str[ft_strlen(str)]),exit(1),NULL);
			map_flag = true;
		}
		if (row[0] == '\n' && map_flag == true)
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

char	**read_map(char *map_name)//, t_data *game)
{
	int		fd;
	char	*str;
	// char	**file_content;

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