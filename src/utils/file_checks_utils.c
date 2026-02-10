/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   file_checks_utils.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mtice <mtice@student.42belgium.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/11 12:29:45 by mtice             #+#    #+#             */
/*   Updated: 2025/12/12 16:39:59 by mtice            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3D.h"

//-----------------------------------------------------------------------------
//records the colours and stores them in the t_data struct
//RETURN_VALUE: returns TRUE if a colour has been found, FALSE if not
bool	record_col(t_data *all, char *line, int fd)
{
	bool	recorded;

	recorded = true;
	if (ft_strchr(line, 'F') && all->floor == -1)
		all->floor = get_colour_values(line);
	else if (ft_strchr(line, 'C') && all->ceiling == -1)
		all->ceiling = get_colour_values(line);
	else if ((ft_strchr (line, 'F') && all->floor != -1)
		|| (ft_strchr(line, 'C') && all->ceiling != -1))
	{
		if (line)
			free(line);
		ft_exit(all, ERR_COL_MANY, fd);
	}
	else
		recorded = false;
	return (recorded);
}

//-----------------------------------------------------------------------------
int	invalid_col(t_data *all, int fd)
{
	if (all->floor == -1)
		ft_exit(all, ERR_COL_FL, fd);
	else if (all->ceiling == -1)
		ft_exit(all, ERR_COL_CL, fd);
	else if (all->floor == -2 || all->ceiling == -2)
		ft_exit(all, ERR_COL_INV, fd);
	else if (all->floor == WHITE || all->ceiling == WHITE
		|| all->floor == BLACK || all->ceiling == BLACK)
		ft_exit(all, ERR_COL_BAD, fd);
	else if (all->floor == all->ceiling)
		ft_exit(all, ERR_COL_DUP, fd);
	return (SUCCESS);
}

//----------------------------------------------------------------------------
static char	*find_text(char *line)
{
	char	**path;
	char	*texture;

	path = ft_split(line, ' ');
	texture = ft_strdup(path[1]);
	free_double_char(path);
	return (texture);
}

//-----------------------------------------------------------------------------
//records the textures and stores them in the t_data struct
//RETURN_VALUE: returns TRUE if a texture has been found, FALSE if not
bool	record_txt(t_data *all, char *line, int fd)
{
	bool	recorded;

	recorded = true;
	if (!all->north && ft_strnstr(line, "NO", ft_strlen(line)))
		all->north = find_text(line);
	else if (!all->east && ft_strnstr(line, "EA", ft_strlen(line)))
		all->east = find_text(line);
	else if (!all->south && ft_strnstr(line, "SO", ft_strlen(line)))
		all->south = find_text(line);
	else if (!all->west && ft_strnstr(line, "WE", ft_strlen(line)))
		all->west = find_text(line);
	else if ((all->north && ft_strnstr(line, "NO", ft_strlen(line)))
		|| (all->east && ft_strnstr(line, "EA", ft_strlen(line)))
		|| (all->south && ft_strnstr(line, "SO", ft_strlen(line)))
		|| (all->west && ft_strnstr(line, "WE", ft_strlen(line))))
	{
		free(line);
		ft_exit(all, ERR_TXT_DUP, fd);
	}
	else
		recorded = false;
	return (recorded);
}

//-----------------------------------------------------------------------------
//checks whether a texture is valid
int	invalid_txt(t_data *all, char *file_name, int fd)
{
	int		fd2;

	if (!file_name)
		ft_exit(all, ERR_TXT_UND, fd);
	else if (file_invalid_name(file_name, ".xpm"))
		ft_exit(all, ERR_TXT_NAME, fd);
	fd2 = file_no_exist(file_name);
	if (fd2 == -1)
		ft_exit(all, ERR_TXT_NOEXIST, fd);
	close(fd2);
	return (SUCCESS);
}
