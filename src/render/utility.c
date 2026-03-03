/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utility.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cbitca <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/12 21:36:11 by cbitca            #+#    #+#             */
/*   Updated: 2026/02/12 21:36:12 by cbitca           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"
#include "render.h"
#include "parsing.h"
#include <sys/wait.h>

// FUNCTION: draw_line
// ----------------------------
// Draws a line between two points on an image using Bresenham's algorithm.
// Recursively steps through the line, plotting each pixel with the specified color.
//
// PARAMETERS
// img  : Pointer to the image structure where the line will be drawn.
// line : Pointer to the line structure containing start/end coordinates, step increments, and color.
//
// RETURN VALUE
// None. Modifies the image by setting the pixels along the line.
void	draw_line(t_img *img, t_line *line)
{
	put_pixel(img, line->x0, line->y0, line->color);
	if (line->x0 == line->x1 && line->y0 == line->y1)
		return ;
	line->err2 = line->err * 2;
	if (line->err2 > -line->dy)
	{
		line->err -= line->dy;
		line->x0 += line->sx;
	}
	if (line->err2 < line->dx)
	{
		line->err += line->dx;
		line->y0 += line->sy;
	}
	draw_line(img, line);
}


// FUNCTION: draw_player
// ----------------------------
// Draws the player as a small circle on the minimap for debugging purposes.
//
// PARAMETERS
// img    : Pointer to the image structure where the player will be drawn.
// player : Pointer to the player structure containing the player's position.
//
// RETURN VALUE
// None. Modifies the image by drawing the player.
void	draw_player(t_img *img, t_player *player)
{
	int	x;
	int	y;
	int	cx;
	int	cy;

	cx = player->x * TILE;
	cy = player->y * TILE;
	y = -5;
	while (y <= 5)
	{
		x = -5;
		while (x <= 5)
		{
			if (x * x + y * y <= 25)
				put_pixel(img, cx + x, cy + y, RED);
			x++;
		}
		y++;
	}
}

// FUNCTION: put_pixel
// ----------------------------
// Sets the color of a single pixel in the image buffer at (x, y).
//
// PARAMETERS
// img   : Pointer to the image structure containing the pixel buffer.
// x     : X-coordinate of the pixel.
// y     : Y-coordinate of the pixel.
// color : The color value to set (usually in 0xRRGGBB format).
//
// RETURN VALUE
// None. Modifies the image buffer by setting the pixel color.
void	put_pixel(t_img *img, int x, int y, int color)
{
	char	*dst;

	dst = img->addr + (y * img->line_len + x * (img->bpp / 8));
	*(unsigned int *)dst = color;
}

// FUNCTION: get_texture_color
// ----------------------------
// Retrieves the color of a pixel from a texture image at (x, y).
//
// PARAMETERS
// tex : Pointer to the texture image structure.
// x   : X-coordinate of the pixel in the texture.
// y   : Y-coordinate of the pixel in the texture.
//
// RETURN VALUE
// Returns the color of the pixel as an integer (0 if coordinates are out of bounds).
int	get_texture_color(t_img *tex, int x, int y)
{
	char	*pixel;

	if (x < 0 || x >= tex->width || y < 0 || y >= tex->height)
		return (0);
	pixel = tex->addr + (y * tex->line_len + x * (tex->bpp / 8));
	return (*(int *)pixel);
}
