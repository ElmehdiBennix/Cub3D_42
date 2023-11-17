/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Cub3d.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hasalam <hasalam@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/29 15:08:23 by hasalam           #+#    #+#             */
/*   Updated: 2023/11/17 16:55:12 by hasalam          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CUB3D_H
# define CUB3D_H

# include "MLX42/include/MLX42/MLX42.h"
# include <math.h>
# include <stdlib.h>
# include <stdio.h>
# include <unistd.h>
# include <limits.h>

# define WIDTH 1500
# define HEIGHT 1000

# define TILE_S 32
# define MAP_NUM_ROWS 12
# define MAP_NUM_COLS 20

# define MINIMAP 0.5

# define WINDOW_WIDTH (MAP_NUM_COLS * TILE_S)
# define WINDOW_HEIGHT (MAP_NUM_ROWS * TILE_S)

# define NUM_RAYS WIDTH

# define PI 3.14159265
# define TWO_PI 6.28318530
# define FOV_ANGLE (60 * (M_PI / 180))

/*******************************/

# define TEX_WIDTH 32
# define TEX_HEIGHT 32

typedef struct Ray
{
	float rayAngle;
	float wallHitX;
	float wallHitY;
	float distance;
	int wasHitVertical;
	int isRayfacingUp;
	int isRayfacingDown;
	int isRayfacingleft;
	int isRayfacingRight;
	int wallHitContent;
}	t_Ray[NUM_RAYS];

typedef struct Player
{
	float x;
	float y;
	float width;
	float height;
	int turnD; // -1 for left, +1 for right
	int walkD; // -1 for back, +1 for front
	float rotationA; // for retation angle
	float walkS; // for walk speed
	float turnS; // for turn speed
	mlx_t* mlx;
	mlx_image_t* img;
	mlx_texture_t* text1;
	mlx_texture_t* text2;
	t_Ray rays;
}	t_Player;


#endif