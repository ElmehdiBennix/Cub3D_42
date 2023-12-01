/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub_tools.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ebennix <ebennix@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/25 01:34:24 by ebennix           #+#    #+#             */
/*   Updated: 2023/12/01 20:13:01 by ebennix          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/cub3d.h"

int get_rgba(int r, int g, int b, int a)
{
    return (r << 24 | g << 16 | b << 8 | a);
}

int ft_get_color(int i ,int x, int y, t_data *game)
{
	int r;
	int g;
	int b;
	int a;

	a = 255;
	r = game->rays[i].text->pixels[(y * (game->rays[i].text->width * 4)) + (x * 4)];
	g = game->rays[i].text->pixels[(y * (game->rays[i].text->width * 4)) + (x * 4) + 1];
	b = game->rays[i].text->pixels[(y * (game->rays[i].text->width * 4)) + (x * 4) + 2];
	// color = &game.text1->pixels[(y * (game.text1->width * 4)) + (x * 4)];
	// printf("%d\n",player);
	// exit(0);
	// return (get_rgba(color[0], color[1], color[2], color[3]));
	return (get_rgba(r, g, b, a));
}