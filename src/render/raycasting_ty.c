/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   raycasting_ty.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tyamano <tyamano@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/19 19:21:56 by tyamano           #+#    #+#             */
/*   Updated: 2026/02/19 21:07:01 by tyamano          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"
#include "render.h"
#include "parsing.h"

void	draw_wall_stripe(t_game, *game, t_ray *ray, int *draw_start, int *draw_end)
{
	int	y;

	y = *draw_start;
	while (y < *draw_end)
	{
		if (ray->side == 0)
			put_pixel(game->img, x, y, RED);
		else
			put_pixel(game->img, x, y, GREEN);
		y++;
	}
}

void	get_dist_and_height(t_game *game, t_ray *ray, int *draw_start, int *draw_end)
{
	int	line_height;

	if (ray->side == 0)
		ray->perp_wall_dist = (ray->map_x - game->player->x + (1 - ray->step_x) / 2) / ray->dir_x;
	else
		ray->perp_wall_dist = (ray->map_y - game->player->y + (1 - ray->step_y) / 2) / ray->dir_y;
	line_height = (int)(game->screen_height / ray.perp_wall_dist);
	*draw_start = -line_height / 2 + game->screen_height / 2;
	if (*draw_start < 0)
		*draw_start = 0;
	*draw_end = line_height / 2 + game->screen_height / 2;
	if (*draw_end >= game->screen_height)
		*draw_end = game->screen_height - 1;
}

void	perform_dda(t_game *game, t_ray *ray)
{
	while (ray->hit == 0)
	{
		if (ray->side_dist_x < ray->side_dist_y)
		{
			ray->side_dist_x += ray->delta_dist_x;
			ray->map_x += ray->step_x;
			ray->side = 0;
		}
		else
		{
			ray->side_dist_y += ray->delta_dist_y;
			ray->map_y += ray->step_y;
			ray->side = 1;
		}
		if (game->map[ray->map_y][ray->map_x] == '1')
			ray->hit = 1;
	}	
}

void	get_initial_side_dist(t_game *game, t_ray *ray)
{
	if (ray->dir_x < 0)
	{
		ray->step_x = -1;
		ray->side_dist_x = (game->player->x - ray->map_x) * ray->delta_dist_x;
	}
	else
	{
		ray->step_x = 1;
		ray->side_dist_x = (ray->map_x + 1.0 - game->player->x) * ray->delta_dist_x;
	}
	if (ray->dir_y < 0)
	{
		ray->step_y = -1;
		ray->side_dist_y = (game->player->y - ray->map_y) * ray->delta_dist_y;
	}
	else
	{
		ray->step_y = 1;
		ray->side_dist_y = (ray->map_y + 1.0 - game->player->y)
		* ray->delta_dist_y;
	}
}

void	init_ray(t_game *game, int x, t_ray *ray)
{
	double	camera_x;

	camera_x = 2 * x / (double)game->screen_width - 1;
	ray->dir_x = game->player->dir_x + game->player->plane_x * camera_x;
	ray->dir_y = game->player->dir_y + game->player->plane_y * camera_x;
	ray->map_x = (int)game->player->x;
	ray->map_y = (int)game->player->y;
	if (ray->dir_x == 0)
		ray->delta_dist_x = 1e30;
	else 
		ray->delta_dist_x = fabs(1 / ray->dir_x);
	if (ray->dir_y == 0)
		ray->delta_dist_y = 1e30;
	else
		ray->delta_dist_y = fabs(1 / ray->dir_y);
	ray->hit = 0;
	get_initial_side_dist(game, ray);
}

void	raycast(t_game *game)
{
	int 	x;
	t_ray	ray;
	int		draw_start;
	int		draw_end;
	
	x = -1;
	while (++x < game->screen_width)
	{
		init_ray(game, x, &ray);
		perform_dda(game, &ray);
		get_dist_and_height(game, &ray, &draw_start, &draw_end);
		draw_wall_stripe(game, &ray, &draw_start, &draw_end);
		x++;
	}
}