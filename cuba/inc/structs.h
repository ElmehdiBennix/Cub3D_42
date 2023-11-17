/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   structs.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ebennix <ebennix@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/13 09:57:52 by ebennix           #+#    #+#             */
/*   Updated: 2023/11/17 18:16:43 by ebennix          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef STRUCTS_H_
# define STRUCTS_H_

typedef struct s_list
{
    void			*content;
    struct s_list	*next;
}					t_list;

// typedef struct s_walls
// {
// 	void			*TEX_NORTH;
// 	void			*TEX_;
// 	void			*TEX_WEST;
// 	void			*TEX_SOUTH;

// 	int				img_width;
// 	int				img_height;
// }					t_walls;


typedef struct 	s_RGB
{
	char 			*content_Nullable;

	unsigned int	R;
	unsigned int	G;
	unsigned int	B;
}			  	t_RGB;

typedef struct s_elements
{
	char 	*content_Nullable;

	void	*texture;
}					t_elements;

typedef struct s_position
{
	char			direction;
	
	int				x;
	int				y;
}					t_position;

typedef struct s_data
{
	// void			*mlx;
	// void			*mlx_win;

	char			**map;
	unsigned int	map_height;
	unsigned int	map_width;

	t_elements		North;
	t_elements		South;
	t_elements		West;
	t_elements		East;

	t_RGB		C_Floor;
	t_RGB		C_Ceiling;
	t_position	player_info;
}					t_data;

#endif