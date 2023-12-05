/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   structs.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hasalam <hasalam@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/13 09:57:52 by ebennix           #+#    #+#             */
/*   Updated: 2023/12/05 18:17:44 by hasalam          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef STRUCTS_H_
# define STRUCTS_H_

typedef struct s_Ray
{
	float 			ray_angle;
	float 			wallHitX;
	float 			wallHitY;
	float 			distance;
	int 			wasHitVertical;
	int 			isRayfacingUp;
	int 			isRayfacingDown;
	int 			isRayfacingleft;
	int 			isRayfacingRight;
	int 			wallHitContent;
	mlx_texture_t	*text;
}				t_Ray[NUM_RAYS];

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
}				t_elements;

typedef struct s_position
{
	char			direction;

	int				x;
	int				y;
}				t_position;

typedef struct s_state
{
	float x;
	float y;
	int	mouseX;
	int	mouseY;
	int turnD;
	int walkD;
	int sideW;
	float rotationA;
	float walkS;
	float turnS;
}				t_state;

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

}				t_images;

typedef struct s_data
{
	mlx_t			*mlx;

	char			**map;
	unsigned int	map_height;
	unsigned int	map_width;
	t_position		player_info;


	t_state			player;
	
	t_elements		North;
	t_elements		South;
	t_elements		West;
	t_elements		East;
	t_RGB		C_Floor;
	t_RGB		C_Ceiling;

	t_images		canvas;
	mlx_texture_t	*door;
	unsigned int 	frames;

	t_Ray rays;
}					t_data;

typedef struct s_var
{
	//draw 3d
	float	corrDist;
	float	distProj;
	float	projWAll_H;
	int		wallStrip_H;
	int		wallTopPixel;
	int		wallBotPixel;
	int		i;
	int 	y;
	int		txtOffset_X;
	int		txtOffset_Y;
	int		distFromTop;
	//mini map
	float	cam_x;
	float	cam_y;
	int		draw_x;
	int 	draw_y;
	int 	x_dist;
	int 	y_dist;
	int 	x;
	//cast ray
	float	x_intercept;
	float	y_intercept;
	float	horzHitDist;
	float	vertHitDist;
	float	horzWall_Hit_X;
	float	horzWall_Hit_Y;
	float	vertWall_Hit_X;
	float	vertWall_Hit_Y;
	float	nxtHorzTouch_X;
	float	nxtHorzTouch_Y;
	float	nxtVertTouch_X;
	float	nxtVertTouch_Y;
	float	xstep;
	float	ystep;
	float	Check_x;
	float	Check_y;
	int		foundVertW_Hit;
	int		foundHorzW_Hit;
	int		vertWallcontnt;
	int		horzWallcontnt;
	int		isRayFac_D;
	int		isRayFac_U;
	int		isRayFac_R;
	int		isRayFac_L;
	//update state
	float	move_step;
	float	newp_x;
	float	newp_y;
	float	px;
	float	py;
	float	tmp;
	//init image
	bool    check;
	char	*path;
	//draw line
	float	dx;
	float	dy;
	float	step;
	//draw_gun
	int			animat[7];
}	t_var;

#endif