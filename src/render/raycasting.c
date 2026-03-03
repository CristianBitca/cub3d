/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   raycasting.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cbitca <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/16 14:14:42 by cbitca            #+#    #+#             */
/*   Updated: 2026/02/16 14:14:43 by cbitca           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"
#include "render.h"
#include "parsing.h"

// FUNCTION: calculate_step_and_side_dist
// ----------------------------
// Calculates the step direction and initial side distances for the DDA algorithm.
// Determines whether to step in the positive or negative X/Y direction and computes
// the distance from the player to the first side of the next map square along each axis.
//
// PARAMETERS
// ray    : Pointer to the ray structure containing direction, map position, and side distance data.
// player : Pointer to the player structure containing current player position.
//
// RETURN VALUE
// None. Updates the ray structure with step_x, step_y, side_dist_x, and side_dist_y.
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

// FUNCTION: dda
// ----------------------------
// Performs the DDA (Digital Differential Analyzer) algorithm to step through the map grid
// until a wall is hit. Determines which square of the map the ray intersects.
//
// PARAMETERS
// ray : Pointer to the ray structure containing map coordinates, side distances, and step info.
// map : 2D character array representing the map layout ('1' = wall, '0' = empty space).
//
// RETURN VALUE
// None. Updates the ray structure with map_x, map_y, and side of the wall hit.
void	dda(t_ray *ray, char **map)
{
	int	hit;

	hit = 0;
	while (hit == 0)
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
		if (map[ray->map_y][ray->map_x] == '1')
			hit = 1;
	}
}


// FUNCTION: calculate_perp_dist
// ----------------------------
// Calculates the perpendicular distance from the player to the wall that the ray hits.
// This distance is used to correct the fish-eye effect in raycasting.
//
// PARAMETERS
// ray    : Pointer to the ray structure containing side and map coordinates.
// player : Pointer to the player structure containing current player position.
//
// RETURN VALUE
// None. Updates ray->perp_wall_dist with the perpendicular distance to the wall.
void	calculate_perp_dist(t_ray *ray, t_player *player)
{
	double	wall_x;

	if (ray->side == 0)
	{
		wall_x = (ray->map_x - player->x + (1 - ray->step_x) / 2);
		ray->perp_wall_dist = wall_x / ray->dir_x;
	}
	else
	{
		wall_x = (ray->map_y - player->y + (1 - ray->step_y) / 2);
		ray->perp_wall_dist = wall_x / ray->dir_y;
	}
}
