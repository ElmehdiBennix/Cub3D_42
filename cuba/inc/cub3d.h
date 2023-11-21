/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3d.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ebennix <ebennix@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/20 06:21:16 by ebennix           #+#    #+#             */
/*   Updated: 2023/11/21 04:28:11 by ebennix          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CUB3D_H_
# define CUB3D_H_

# include "../../lib/inc/lib_42.h"
# include "../../MLX42/include/MLX42/MLX42.h"
# include "../inc/defin.h"
# include "../inc/structs.h"
# include <math.h>
// # include <time.h>

char	**read_file(char *str);
void    parser(t_data   *game, char **file); // might delete it and make it static 

char	**world_fields(char **file, t_data  *game);
void	valid_map(t_data *game);
void    map_padding(t_data *game);
void 	boundary_check(t_data *game);


// void	open_window(t_data *game);
int     drawing(void);


bool    init_textures(char *content ,mlx_texture_t   **texture);



bool    spaces(char *line ,bool new_line);
void    ft_error(void);



void	free_fields(t_data *game);
void	free_texture(t_data *game);

#endif