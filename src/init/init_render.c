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

void	init_line(t_line *line, int color)
{
	line->dx = abs(line->x1 - line->x0);
	line->dy = abs(line->y1 - line->y0);
	if (line->x0 < line->x1)
		line->sx = 1;
	else
		line->sx = -1;
	if (line->y0 < line->y1)
		line->sy = 1;
	else
		line->sy = -1;
	line->err = line->dx - line->dy;
	line->color = color;
}

void	init_ray(t_ray *ray, t_game *game, t_player *player, int x)
{
	double	camera_x;

	camera_x = 2 * x / (double)game->screen_width - 1;
	ray->dir_x = player->dir_x + player->plane_x * camera_x;
	ray->dir_y = player->dir_y + player->plane_y * camera_x;
	ray->map_x = (int)player->x;
	ray->map_y = (int)player->y;
	ray->delta_dist_x = fabs(1.0 / ray->dir_x);
	ray->delta_dist_y = fabs(1.0 / ray->dir_y);
	calculate_step_and_side_dist(ray, game->player);
	dda(ray, game->map);
	calculate_perp_dist(ray, game->player);
}

void	init_ray_line(t_line *line, t_ray *ray, t_player *player)
{
	line->x0 = player->x * TILE;
	line->y0 = player->y * TILE;
	line->x1 = (player->x + ray->dir_x * ray->perp_wall_dist) * TILE;
	line->y1 = (player->y + ray->dir_y * ray->perp_wall_dist) * TILE;
	init_line(line, GREEN);
}

void	init_draw(t_draw *draw, t_ray *ray, t_game *game)
{
	draw->line_height = (int)(game->screen_height / ray->perp_wall_dist);
	draw->draw_start = -draw->line_height / 2 + game->screen_height / 2;
	if (draw->draw_start < 0)
		draw->draw_start = 0;
	draw->draw_end = draw->line_height / 2 + game->screen_height / 2;
	if (draw->draw_end >= game->screen_height)
		draw->draw_end = game->screen_height - 1;
	draw->img = texture_side(game, ray);
}
