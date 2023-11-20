/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   defin.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ebennix <ebennix@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/13 10:16:42 by ebennix           #+#    #+#             */
/*   Updated: 2023/11/21 00:30:17 by ebennix          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef DEFIN_H_
# define DEFIN_H_

# define true 1
# define false 0

# define WIDTH 1500
# define HEIGHT 1000

# define TILE_S 32


# define MAP_NUM_ROWS 12 // mine 
# define MAP_NUM_COLS 20 // mine 


# define MINIMAP 0.5

# define WINDOW_WIDTH (MAP_NUM_COLS * TILE_S) // add to stuct
# define WINDOW_HEIGHT (MAP_NUM_ROWS * TILE_S) // add to stuct

# define NUM_RAYS WIDTH

# define PI 3.14159265
# define TWO_PI 6.28318530
# define FOV_ANGLE (60 * (M_PI / 180))

/*******************************/

# define TEX_WIDTH 32
# define TEX_HEIGHT 32


#endif