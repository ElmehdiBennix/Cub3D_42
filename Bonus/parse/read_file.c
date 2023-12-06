/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   read_file.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hasalam <hasalam@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/01 00:45:04 by ebennix           #+#    #+#             */
/*   Updated: 2023/12/06 01:10:27 by hasalam          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/cub3d.h"

bool	spaces(char *line, bool new_line)
{
	int	i;

	i = 0;
	while (line[i] && line[i] == ' ')
		i++;
	if (new_line == true && line[i] == '\n')
		return (true);
	else if (new_line == false && line[i] == '\0')
		return (true);
	return (false);
}

static bool	map_head(char *line)
{
	int	i;

	i = 0;
	while (line[i])
	{
		if (line[i] != ' ' && line[i] != '1' && line[i] != '0'
			&& line[i] != '\n')
			return (false);
		i++;
	}
	return (true);
}

static char	**file_data(int fd)
{
	struct s_file_data	var;

	var.str = NULL;
	var.row = NULL;
	var.map_flag = false;
	while (true)
	{
		var.row = get_next_line(fd);
		if (var.row == NULL)
			break ;
		if (var.map_flag == false && spaces(var.row, true) == false
			&& map_head(var.row) == true)
			var.map_flag = true;
		else if (var.row[0] == '\n' && var.map_flag == true)
			return (ft_fprintf(2, "Error : new line in map\n"), free(var.row),
				free(var.str), exit(1), NULL);
		var.str = join_em(var.str, var.row, 3);
	}
	close(fd);
	var.res = ft_split(var.str, '\n');
	free(var.str);
	if (!var.res)
		return (ft_fprintf(2, "Error : failed to load map\n"), exit(1), NULL);
	return (var.res);
}

char	**read_file(char *map_name)
{
	int		fd;
	char	*str;

	str = ft_strnstr(map_name, ".cub", ft_strlen(map_name));
	if (!str || ft_strncmp(str, ".cub", ft_strlen(str)) != 0)
		return (ft_fprintf(2,
				RED "Error : Map must end with \".cub\" extention." DEFAULT),
			exit(1), NULL);
	fd = open(map_name, O_RDONLY);
	if (fd < 0)
		return (ft_fprintf(2, RED "Error : Failed to open map file." DEFAULT),
			exit(2), NULL);
	return (file_data(fd));
}
