/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   structs.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ebennix <ebennix@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/13 09:57:52 by ebennix           #+#    #+#             */
/*   Updated: 2023/11/30 23:59:05 by ebennix          ###   ########.fr       */
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
	mlx_texture_t	*Faces[6];
	mlx_texture_t	*Gun_animation[6];
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

typedef struct s_images
{
	mlx_image_t		*world_3D;
	mlx_image_t		*HUD;

	mlx_image_t		*gun[6];
	int32_t 		gun_x;
	int32_t 		gun_y;
	bool 			gun_shoot;
	bool			gun_running;

	mlx_image_t		*Faces[6];
	bool			face_idle;

	mlx_image_t		*door[2];
	bool			enable_door;
}				t_images;

typedef struct s_data
{
// -> mlx Data
	mlx_t			*mlx;
// -> file_pase_Data
	char			**map;
	unsigned int	map_height;
	unsigned int	map_width;
	t_position		player_info; // take off and setup player using it
// -> player location Data
	t_state			player;
// -> fields data
	t_elements		North;
	t_elements		South;
	t_elements		West;
	t_elements		East;
	t_RGB		C_Floor;
	t_RGB		C_Ceiling;
// -> HUD_elemnts canvas
	t_textures		texs;
	t_images		canvas;

	unsigned int 	frames;
// -> rays Data
	t_Ray rays;
}					t_data;

#endif