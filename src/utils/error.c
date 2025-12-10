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

int	check_arg(int argc, char **argv)
{
	if (argc < 2)
		return (print_error(ARG_1));
	if (argc > 2)
		return (print_error(ARG_3));
	if (ft_strncmp(&argv[1][ft_strlen(argv[1]) - 4], FORMAT, 4))
		return (print_error(ARG_2));
	return (0);
}