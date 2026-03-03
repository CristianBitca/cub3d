/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cbitca <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/10 14:33:10 by cbitca            #+#    #+#             */
/*   Updated: 2025/12/10 14:33:11 by cbitca           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PARSING_H
#define PARSING_H

// Include

#include "cub3d.h"

// MACROS: ERROR MESSAGES
// ---------------------------------------------------
// This group of macros defines standardized error messages used throughout Cub3D
// to handle file operations and map parsing issues. They ensure consistent reporting
// when something goes wrong, helping with debugging and user feedback.
//
// - FILE_OPEN  : Displayed when a file cannot be opened.
// - XPM_FILE   : Displayed when a texture file (XPM) fails to load; includes file path and texture name.
// - EXTRA_ELEM : Displayed when an unexpected or unused element is found in the map file.
//
// Usage: Pass these macros to printf or error handling functions when a corresponding
// error occurs.
#define FILE_OPEN	"Failed to open the file.\n"
#define	XPM_FILE	"Failed to open the file %s, to load %s\n"
#define	EXTRA_ELEM	"Unused element %s located in %s\n"

// MACROS: MAP VALIDATION
// ---------------------------------------------------
// This group of macros defines valid characters for maps and player starting positions
// in Cub3D. They are used to verify map files and ensure that only allowed symbols are
// present, preventing invalid maps or unexpected behavior.
//
// - MAP_CHARS   : All valid characters in the map ('0', '1', 'N', 'S', 'E', 'W', space).
// - ENTRY_CHARS : Characters representing valid player starting positions ('N', 'S', 'E', 'W').
//
// Usage: Use these macros during map parsing and validation to check for valid characters
// and to initialize the player at the correct position.
#define MAP_CHARS	"01NSEW "
#define ENTRY_CHARS	"NSEW"

// parse

int		parse(t_game *game, char *path);

// parse_elem

int		check_elem(char	*line);
int		check_rgb(char	*line);
void	parse_rgb(int *p_elem, char **elem);
void	parse_img(t_game *game, t_img **img, char **elem);
void	parse_elem(t_game *game, char *line);

// parse_map

int		check_map(char *line, int check);
void	parse_map(t_game *game, char *line, int fd);
int		check_map_valid(t_game *game, char *content, t_player *player);
void	flood_fill(t_game *game, char **buffer, int y, int x);

#endif
