/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_images.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ebennix <ebennix@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/08 20:29:40 by ebennix           #+#    #+#             */
/*   Updated: 2023/11/21 01:40:24 by ebennix          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/cub3d.h"

bool    init_textures(char *content ,void   *texture)
{
    texture = mlx_load_png(content);
	if (!texture)
		return (false);
    return (true);
}