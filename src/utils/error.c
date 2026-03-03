/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cbitca <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/10 14:29:29 by cbitca            #+#    #+#             */
/*   Updated: 2025/12/10 14:29:30 by cbitca           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "utils.h"

// FUNCTION: error
// ----------------------------
// Prints a generic error message (ERR) to the console, but only once.
// Uses a static variable to prevent repeated prints.
//
// RETURN VALUE
// None.
void	error(void)
{
	static int	status;

	if (!status)
	{
		printf(ERR);
		status = 1;
	}
}

// FUNCTION: exit_error
// ----------------------------
// Prints a generic error message and an optional specific error string,
// then terminates the program.
//
// PARAMETERS
// err : Optional C string containing additional error info.
//
// RETURN VALUE
// Does not return; exits the program with EXIT_FAILURE.
int	exit_error(char *err)
{
	error();
	if (err)
		printf("%s", err);
	exit(EXIT_FAILURE);
}

// FUNCTION: check_arg
// ----------------------------
// Validates the command-line arguments for the program.
//
// PARAMETERS
// argc : Argument count.
// argv : Argument vector.
//
// RETURN VALUE
// EXIT_SUCCESS if arguments are valid.
// Prints an error message and returns non-zero if invalid.
int	check_arg(int argc, char **argv)
{
	if (argc < 2)
		return (printf(ARG_1));
	if (argc > 2)
		return (printf(ARG_3));
	if (ft_strncmp(&argv[1][ft_strlen(argv[1]) - 4], MAP_FORMAT, 4))
		return (printf(ARG_2));
	return (EXIT_SUCCESS);
}

// FUNCTION: check_parse
// ----------------------------
// Ensures that all required assets (textures) and the map have been loaded
// successfully after parsing. Exits with an error if any are missing.
//
// PARAMETERS
// game   : Pointer to the main game structure.
// assets : Pointer to the assets structure containing texture pointers.
//
// RETURN VALUE
// EXIT_SUCCESS if all assets and map are valid.
// Exits the program with an error if any required resource is missing.
int	check_parse(t_game *game, t_asset *assets)
{
	if (!assets->EA)
		exit_error(ASSET_MISS);
	if (!assets->SO)
		exit_error(ASSET_MISS);
	if (!assets->NO)
		exit_error(ASSET_MISS);
	if (!assets->WE)
		exit_error(ASSET_MISS);
	if (!game->map)
		exit_error(ASSET_MISS);
	return (EXIT_SUCCESS);
}
