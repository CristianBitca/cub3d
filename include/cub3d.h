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

// Struct

typedef struct s_map
{
	void	*NO;
	void	*SO;
	void	*WE;
	void	*EA;
	int		F;
	int		C;
	char	**content;
	int		x;
	int		y;
	int		width;
	int		height;
}	t_map;


typedef struct s_game
{
	void		*mlx;
	void		*win;
	t_map	*map;
}	t_game;

// Function

// init

void	init_game(t_game *game, char *path);

#endif
