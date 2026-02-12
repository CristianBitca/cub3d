/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_render.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cbitca <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/12 21:56:03 by cbitca            #+#    #+#             */
/*   Updated: 2026/02/12 21:56:04 by cbitca           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"
#include "parsing.h"
#include "render.h"
#include "utils.h"

t_line	*init_line(t_player *player, int x1, int y1, int color)
{
	t_line	*line;

	line = ft_calloc(sizeof(line), 1);
	if (!line)
		return (0);
	line->dx = abs(x1 - (int)player->x);
	line->dy = abs(y1 - (int)player->y);
	line->sx = ((int)player->x < x1) ? 1 : -1;
	line->sy = ((int)player->y < y1) ? 1 : -1;
	line->err = line->dx - line->dy;
	line->color = color;
	return (line);
}
