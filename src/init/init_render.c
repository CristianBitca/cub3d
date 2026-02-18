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

	line = ft_calloc(sizeof(t_line), 1);
	if (!line)
		return (0);
	line->x0 = player->x * TILE;
	line->y0 = player->y * TILE;
	line->x1 = x1;
	line->y1 = y1;
	line->dx = abs(x1 - line->x0);
	line->dy = abs(y1 - line->y0);
	if (line->x0 < x1)
		line->sx = 1;
	else
		line->sx = -1;
	if (line->y0 < y1)
		line->sy = 1;
	else
		line->sy = -1;
	line->err = line->dx - line->dy;
	line->color = color;
	return (line);
}

void	init_ray(t_ray **ray, t_player *player, int i, double width)
{
	double camera_x;

	*ray = ft_calloc(sizeof(t_ray), 1);
	if (!*ray)
		return ;
	camera_x = 2 * i / (double)width - 1;
	(*ray)->dir_x = player->dir_x + player->plane_x * camera_x;
	(*ray)->dir_y = player->dir_y + player->plane_y * camera_x;
	(*ray)->map_x = (int)player->x;
	(*ray)->map_y = (int)player->y;
	(*ray)->delta_dist_x = fabs(1.0 / (*ray)->dir_x);
	(*ray)->delta_dist_y = fabs(1.0 / (*ray)->dir_y);
}

void	init_ray_line(t_line **line, t_ray *ray, t_player *player)
{
	double hit_x;
	double hit_y;

	hit_x = player->x + ray->dir_x * ray->perp_wall_dist;
	hit_y = player->y + ray->dir_y * ray->perp_wall_dist;
	*line = init_line(player, (int)(hit_x * TILE), (int)(hit_y * TILE), GREEN);
}

void	calculate_step_and_side_dist(t_ray *ray, t_player *player)
{
	if (ray->dir_x < 0)
	{
		ray->step_x = -1;
		ray->side_dist_x = (player->x - ray->map_x) * ray->delta_dist_x;
	}
	else
	{
		ray->step_x = 1;
		ray->side_dist_x = (ray->map_x + 1.0 - player->x) * ray->delta_dist_x;
    }
	if (ray->dir_y < 0)
	{
		ray->step_y = -1;
		ray->side_dist_y = (player->y - ray->map_y) * ray->delta_dist_y;
	}
	else
	{
		ray->step_y = 1;
		ray->side_dist_y = (ray->map_y + 1.0 - player->y) * ray->delta_dist_y;
	}
}

void calculate_perp_dist(t_ray *ray, t_player *player)
{
    if (ray->side == 0)  // Vertical wall hit
        ray->perp_wall_dist = (ray->map_x - player->x + (1 - ray->step_x) / 2) / ray->dir_x;
    else  // Horizontal wall hit
        ray->perp_wall_dist = (ray->map_y - player->y + (1 - ray->step_y) / 2) / ray->dir_y;
}