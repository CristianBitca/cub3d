/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3d.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cbitca <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/08 18:20:29 by cbitca            #+#    #+#             */
/*   Updated: 2025/12/08 18:20:31 by cbitca           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CUB3D_H
#define CUB3D_H

// Include

#include <stdio.h>
#include "libft/include/libft.h"
#include "minilibx-linux/mlx.h"
#include "math.h"

// Struct

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
	D_KEY = 100
}	t_key_code;

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

typedef	struct s_img
{    
	void    *img;
    char    *addr;
    int     bpp;
    int     line_len;
    int     endian;
}	t_img;

typedef struct s_player
{
    double  x;
    double  y;
    double  dir_x;
    double  dir_y;
    double  plane_x;
    double  plane_y;
	int		orientation;
}	t_player;

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
	double perp_wall_dist;
	int side; // 0 = vertical, 1 = horizontal
}	t_ray;

typedef	struct	s_key
{
	int		w;
	int		a;
	int		s;
	int		d;
	int		left;
	int		right;
}	t_key;

typedef struct s_asset
{
	t_img	*NO;
	t_img	*SO;
	t_img	*WE;
	t_img	*EA;
	int		F;
	int		C;
}	t_asset;


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

void	init_game(t_game *game, char *path);

// init_assets

#endif
