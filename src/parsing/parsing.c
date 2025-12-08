/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mtice <mtice@student.42belgium.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/02 13:18:52 by mtice             #+#    #+#             */
/*   Updated: 2025/12/07 16:50:23 by mtice            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3D.h"

int	parsing(t_data *all, char *map_name)
{
	if (file_checks(all, map_name))
		return (FAILURE);
	if (map_checks(all, map_name))
		return (FAILURE);
	else if (map_reformats(all))
		return (FAILURE);
	//else if (position_image(all))
		//return (FAILURE);
	return (SUCCESS);
}
