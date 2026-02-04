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

#define WIDTH	1920
#define HEIGHT	1080	

// Struct

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


typedef struct s_asset
{
	void	*NO;
	void	*SO;
	void	*WE;
	void	*EA;
	int		F;
	int		C;
}	t_asset;


typedef struct s_game
{
	void		*mlx;
	void		*win;
	char		**map;
	t_asset		*asset;
	t_player	*player;
	t_img		*img;
}	t_game;

// Function

// init

void	init_game(t_game *game, char *path);

#endif
