/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ebennix <ebennix@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/01 19:45:35 by ebennix           #+#    #+#             */
/*   Updated: 2023/11/16 09:16:07 by ebennix          ###   ########.fr       */
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
		ft_bzero(&game, sizeof(t_data));
    	read_map(*(++av), &game);
    	// open_window(game);
    	// init_images(game);
    }
	ft_fprintf(2, RED "Error : supply the map file.\n" DEFAULT);
	return (0);
}
