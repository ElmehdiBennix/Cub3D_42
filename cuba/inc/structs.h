/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   structs.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ebennix <ebennix@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/13 09:57:52 by ebennix           #+#    #+#             */
/*   Updated: 2023/11/16 09:58:03 by ebennix          ###   ########.fr       */
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
// 	void			*top_v1;
// 	void			*top_v2;
// 	void			*down_v1;
// 	void			*down_v2;
// 	void			*right_v1;
// 	void			*right_v2;
// 	void			*left_v1;
// 	void			*left_v2;
// 	void			*down_right;
// 	void			*down_left;
// 	void			*block_v1;
// 	void			*block_v2;
// 	void			*full;

// 	int				img_width;
// 	int				img_height;
// }					t_walls;

// typedef struct s_textures
// {
// 	void			*floor;
// 	void			*bones;
// 	void			*rocks;
// 	void			*head_bone;
// 	void			*web;

// 	int				img_height;
// 	int				img_width;
// }					t_textures;

// typedef struct s_componets
// {
// 	t_list			*player;
// 	t_list			*exit;
// 	t_list			*collectible;
// 	t_list			*floor_enemy;
// 	t_list			*wall_enemy;
// 	t_list			*tmp;

// 	int				enemy_status;
// 	int				img_height;
// 	int				img_width;
// }					t_componets;

// typedef struct s_elements
// {
// 	unsigned int	identifiers;
// 	unsigned int	c_count;
// 	unsigned int	e_count;
// }					t_elements;

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