/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3d.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ebennix <ebennix@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/20 06:21:16 by ebennix           #+#    #+#             */
/*   Updated: 2023/11/18 00:33:01 by ebennix          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CUB3D_H_
# define CUB3D_H_

# include "../../lib/inc/lib_42.h"
# include "../inc/defin.h"
# include "../inc/structs.h"
// # include <time.h>
// # include <mlx.h>

char	**read_file(char *str);
void    parser(t_data   *game, char **file);

bool adbdoul_lewel(char *line);


char	**world_fields(char **file, t_data  *game); // gets fields alone and retuns the map
void	valid_map(t_data *game);
void    map_padding(t_data *game);
void 	boundary_check(t_data *game);

// void	open_window(t_data *game);

// void	*protect_image(void *mlx_ptr, char *filename, int *width, int *height);
// void	init_images(t_data *game);
// void	init_images_1(t_data *game);
// void	init_images_2(t_data *game);
// void	init_images_3(t_data *game);
// void	init_images_4(t_data *game);

// void	free_game(t_data *game);
// int	exit_game(t_data *game);

#endif