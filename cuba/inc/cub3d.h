/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3d.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hasalam <hasalam@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/20 06:21:16 by ebennix           #+#    #+#             */
/*   Updated: 2023/12/05 20:21:18 by hasalam          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CUB3D_H_
# define CUB3D_H_

# include "../../lib/inc/lib_42.h"
# include "../../MLX42/include/MLX42/MLX42.h"
# include "../inc/defin.h"
# include "../inc/structs.h"
# include <math.h>

bool    spaces(char *line, bool new_line);
char	**read_file(char *str);

char	**world_fields(char **file, t_data  *game);
bool	collect_fields(char *line, int *fields, t_data *game);
bool	check_fields(t_data *game);
bool	check_fields_helper(t_data *game);
void	valid_map(t_data *game);
void    map_padding(t_data *game);
void 	boundary_check(t_data *game);

bool    init_textures(char *content ,mlx_texture_t   **texture);
void    init_images(t_data *game);
void    disable_images(t_data *game);

void	mini_map(t_data *game ,double x_vis, double y_vis);

void	draw_line(mlx_image_t *img, struct s_draw_line *arg);

int     get_rgba(int r, int g, int b, int a);
int     ft_get_color(int i ,int x, int y, t_data *game);

void	mouse_event(double x, double y, void *param);
void	mouse_click(mouse_key_t b, action_t a, modifier_key_t m, void* p);
void    update_state(t_data *game);
void    key_events(mlx_key_data_t keycode, t_data *game);

void	cast_all_rays(t_data *game);
void	cast_ray_helper1(t_data *game, t_var *var, float ray_a);
void	cast_ray_helper2(t_data *game, t_var *var);
void	cast_ray_helper3(t_data *game, t_var *var, float ray_a);
void	cast_ray_helper4(t_data *game, t_var *var);
void	cast_ray_helper5(t_data *game, t_var *var);
void	generate3d_map(t_data *game);

void    setup(t_data	*game);

void    draw_gun(t_data *game);
void    draw_faces(t_data *game);

void    ft_error(void);
void	free_fields(t_data *game);
void	free_texture(t_data *game);

float	normalize_angle(float angle);
float	distancebetween_points(float x1, float y1, float x2, float y2);
int		check_walls(t_data *game, float px, float py, int flag);
int     check_walls1(t_data *game, float px, float py);
int     check_walls2(t_data *game, float px, float py);

#endif