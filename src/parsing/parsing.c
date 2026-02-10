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

//-----------------------------------------------------------------------------
//req_extension: required extension (E.g. .cub for file and .xpm for texture)
int	file_invalid_name(char *file_name, char *req_extension)
{
	char	*extension;
	char	*real_file_name;

	if (!file_name || file_name[0] == '\0')
		return (FAILURE);
	extension = ft_strchr(file_name, '.');
	if (extension == NULL || extension != ft_strrchr(file_name, '.')
		|| !req_extension)
		return (FAILURE);
	if (ft_strncmp(extension, req_extension, ft_strlen(req_extension)))
		return (FAILURE);
	real_file_name = ft_strrchr(file_name, '/');
	if (real_file_name)
	{
		real_file_name++;
		if (ft_strlen(real_file_name) <= ft_strlen(req_extension))
			return (FAILURE);
	}
	else if (ft_strlen(file_name) <= ft_strlen(req_extension))
		return (FAILURE);
	return (SUCCESS);
}

//-----------------------------------------------------------------------------
//calls different parsing functions
int	parsing(t_data *all, char *map_name)
{
	if (file_invalid_name(map_name, ".cub"))
		ft_exit(all, ERR_FILE_NAME, 0);
	if (file_checks(all, map_name))
		return (FAILURE);
	if (map_checks(all, map_name))
		return (FAILURE);
	return (SUCCESS);
}
