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

// Struct

typedef enum e_type
{
	XPM,
	RGB,
}	t_type;

typedef struct s_element
{
	int	id;
	char	data;
	t_type	type;
	struct s_element	*next;
}	t_element;

typedef struct s_map
{
	t_element	*first;
	char	**content;
}	t_map;


typedef struct s_game
{
	t_map	*map;
}	t_game;

// Function

// init

int	init_game(t_game *game, char *path);

#endif
