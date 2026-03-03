/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_map.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cbitca <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/04 15:59:34 by cbitca            #+#    #+#             */
/*   Updated: 2026/02/04 15:59:35 by cbitca           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"
#include "parsing.h"
#include "utils.h"


// FUNCTION: flood_fill
// ----------------------------
// Performs a flood-fill algorithm on the map to validate it is properly closed.
// Marks visited cells with 'V'. If an invalid location or edge is reached, exits.
//
// PARAMETERS
// game   : Pointer to the game structure (used for error handling).
// buffer : 2D character array representing the map.
// y      : Current Y coordinate to check.
// x      : Current X coordinate to check.
//
// RETURN VALUE
// None. Exits the program if the map is invalid.
void	flood_fill(t_game *game, char **buffer, int y, int x)
{
	if (x < 0 || y < 0 || !buffer[y] || !buffer[y][x])
		(exit_error(MAP_INVALID));
	if (buffer[y][x] == ' ' || buffer[y][x] == '\0')
		(exit_error(MAP_INVALID));
	if (buffer[y][x] == '1' || buffer[y][x] == 'V')
		return ;
	buffer[y][x] = 'V';
	flood_fill(game, buffer, y + 1, x);
	flood_fill(game, buffer, y - 1, x);
	flood_fill(game, buffer, y, x + 1);
	flood_fill(game, buffer, y, x - 1);
	flood_fill(game, buffer, y + 1, x + 1);
	flood_fill(game, buffer, y - 1, x + 1);
	flood_fill(game, buffer, y - 1, x - 1);
	flood_fill(game, buffer, y + 1, x - 1);
}

// FUNCTION: check_map_valid
// ----------------------------
// Checks the map for a valid player entry and ensures it is closed by walls.
// Uses flood_fill to validate the map from the player's start position.
//
// PARAMETERS
// game    : Pointer to the game structure (used for player info and errors).
// content : String representing the full map contents.
// player  : Pointer to the player structure to set starting position.
//
// RETURN VALUE
// Returns EXIT_SUCCESS (0) if map is valid. Exits program if invalid.
int	check_map_valid(t_game *game, char *content, t_player *player)
{
	char	**buffer;
	int		y;
	int		x;

	buffer = ft_split(content, '\n');
	y = 0;
	while (buffer[y])
	{
		x = 0;
		while (buffer[y][x])
		{
			if (ft_strchr(ENTRY_CHARS, buffer[y][x])
			&& buffer[y][x] != '\n')
			{
				player->y = (double)y;
				player->x = (double)x;
				flood_fill(game, buffer, y, x);
				return (free_content(buffer), EXIT_SUCCESS);
			}
			x++;
		}
		y++;
	}
	return (EXIT_SUCCESS);
}

// FUNCTION: check_map
// ----------------------------
// Validates a single map line for allowed characters and proper player entry count.
//
// PARAMETERS
// line  : Line of map to check.
// check : If non-zero, enforce exactly one player entry in the line.
//
// RETURN VALUE
// Returns EXIT_SUCCESS (0) if line is valid. Exits program if invalid.
int	check_map(char *line, int check)
{
	int		i;
	int		c;

	i = 0;
	c = 0;
	while (line[i])
	{
		if (!ft_strchr(MAP_CHARS, line[i]) && line[i] != '\n')
			exit_error(MAP_CHAR);
		if (ft_strchr(ENTRY_CHARS, line[i]) && line[i] != '\n')
			c++;
		i++;
	}
	if (c > 1 && check)
		exit_error(MAP_ENTRY);
	else if (c < 1 && check)
		exit_error(MAP_NOENTRY);
	return (EXIT_SUCCESS);
}

// FUNCTION: parse_map
// ----------------------------
// Reads the map from file, builds the full map string, validates it, and stores
// it in the game structure as a 2D array. Sets map width, height, and player start.
//
// PARAMETERS
// game : Pointer to the game structure to store map and player info.
// line : First line of the map already read from the file.
// fd   : File descriptor for reading the rest of the map.
//
// RETURN VALUE
// None. Exits the program if the map is invalid.
void	parse_map(t_game *game, char *line, int fd)
{
	char	*buffer;
	char	*tmp;

	buffer = ft_strdup("");
	while (line)
	{
		tmp = buffer;
		buffer = ft_strjoin(buffer, line);
		if ((int)ft_strlen(line) - 1 > game->map_width)
			game->map_width = ft_strlen(line) - 1;
		(free(tmp), free(line));
		line = ft_get_next_line(fd);
	}
	if (check_map(buffer, 1))
		exit_error(MAP_INVALID);
	if (check_map_valid(game, buffer, game->player))
		exit_error(MAP_INVALID);
	game->map = ft_split(buffer, '\n');
	game->map_height = count_words(buffer, '\n');
	free(buffer);
}
