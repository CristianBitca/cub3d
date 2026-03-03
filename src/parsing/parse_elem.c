/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_elem.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cbitca <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/18 16:06:20 by cbitca            #+#    #+#             */
/*   Updated: 2026/01/18 16:06:21 by cbitca           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"
#include "parsing.h"
#include "utils.h"

// FUNCTION: check_rgb
// ----------------------------
// Validates that a string represents a properly formatted RGB color.
// The string should contain only digits and commas, with exactly three components.
//
// PARAMETERS
// line : The RGB string to validate (e.g., "255,128,0").
//
// RETURN VALUE
// Returns EXIT_SUCCESS (0) if the string is valid, EXIT_FAILURE (1) otherwise.
int	check_rgb(char	*line)
{
	int	i;
	int	c;

	i = 0;
	c = 0;
	while (line[i])
	{
		if (!ft_isdigit(line[i]) && line[i] != ',')
			return (EXIT_FAILURE);
		i++;
	}
	if (count_words(line, ',') != 3)
		return (EXIT_FAILURE);
	return (EXIT_SUCCESS);
}

// FUNCTION: parse_rgb
// ----------------------------
// Parses an RGB string and stores the combined color value in the provided integer.
//
// PARAMETERS
// p_elem : Pointer to an integer to store the combined RGB color (0xRRGGBB).
// elem   : Array of strings where elem[0] is the element name and elem[1] is the RGB string.
//
// RETURN VALUE
// None. On failure, prints an error and exits the program.
void	parse_rgb(int *p_elem, char **elem)
{
	char	**tmp;
	int		r;
	int		g;
	int		b;

	if (check_rgb(elem[1]))
	{
		(error(), printf(RGB, elem[0], elem[1]));
		return ((void)(exit_error(0)));
	}
	tmp = ft_split(elem[1], ',');
	r = ft_atoi(tmp[0]);
	g = ft_atoi(tmp[1]);
	b = ft_atoi(tmp[2]);
	if (!(0 <= r && 255 >= r)
		|| !(0 <= g && 255 >= g)
		|| !(0 <= b && 255 >= b))
	{
		(error(), printf(RGB, elem[0], elem[1]));
		(free(tmp[0]), free(tmp[1]), free(tmp[2]), free(tmp));
		return ((void)(exit_error(0)));
	}
	*p_elem = (r << 16) | (g << 8) | b;
	(free(tmp[0]), free(tmp[1]), free(tmp[2]), free(tmp));
}

// FUNCTION: parse_img
// ----------------------------
// Loads a texture image from a file and stores its data in the provided t_img structure.
//
// PARAMETERS
// game : Pointer to the game structure (contains mlx pointer for loading images).
// img  : Pointer to the t_img pointer to initialize and store image data.
// elem : Array of strings where elem[0] is the element name and elem[1] is the image file path.
//
// RETURN VALUE
// None. On failure, prints an error and exits the program.
void	parse_img(t_game *game, t_img **img, char **elem)
{
	int		width;
	int		height;
	char	*tmp;

	width = 0;
	height = 0;
	*img = ft_calloc(sizeof(t_img), 1);
	if (!*img)
		(exit_error(IMG_MEM));
	tmp = ft_strtrim(elem[1], "\n\t");
	if (ft_strncmp(&tmp[ft_strlen(tmp) - 4], IMG_FORMAT, 4))
		return ((void)(error(), printf(IMG_EXT, elem[0]),
			free(tmp), exit_error(0)));
	(*img)->img = mlx_xpm_file_to_image(game->mlx, tmp, &width, &height);
	if (!(*img)->img)
		return ((void)(error(), printf(XPM_FILE, tmp, elem[0]),
			exit_error(0)));
	(*img)->addr = mlx_get_data_addr((*img)->img,
			&(*img)->bpp, &(*img)->line_len, &(*img)->endian);
	if (!(*img)->addr)
		return ((void)(error(), printf(XPM_FILE, tmp, elem[0]),
			exit_error(0)));
	(*img)->width = width;
	(*img)->height = height;
	free(tmp);
}

// FUNCTION: parse_elem
// ----------------------------
// Parses a single line of element definition from the map file. Determines whether
// it is a texture or a color and calls the appropriate parsing function.
//
// PARAMETERS
// game : Pointer to the game structure (stores textures and colors).
// line : Line of the map file containing an element definition.
//
// RETURN VALUE
// None. On failure, prints an error and exits the program.
void	parse_elem(t_game *game, char *line)
{
	char	**element;
	char	*tmp;

	tmp = line;
	line = ft_strtrim(line, "\n\t ");
	free(tmp);
	element = ft_split(line, ' ');
	if (!element[1])
		(error(), printf(IMG_PATH, element[0]), exit_error(0));
	if (!ft_strncmp("NO", element[0], 3))
		parse_img(game, &game->asset->NO, element);
	else if (!ft_strncmp("SO", element[0], 3))
		parse_img(game, &game->asset->SO, element);
	else if (!ft_strncmp("WE", element[0], 3))
		parse_img(game, &game->asset->WE, element);
	else if (!ft_strncmp("EA", element[0], 3))
		parse_img(game, &game->asset->EA, element);
	else if (!ft_strncmp("F", element[0], 2))
		parse_rgb(&game->asset->F, element);
	else if (!ft_strncmp("C", element[0], 2))
		parse_rgb(&game->asset->C, element);
	(free_content(element), free(line));
	(void)game;
}

// FUNCTION: check_elem
// ----------------------------
// Validates the format of a single element line. Ensures it contains exactly
// one space separating two strings and that the element identifier is not too long.
//
// PARAMETERS
// line : Line of the map file containing an element definition.
//
// RETURN VALUE
// Returns EXIT_SUCCESS (0) if the element line is valid, EXIT_FAILURE (1) otherwise.
int	check_elem(char	*line)
{
	char	**element;

	if (!ft_strchr(line, ' '))
		return (EXIT_FAILURE);
	if (count_words(line, ' ') != 2)
		return (EXIT_FAILURE);
	element = ft_split(line, ' ');
	if (ft_strlen(element[0]) > 2)
	{
		(free(element[0]), free(element[1]), free(element));
		return (EXIT_FAILURE);
	}
	(free(element[0]), free(element[1]), free(element));
	return (EXIT_SUCCESS);
}
