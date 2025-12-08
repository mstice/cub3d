/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   file_checks.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mtice <mtice@student.42belgium.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/05 14:55:26 by mtice             #+#    #+#             */
/*   Updated: 2025/12/08 15:50:24 by mtice            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3D.h"

//-----------------------------------------------------------------------------
//checks whether the name of the map is valid (extension must be .cub)
static int	file_invalid_name(t_data *all, char *file_name)
{
	char	*extension;
	char	*real_file_name;

	if (!file_name || file_name[0] == '\0')
		return (FAILURE);
	extension = ft_strchr(file_name, '.');
	if (extension == NULL || extension != ft_strrchr(file_name, '.'))
		ft_exit(all, ERR_FILE_NAME);
	if (ft_strncmp(extension, ".cub\0", 5))
		ft_exit(all, ERR_FILE_NAME);
	real_file_name = ft_strrchr(file_name, '/');
	if (real_file_name)
	{
		real_file_name++;
		if (ft_strlen(real_file_name) < 5)
			ft_exit(all, ERR_FILE_NAME);
	}
	else if (ft_strlen(file_name) < 5)
		ft_exit(all, ERR_FILE_NAME);
	return (SUCCESS);
}

//-----------------------------------------------------------------------------
//checks if file exists and has correct permissions
int	file_no_exist(t_data *all, char *file_name)
{
	int	fd;

	fd = open(file_name, O_RDONLY);
	if (fd < 0 || fd > 1024)
		ft_exit(all, ERR_FILE_NOEXIST);
	return (fd);
}

//-----------------------------------------------------------------------------
static void	record_col(t_data *all, char *p_line, int fd)
{
	if (ft_strchr(p_line, 'F'))
	{
		if (all->floor)
			close(fd), ft_exit(all, ERR_COL_DUP);
		all->floor = ft_strdup(p_line);
	}
	else if (ft_strchr(p_line, 'C'))
	{
		if (all->ceiling)
			close(fd), ft_exit(all, ERR_COL_DUP);
		all->ceiling = ft_strdup(p_line);
	}
}

//-----------------------------------------------------------------------------
static void	record_text(t_data *all, char *p_line, int fd)
{
	if (ft_strnstr(p_line, "NO", ft_strlen(p_line)))
	{
		if (all->north_text)
			close(fd), ft_exit(all, ERR_TXT_DUP);
		all->north_text = ft_strdup(p_line);
	}
	else if (ft_strnstr(p_line, "EA", ft_strlen(p_line)))
	{
		if (all->east_text)
			close(fd), ft_exit(all, ERR_TXT_DUP);
		all->east_text = ft_strdup(p_line);
	}
	else if (ft_strnstr(p_line, "SO", ft_strlen(p_line)))
	{
		if (all->south_text)
			close(fd), ft_exit(all, ERR_TXT_DUP);
		all->south_text = ft_strdup(p_line);
	}
	else if (ft_strnstr(p_line, "WE", ft_strlen(p_line)))
	{
		if (all->west_text)
			close(fd), ft_exit(all, ERR_TXT_DUP);
		all->west_text = ft_strdup(p_line);
	}
}

static int	file_err_elements(t_data *all, int fd)
{
	if (!all->ceiling) //&& valid_col(all->ceiling))
		close(fd), ft_exit(all, ERR_COL_CL); //TODO: check if its valid colour
	else if (!all->floor) //&& valid_col(all->floor))
		close(fd), ft_exit(all, ERR_COL_FL); //TODO: check if its a valid colour
	else if (!all->north_text || !all->east_text
			|| !all->south_text || !all->west_text) //TODO: check if its a valid path
		close(fd), ft_exit(all, ERR_NO_TXT);
	return (SUCCESS);
}

//-----------------------------------------------------------------------------
static int	record_file_attributes(t_data *all, int fd)
{
	char	*line;
	char	*p_line;

	line = get_next_line(fd);
	if (!line)
		close(fd), ft_exit(all, ERR_FILE_EMPTY);
	while (line != NULL && ++(all->map_start))
	{
		p_line = ft_strtrim(line, "\n");
		if (p_line && *p_line)
		{
			record_col(all, p_line, fd);
			record_text(all, p_line, fd);
		}
		free(line), free(p_line);
		if (all->floor && all->ceiling && all->north_text
			&& all->east_text && all->south_text && all->west_text)
		{
			// printf("floor: %s\n", all->floor);
			// printf("ceiling: %s\n", all->ceiling);
			// printf("north: %s\n", all->north_text);
			// printf("east: %s\n", all->east_text);
			// printf("south: %s\n", all->south_text);
			//printf("west: %s\n", all->west_text);
			break ;
		}
		line = get_next_line(fd);
	}
	return (file_err_elements(all, fd));
}

//-----------------------------------------------------------------------------
// static int	file_err_elements(t_data *all)
// {
// 	if (!all->ceiling) //&& valid_col(all->ceiling))
// 		ft_exit(all, ERR_COL_CL); //TODO: check if its valid colour
// 	else if (!all->floor) //&& valid_col(all->floor))
// 		ft_exit(all, ERR_COL_FL); //TODO: check if its a valid colour
// 	else if (!all->north_text || !all->east_text
// 			|| !all->south_text || !all->west_text) //TODO: check if its a valid path
// 		ft_exit(all, ERR_NO_TXT);
// 	return (SUCCESS);
// }
//-----------------------------------------------------------------------------
//finds height of map for later reference
//checks if map is populated
//p_line -> processed line (after \n char removal)
static int	record_map_attributes(t_data *all, int fd)
{
	char	*line;
	char	*p_line;

	line = get_next_line(fd);
	if (!line)
		close(fd), ft_exit(all, ERR_FILE_EMPTY);
	p_line = ft_strtrim(line, "\n");
	while (!p_line || !(*p_line))
	{
		free(p_line), free(line);
		line = get_next_line(fd);
		p_line = ft_strtrim(line, "\n");
		all->map_start++;
	}
	while (line && p_line && *p_line)
	{
		all->width = get_max(all->width, ft_strlen(p_line));
		free(line), free(p_line);
		all->height++;
		line = get_next_line(fd);
		p_line = ft_strtrim(line, "\n");
	}
	free(line), free(p_line);
	return (SUCCESS);
}

//-----------------------------------------------------------------------------
//parses input and performs the necessary error checking before
//map-specific checks
int	file_checks(t_data *all, char *file_name)
{
	int	fd;

	if (file_invalid_name(all, file_name))
		return (FAILURE);
	fd = file_no_exist(all, file_name);
	if (record_file_attributes(all, fd))
		return (FAILURE);
	// else if (file_err_elements(all))
	// 	return (FAILURE);
	if (record_map_attributes(all, fd))
		return (FAILURE);
	close(fd);
	return (SUCCESS);
}
