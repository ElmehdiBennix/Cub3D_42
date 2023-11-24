/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   structs.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ebennix <ebennix@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/13 09:57:52 by ebennix           #+#    #+#             */
/*   Updated: 2023/11/24 01:21:25 by ebennix          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef STRUCTS_H_
# define STRUCTS_H_

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









// typedef struct s_list
// {
//     void			*content;
//     struct s_list	*next;
// }					t_list;







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

	mlx_texture_t	*texture;
}					t_elements;

typedef struct s_position
{
	char			direction;

	int				x;
	int				y;
}					t_position;

typedef struct s_state
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
	
} t_state;

typedef struct s_data
{
// -> mlx Data
	mlx_t			*mlx;
	int				win_width;
	int				win_height;
// -> file_pase_Data
	char			**map;
	unsigned int	map_height;
	unsigned int	map_width;
	t_position		player_info;
// -> player location Data
	t_state			player;
// -> textures and rgb colors Data
	t_elements		North;
	t_elements		South;
	t_elements		West;
	t_elements		East;

	t_RGB		C_Floor;
	t_RGB		C_Ceiling;
// -> HUD_elemnts canvas
	mlx_image_t		*HUD_Frame;
			// mlx_image_t		*img1;
			// mlx_image_t		*img2;
			// mlx_image_t		*img3;
// -> rays Data
	t_Ray rays;
}					t_data;

#endif