/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   structs.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ebennix <ebennix@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/13 09:57:52 by ebennix           #+#    #+#             */
/*   Updated: 2023/11/27 05:27:40 by ebennix          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef STRUCTS_H_
# define STRUCTS_H_


typedef struct s_Ray
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
	mlx_texture_t	*text;
}	t_Ray[NUM_RAYS];

// typedef struct Player
// {
// 	float x;
// 	float y;
// 	int	mouseX;
// 	int	mouseY;
// 	int turnD; // -1 for left, +1 for right
// 	int walkD; // -1 for back, +1 for front
// 	int sideW;
// 	float rotationA; // for retation angle
// 	float walkS; // for walk speed
// 	float turnS; // for turn speed
// 	mlx_t* mlx;
// 	mlx_image_t* img;
// 	mlx_texture_t* text1;
// 	mlx_texture_t* text2;
// 	mlx_texture_t* text3;
// 	mlx_texture_t* text4;
// 	t_Ray rays;
// }	t_Player;




typedef struct s_list
{
    mlx_texture_t	*content;
    struct s_list	*next;
}					t_list;

typedef struct s_draw
{
	mlx_image_t *canva;
// from
	float 	x1;
	float 	y1;
// to
	float 	x2;
	float 	y2;
	uint32_t 	color;
}				t_draw;

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

typedef struct s_textures
{
	mlx_texture_t	*HUD_template;
	t_list			*Faces;
	t_list			*Gun_animation;
	// add all textures hir
}				t_textures;

typedef struct s_state
{
	float x;
	float y;
	int	mouseX;
	int	mouseY;
	int turnD; // -1 for left, +1 for right
	int walkD; // -1 for back, +1 for front
	int sideW;
	float rotationA; // for retation angle
	float walkS; // for walk speed
	float turnS; // for turn speed
	
} t_state;

typedef struct s_data
{
// -> mlx Data
	mlx_t			*mlx;
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
	t_textures		texs;

	// mlx_image_t		*ray_casting;
	mlx_image_t		*Faces;
	mlx_image_t		*HUD;
	mlx_image_t		*gun;
	mlx_image_t		*world_3D;
// -> rays Data
	t_Ray rays;
}					t_data;

#endif