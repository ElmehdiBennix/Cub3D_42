/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub_tools.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hasalam <hasalam@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/25 01:34:24 by ebennix           #+#    #+#             */
/*   Updated: 2023/12/06 01:11:27 by hasalam          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/cub3d.h"

int	get_rgba(int r, int g, int b, int a)
{
	return (r << 24 | g << 16 | b << 8 | a);
}

int	ft_get_color(int i, int x, int y, t_data *game)
{
	int	r;
	int	g;
	int	b;
	int	total;

	total = y * (game->rays[i].text->width * 4) + (x * 4);
	r = game->rays[i].text->pixels[total];
	g = game->rays[i].text->pixels[total + 1];
	b = game->rays[i].text->pixels[total + 2];
	return (get_rgba(r, g, b, 255));
}

void	update_state(t_data *game)
{
	struct s_update_state	var;

	game->player.rotation_a += game->player.turn_d * game->player.turn_s;
	var.move_step = game->player.walk_d * game->player.walk_s;
	var.newp_x = cos(game->player.rotation_a) * var.move_step;
	var.newp_y = sin(game->player.rotation_a) * var.move_step;
	var.px = game->player.x + var.newp_x;
	var.py = game->player.y + var.newp_y;
	if (!check_walls(game, var.px, var.py, 0))
	{
		game->player.x = var.px;
		game->player.y = var.py;
	}
	var.tmp = game->player.rotation_a + game->player.side_w
		* game->player.turn_s;
	var.move_step = game->player.side_w * game->player.walk_s;
	var.newp_x = cos(var.tmp + (90 * (M_PI / 180))) * var.move_step;
	var.newp_y = sin(var.tmp + (90 * (M_PI / 180))) * var.move_step;
	var.px = game->player.x + var.newp_x;
	var.py = game->player.y + var.newp_y;
	if (!check_walls(game, var.px, var.py, 0))
	{
		game->player.x = var.px;
		game->player.y = var.py;
	}
}

void	disable_images(t_data *game)
{
	game->canvas.gun[0]->enabled = false;
	game->canvas.gun[1]->enabled = false;
	game->canvas.gun[2]->enabled = false;
	game->canvas.gun[3]->enabled = false;
	game->canvas.gun[4]->enabled = false;
	game->canvas.gun[5]->enabled = false;
	game->canvas.faces[0]->enabled = false;
	game->canvas.faces[1]->enabled = false;
	game->canvas.faces[2]->enabled = false;
	game->canvas.faces[3]->enabled = false;
	game->canvas.faces[4]->enabled = false;
	game->canvas.faces[5]->enabled = false;
	game->canvas.hud->enabled = false;
}

char	**world_fields(char **file, t_data *game)
{
	int				fields;
	unsigned int	i;

	fields = 0;
	i = 0;
	while (file[i] && fields < 6)
	{
		if (collect_fields(file[i], &fields, game) == false)
			break ;
		i++;
	}
	if (check_fields(game) == false)
		return (free2d(&file[i]), free(file), free_fields(game),
			free_texture(game), exit(1), NULL);
	free_fields(game);
	return (&file[i]);
}
