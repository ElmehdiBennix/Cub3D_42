/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   defin.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ebennix <ebennix@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/13 10:16:42 by ebennix           #+#    #+#             */
/*   Updated: 2023/11/19 02:03:04 by ebennix          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef DEFIN_H_
# define DEFIN_H_

# define true 1
# define false 0

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

// # define MAC_W 13
// # define MAC_A 0
// # define MAC_S 1
// # define MAC_D 2

// # define MAC_UP 126
// # define MAC_DOWN 125
// # define MAC_LEFT 123
// # define MAC_RIGHT 124

// # define MAC_ESC 53


// typedf enum s_keys
// {
//     MAC_W = 13,
//     MAC_A = 0,
//     MAC_S = 1,
//     MAC_D = 2,

//     MAC_UP = 126;
//     MAC_DOWN = 125,
//     MAC_LEFT = 123,
//     MAC_RIGHT = 124,
    
//     MAC_ESC = 53,

// }        t_keys;


#endif