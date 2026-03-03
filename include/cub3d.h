/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3d.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tyamano <tyamano@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/08 18:20:29 by cbitca            #+#    #+#             */
/*   Updated: 2026/02/19 20:42:58 by tyamano          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CUB3D_H
#define CUB3D_H

// Include

#include <stdio.h>
#include "libft/include/libft.h"
#include "minilibx-linux/mlx.h"
#include "math.h"
#include <sys/time.h>

// Struct

// ENUM: t_colors
// --------------
// Defines common colors used in the game for rendering purposes. Each color
// is represented as a hexadecimal RGB value.
//
// USAGE
// Can be used to set pixel colors in images or for drawing lines and shapes.
typedef enum e_colors
{
	RED = 0xFF0000,
	GREEN = 0x00FF00,
	WHITE = 0xFFFFFF,
	BLACK = 0x000000
}	t_colors;

// ENUM: t_key_code
// ----------------
// Enumerates key codes and event types from the X11 / MinilibX environment.
//
// USAGE
// Used to detect specific key presses or window events such as ESC, arrows,
// WASD movement keys, or closing the window.
typedef enum e_key_code
{
	CLOSE_ICON = 17,
	ESC_KEY = 65307,
	KEY_PRESS = 2,
	KEY_RELEASE = 3,
	UP_ARROW_KEY = 65362,
	DOWN_ARROW_KEY = 65364,
	LEFT_ARROW_KEY = 65361,
	RIGHT_ARROW_KEY = 65363,
	W_KEY = 119,
	A_KEY = 97,
	S_KEY = 115,
	D_KEY = 100,
	M_KEY = 109
}	t_key_code;

// ENUM: t_data_type
// -----------------
// Lists all possible types of data structures used in the game logic.
//
// USAGE
// Useful for generic functions or type checking when handling different data
// types like INT, CHAR, IMG, PLAYER, RAY, etc.
typedef	enum e_data_type
{
	INT,
	CHAR,
	DOUBLE,
	IMG,
	PLAYER,
	RAY,
	KEY,
	ASSET,
	VOID
}	t_data_type;

// STRUCT: t_img
// --------------
// Stores information about an image used in rendering.
//
// MEMBERS
// img       : Pointer to the image object from MinilibX.
// addr      : Memory address of the image data.
// bpp       : Bits per pixel.
// line_len  : Number of bytes per row of the image.
// endian    : Endianness of the image.
// width     : Width of the image in pixels.
// height    : Height of the image in pixels.
//
// USAGE
// Holds textures or framebuffers that are drawn to the window.
typedef	struct s_img
{    
	void    *img;
    char    *addr;
    int     bpp;
    int     line_len;
    int     endian;
	int		width;
	int		height;
}	t_img;

// STRUCT: t_player
// -----------------
// Represents the player state in the game.
//
// MEMBERS
// x, y          : Position coordinates of the player.
// dir_x, dir_y  : Direction vector of the player.
// plane_x, plane_y : Camera plane for raycasting calculations.
//
// USAGE
// Used for movement, rotation, and raycasting for rendering 3D perspective.
typedef struct s_player
{
    double  x;
    double  y;
    double  dir_x;
    double  dir_y;
    double  plane_x;
    double  plane_y;
}	t_player;

// STRUCT: t_ray
// --------------
// Stores information about a single ray used in the raycasting algorithm.
//
// MEMBERS
// dir_x, dir_y        : Ray direction vector.
// delta_dist_x/y      : Distance the ray must travel to cross a grid cell in x/y.
// side_dist_x/y       : Distance from current position to next x/y side.
// step_x, step_y      : Step direction for x and y axes (+1 or -1).
// map_x, map_y        : Current grid cell coordinates.
// perp_wall_dist      : Perpendicular distance from player to wall hit.
// side                : Which side of the wall was hit (0=x, 1=y).
//
// USAGE
// Essential for determining wall intersections and rendering 3D scene slices.
typedef struct	s_ray
{
	double	dir_x;
	double	dir_y;
	double	delta_dist_x;
	double	delta_dist_y;
	double	side_dist_x;
	double	side_dist_y;
	int		step_x;
	int		step_y;
	int 	map_x;
	int		map_y;
	double 	perp_wall_dist;
	int 	side;
}	t_ray;

// STRUCT: t_draw
// -----------------
// Stores parameters for drawing vertical slices of walls on the screen.
//
// MEMBERS
// line_height : Height of the vertical line to draw.
// draw_start  : Starting pixel of the line on the screen.
// draw_end    : Ending pixel of the line on the screen.
// img_x       : Texture X coordinate.
// img         : Pointer to the texture image.
//
// USAGE
// Used in raycasting to calculate which part of a texture to draw on the screen.
typedef struct s_draw
{
    int 	line_height;
    int 	draw_start;
    int 	draw_end;
    int 	img_x;
	t_img	*img;
}   t_draw;

// STRUCT: t_line
// -----------------
// Represents a line to be drawn on the screen (e.g., for debugging or rays).
//
// MEMBERS
// x0, y0, x1, y1 : Start and end points of the line.
// dx, dy         : Differences in x and y (for Bresenham’s algorithm).
// sx, sy         : Step directions.
// err, err2      : Error variables for Bresenham’s algorithm.
// color          : Line color.
//
// USAGE
// Helps in rendering lines for walls, rays, or debugging visuals.
typedef	struct	s_line
{
	int		x0;
	int		y0;
	int		x1;
	int		y1;
	int		dx;
	int		dy;
	int		sx;
	int		sy;
	int		err;
	int		err2;
	int		color;
}	t_line;


// STRUCT: t_key
// -----------------
// Stores the state of movement keys for the player.
//
// MEMBERS
// w, a, s, d   : WASD key states (pressed or not).
// left, right  : Arrow key states for rotation.
//
// USAGE
// Used to update the player position and rotation during the game loop.
typedef	struct	s_key
{
	int		w;
	int		a;
	int		s;
	int		d;
	int		left;
	int		right;
}	t_key;

// STRUCT: t_asset
// -----------------
// Holds the textures and color values for the game’s map assets.
//
// MEMBERS
// NO, SO, WE, EA : Texture images for the four directions.
// F, C           : Floor and ceiling colors.
//
// USAGE
// Provides all necessary assets for rendering walls, floors, and ceilings.
typedef struct s_asset
{
	t_img	*NO;
	t_img	*SO;
	t_img	*WE;
	t_img	*EA;
	int		F;
	int		C;
}	t_asset;

// STRUCT: t_game
// -----------------
// Central structure representing the game state.
//
// MEMBERS
// mlx, win      : Pointers to MinilibX instance and window.
// img           : Pointer to current screen image.
// map           : 2D array representing the game map.
// map_width/height : Dimensions of the map.
// screen_width/height : Dimensions of the window.
// asset         : Pointer to loaded textures and colors.
// player        : Pointer to the player structure.
// key           : Pointer to key state structure.
// move_speed, rot_speed : Movement and rotation speed.
// time, old_time : Timing for movement and rendering calculations.
// debug_mode    : Enables or disables debug rendering.
//
// USAGE
// Maintains all information required for game initialization, updating,
// and rendering within the game loop.
typedef struct s_game
{
	void		*mlx;
	void		*win;
	t_img		*img;
	char		**map;
	int			map_width;
	int			map_height;
	int			screen_width;
	int			screen_height;
	t_asset		*asset;
	t_player	*player;
	t_key		*key;
	double		move_speed;
	double		rot_speed;
	double		time;
	double		old_time;
	int			debug_mode;
}	t_game;

// Function

// init

void	init_img(t_game *game, t_img *img);
void	init_player(t_game *game, t_player *player);
void	init_data(t_game *game);
void	init_game(t_game *game, char *path);

// init_render

void	init_line(t_line *line, int color);
void	init_ray(t_ray *ray, t_game *game, t_player *player, int X);
void	init_ray_line(t_line *line, t_ray *ray, t_player *player);
void	init_draw(t_draw *draw, t_ray *ray, t_game *game);

#endif
