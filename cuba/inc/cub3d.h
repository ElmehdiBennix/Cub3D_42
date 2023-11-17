/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3d.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ebennix <ebennix@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/20 06:21:16 by ebennix           #+#    #+#             */
/*   Updated: 2023/11/16 12:54:33 by ebennix          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CUB3D_H_
# define CUB3D_H_

# include "../../lib/inc/lib_42.h"
# include "../inc/defin.h"
# include "../inc/structs.h"
// # include <time.h>
# include <mlx.h>


char	**read_map(char *str);
void    parse_map(t_data   *game, char **file)

// void	open_window(t_data *game);
// void	init_images(t_data *game);



// void	ones_row(char *res);
// void	collect_data(t_data *game, char data, int x, int y);
// void	set_check(t_data *game);
// int		under_wall(char **map, int x, int y, int flag);


// void	*protect_image(void *mlx_ptr, char *filename, int *width, int *height);
// void	init_images_1(t_data *game);
// void	init_images_2(t_data *game);
// void	init_images_3(t_data *game);
// void	init_images_4(t_data *game);
// void	free_game(t_data *game);
// int		exit_game(t_data *game);

#endif