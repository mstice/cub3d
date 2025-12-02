/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mtice <mtice@student.42belgium.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/02 13:18:52 by mtice             #+#    #+#             */
/*   Updated: 2025/12/02 13:50:44 by mtice            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3D.h"

int	parsing(t_data *all, char *map_name)
{
	if (map_checks(all, map_name))
		return (FAILURE);
	// else if (map_chars(all))
	// 	return (FAILURE);
	// else if (map_3d_map(all))
	// 	return (FAILURE);
	// else if (map_2d_map(all))
	// 	return (FAILURE);
	return (SUCCESS);
}
