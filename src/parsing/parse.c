/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cbitca <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/10 17:40:02 by cbitca            #+#    #+#             */
/*   Updated: 2025/12/10 17:40:03 by cbitca           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"
#include "parsing.h"
#include "utils.h"

// FUNCTION: parse
// ----------------------------
// Reads a Cub3D configuration file, parses textures, colors, and the map,
// and validates the parsed data. Calls the appropriate parse functions based
// on whether a line is an element, a map line, or empty.
//
// PARAMETERS
// game : Pointer to the game structure where parsed data will be stored.
// path : Path to the .cub configuration file.
//
// RETURN VALUE
// Returns EXIT_SUCCESS (0) if parsing succeeds, EXIT_FAILURE (1) on failure.
// Exits the program immediately if the file cannot be opened or if critical
// parsing errors occur.
int	parse(t_game *game, char *path)
{
	int		fd;
	char	*line;

	fd = open(path, O_RDONLY);
	if (fd <= 0)
		exit_error(FILE_OPEN);
	line = ft_get_next_line(fd);
	while (line)
	{
		if (!ft_strncmp(line, "\n", 2))
			free(line);
		else if (!check_elem(line))
			parse_elem(game, line);
		else if (!check_map(line, 0))
			parse_map(game, line, fd);
		else if (line)
			return (exit_error(ERR));
		line = ft_get_next_line(fd);
	}
	(free(line), close(fd));
	if (check_parse(game, game->asset))
		return (EXIT_FAILURE);
	return (EXIT_SUCCESS);
}
