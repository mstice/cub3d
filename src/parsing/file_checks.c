/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   file_checks.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mtice <mtice@student.42belgium.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/05 14:55:26 by mtice             #+#    #+#             */
/*   Updated: 2025/12/11 13:25:43 by mtice            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3D.h"

//-----------------------------------------------------------------------------
//checks if file exists and has correct permissions
//opens file to read_only and returns fd
int	file_no_exist(char *file_name)
{
	int	fd;

	fd = open(file_name, O_RDONLY);
	if (fd < 0 || fd > 1024)
		return (-1);
	return (fd);
}

//-----------------------------------------------------------------------------
//checks file elements (textures and colours) for errors
static void	file_err_elements(t_data *all, int fd)
{
	invalid_col(all, fd);
	invalid_txt(all, all->north, fd);
	invalid_txt(all, all->east, fd);
	invalid_txt(all, all->south, fd);
	invalid_txt(all, all->west, fd);
	if (!ft_strcmp(all->north, all->east) || !ft_strcmp(all->north, all->south)
		|| !ft_strcmp(all->north, all->west)
		|| !ft_strcmp(all->east, all->south)
		|| !ft_strcmp(all->east, all->west)
		|| !ft_strcmp(all->south, all->west))
		ft_exit(all, ERR_TXT_DUP, fd);
}

//-----------------------------------------------------------------------------
//check if we have found the first line of the map
static char	*check_line(t_data *all, char *line, int fd)
{
	int		i;
	char	*map_start;

	i = 0;
	while (ft_isspace(line[i]))
		i++;
	if (ft_isdigit(line[i]) && --all->map_start)
	{
		map_start = ft_strdup(&line[i]);
		free(line);
		return (map_start);
	}
	else if (line[i])
	{
		free(line);
		file_err_elements(all, fd);
		ft_exit(all, ERR_MAP_LAST, fd);
	}
	return (NULL);
}

//-----------------------------------------------------------------------------
//records colour, and texture paths, and when the map starts
static char	*record_file_attributes(t_data *all, int fd)
{
	char	*line;
	char	*map_start;

	line = get_next_line(fd);
	if (!line)
		ft_exit(all, ERR_FILE_EMPTY, fd);
	while (line != NULL && ++all->map_start)
	{
		line = ft_strtrim(line, "\n");
		if ((line && *line)
			&& (!record_col(all, line, fd) && !record_txt(all, line, fd)))
		{
			map_start = check_line(all, line, fd);
			if (map_start)
				return (map_start);
		}
		free(line);
		line = get_next_line(fd);
	}
	return (NULL);
}

//-----------------------------------------------------------------------------
//performs the necessary error checking on the file and its contents before
//map-specific checks
int	file_checks(t_data *all, char *file_name)
{
	int		fd;
	char	*map_start;

	fd = file_no_exist(file_name);
	if (fd == -1)
		ft_exit(all, ERR_FILE_NOEXIST, 0);
	map_start = record_file_attributes(all, fd);
	if (!map_start)
		ft_exit(all, ERR_MAP_LAST, 0);
	record_map_attributes(all, fd, map_start);
	file_err_elements(all, fd);
	close(fd);
	return (SUCCESS);
}
