/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cbitca <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/10 14:32:40 by cbitca            #+#    #+#             */
/*   Updated: 2025/12/10 14:32:41 by cbitca           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef UTILS_H
#define UTILS_H

// Include

#include "cub3d.h"

// Def

#define MAP_FORMAT	".cub"
#define IMG_FORMAT	".xpm"

// Error message

#define ERR			"Error\n"

#define MLX_MLX		"Unable to initialize MLX\n"
#define MLX_WIN		"Unable to initialize MLX window\n"
#define MLX_IMG		"Unable to initialize MLX image\n"

#define ARG_1		"Missing the argument, PATH to the map.\n"
#define ARG_2		"The argumtent is not type .cub.\n"
#define ARG_3		"Moo many arguments.\n"

#define	ASSET_MEM	"Unable to initialize memory for assets data\n"
#define ASSET_MAP	"Unable to allocate memory for map\n"

#define PLAYER_MEM	"Unable to initialize for player data\n"

#define IMG_MEM		"Unable to initialize memory for image data\n"

#define IMG_EXT		"Image %s has from incompatible format(expeced .xpm)\n"
#define RGB			"Element %s has wrong RGB value(%s)\n"
#define MAP_ENTRY	"Too many starting points in the map\n"
#define MAP_CHAR	"Unexpected character in the map\n"

// Functions

// error

int		check_arg(int argc, char **argv);
int		check_assets(t_asset *asset);

// exit

void	error();
int		exit_error(char *err);
void	free_content(char **content);
int	exit_game(t_game *game);
int key_hook(int keycode, t_game *game);

// debug_data

void	data_preview(t_game *game);

#endif