/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cbitca <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/23 18:51:42 by cbitca            #+#    #+#             */
/*   Updated: 2026/02/23 18:51:43 by cbitca           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"
#include "render.h"
#include "parsing.h"

// FUNCTION: texture_side
// ----------------------------
// Determines which wall texture should be used based on the side of the wall hit by the ray.
//
// LOGIC
// - If the ray hits a vertical wall (side == 0):
//     - dir_x > 0 → East wall texture
//     - dir_x <= 0 → West wall texture
// - If the ray hits a horizontal wall (side != 0):
//     - dir_y > 0 → South wall texture
//     - dir_y <= 0 → North wall texture
//
// RETURN VALUE
// Returns a pointer to the corresponding t_img structure representing the wall texture.
t_img	*texture_side(t_game *game, t_ray *ray)
{
	if (ray->side == 0)
	{
		if (ray->dir_x > 0)
			return (game->asset->EA);
		else
			return (game->asset->WE);
	}
	else
	{
		if (ray->dir_y > 0)
			return (game->asset->SO);
		else
			return (game->asset->NO);
	}
}

// FUNCTION: calc_texture_x
// ----------------------------
// Calculates the horizontal coordinate (img_x) on the texture corresponding to the point where the ray hits a wall.
//
// LOGIC
// - Computes the exact position (wall_x) where the wall was hit:
//     - Vertical wall (side == 0): wall_x = player y-position + perpendicular wall distance * ray dir_y
//     - Horizontal wall (side != 0): wall_x = player x-position + perpendicular wall distance * ray dir_x
// - Converts wall_x to texture space by multiplying by the texture width.
// - Flips img_x if the wall is hit from a certain direction to correct texture orientation.
//
// PARAMETERS
// draw   : Pointer to the draw structure storing the texture coordinates.
// ray    : Pointer to the ray structure containing ray direction and hit side.
// player : Pointer to the player structure for current position.
// width  : Width of the texture in pixels.
//
// RETURN VALUE
// Sets draw->img_x to the correct horizontal texture coordinate.
void	calc_texture_x(t_draw *draw, t_ray *ray, t_player *player, int width)
{
	double	wall_x;

	if (ray->side == 0)
		wall_x = player->y + ray->perp_wall_dist * ray->dir_y;
	else
		wall_x = player->x + ray->perp_wall_dist * ray->dir_x;
	wall_x -= floor(wall_x);
	draw->img_x = (int)(wall_x * (double)width);
	if ((ray->side == 0 && ray->dir_x > 0)
		|| (ray->side == 1 && ray->dir_y < 0))
		draw->img_x = width - draw->img_x - 1;
}

// FUNCTION: draw_ceiling
// ----------------------------
// Draws the ceiling portion of the screen column at position x with a specified color.
//
// LOGIC
// - Iterates from the top of the screen (y = 0) down to draw->draw_start (the start of the wall).
// - Sets each pixel to the given ceiling color using put_pixel.
//
// PARAMETERS
// game  : Pointer to the game structure containing the image buffer.
// draw  : Pointer to the draw structure containing the wall start position.
// x     : Horizontal screen coordinate (column) being drawn.
// color : Color value to fill the ceiling pixels.
//
// RETURN VALUE
// No return value. Modifies the image buffer directly by drawing ceiling pixels.
void	draw_ceiling(t_game *game, t_draw *draw, int x, int color)
{
	int	y;

	y = 0;
	while (y < draw->draw_start)
	{
		put_pixel(game->img, x, y, color);
		y++;
	}
}

// FUNCTION: draw_wall
// ----------------------------
// Draws the vertical wall slice of the screen column at position x using the specified texture.
//
// LOGIC
// - Iterates from draw->draw_start to draw->draw_end (the visible portion of the wall).
// - Calculates the corresponding vertical texture coordinate (tex_y) for each pixel:
//     - d = scaled distance from the top of the wall line
//     - tex_y = scaled to texture height
// - Fetches the color from the texture using get_texture_color(img, draw->img_x, tex_y).
// - Draws the pixel on the screen with put_pixel.
//
// PARAMETERS
// game : Pointer to the game structure containing the image buffer and screen dimensions.
// draw : Pointer to the draw structure containing wall drawing information.
// x    : Horizontal screen coordinate (column) being drawn.
// img  : Pointer to the texture image to use for the wall.
//
// RETURN VALUE
// No return value. Modifies the image buffer directly by drawing wall pixels.
void	draw_wall(t_game *game, t_draw *draw, int x, t_img *img)
{
	int	y;
	int	tex_y;
	int	color;
	int	d;

	y = draw->draw_start;
	while (y < draw->draw_end)
	{
		d = y * 256 - game->screen_height * 128 + draw->line_height * 128;
		tex_y = ((d * img->height) / draw->line_height) / 256;
		color = get_texture_color(img, draw->img_x, tex_y);
		put_pixel(game->img, x, y, color);
		y++;
	}
}

// FUNCTION: draw_floor
// ----------------------------
// Draws the floor portion of the screen column at position x with a specified color.
//
// LOGIC
// - Iterates from draw->draw_end (the end of the wall) to the bottom of the screen (screen_height).
// - Sets each pixel to the given floor color using put_pixel.
//
// PARAMETERS
// game  : Pointer to the game structure containing the image buffer and screen dimensions.
// draw  : Pointer to the draw structure containing the wall end position.
// x     : Horizontal screen coordinate (column) being drawn.
// color : Color value to fill the floor pixels.
//
// RETURN VALUE
// No return value. Modifies the image buffer directly by drawing floor pixels.
void	draw_floor(t_game *game, t_draw *draw, int x, int color)
{
	int	y;

	y = draw->draw_end;
	while (y < game->screen_height)
	{
		put_pixel(game->img, x, y, color);
		y++;
	}
}
