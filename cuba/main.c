/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ebennix <ebennix@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/01 19:45:35 by ebennix           #+#    #+#             */
/*   Updated: 2023/11/17 18:36:09 by ebennix          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "inc/cub3d.h"

int	main(int ac, char **av)
{
    t_data	game;
	
    if (ac == 2)
    {
    	// game = (t_data *)ft_calloc(sizeof(t_data), 1);
    	// if (!game)
		// {
    	// 	ft_fprintf(2, "memory allocation failed.");
		// 	exit(1);
		// }
    	
		parser(&game, read_map(*(++av)));
    	// open_window(game);
    	// init_images(game);
    }
	ft_fprintf(2, RED "Error : supply the map file.\n" DEFAULT);
	return (0);
}


// empty texture file but the file exists