/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   structs.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ebennix <ebennix@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/13 09:57:52 by ebennix           #+#    #+#             */
/*   Updated: 2023/12/06 17:34:26 by ebennix          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef STRUCTS_H
# define STRUCTS_H

typedef struct s_Ray
{
	float			ray_angle;
	float			wall_hit_x;
	float			wall_hit_y;
	float			distance;
	int				was_hit_vertical;
	int				is_ray_facing_up;
	int				is_ray_facing_down;
	int				is_ray_facing_left;
	int				is_ray_facing_right;
	int				wall_hit_content;
	mlx_texture_t	*text;
}	t_Ray[NUM_RAYS];

typedef struct s_RGB
{
	char			*content_nullable;

	unsigned int	r;
	unsigned int	g;
	unsigned int	b;
}					t_RGB;

typedef struct s_elements
{
	char			*content_nullable;

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
	float			x;
	float			y;
	int				turn_d;
	int				walk_d;
	int				side_w;
	float			rotation_a;
	float			walk_s;
	float			turn_s;
	float			fov_angle;
}					t_state;
typedef struct s_data
{
	mlx_t			*mlx;

	char			**map;
	unsigned int	map_height;
	unsigned int	map_width;
	t_position		player_info;

	t_state			player;

	t_elements		north;
	t_elements		south;
	t_elements		west;
	t_elements		east;
	t_RGB			c_floor;
	t_RGB			c_ceiling;

	mlx_image_t		*world_3d;
	t_Ray			rays;
}					t_data;

struct				s_draw_3d
{
	float			corr_dist;
	float			dist_proj;
	float			proj_wall_h;
	int				wall_strip_h;
	int				wall_top_pixel;
	int				wall_bot_pixel;
	int				i;
	int				y;
	int				txt_offset_x;
	int				txt_offset_y;
	int				dist_from_top;
};

struct				s_cast_ray
{
	float			x_intercept;
	float			y_intercept;
	float			horz_hit_dist;
	float			vert_hit_dist;
	float			horz_wall_hit_x;
	float			horz_wall_hit_y;
	float			vert_wall_hit_x;
	float			vert_wall_hit_y;
	float			nxt_horz_touch_x;
	float			nxt_horz_touch_y;
	float			nxt_vert_touch_x;
	float			nxt_vert_touch_y;
	float			xstep;
	float			ystep;
	float			check_x;
	float			check_y;
	int				found_vertw_hit;
	int				found_horzw_hit;
	int				vert_wall_contnt;
	int				horz_wall_contnt;
	int				is_ray_fac_d;
	int				is_ray_fac_u;
	int				is_ray_fac_r;
	int				is_ray_fac_l;
};

struct				s_valid_map
{
	int				i;
	int				j;
	int				longest;
	int				player;
};

struct				s_file_data
{
	char			*str;
	char			*row;
	bool			map_flag;
	char			**res;
};

struct				s_update_state
{
	float			move_step;
	float			newp_x;
	float			newp_y;
	float			px;
	float			py;
	float			tmp;
};

struct				s_var
{
	int				i;
	int				j;
};

#endif