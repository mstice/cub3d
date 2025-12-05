/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   file_checks.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mtice <mtice@student.42belgium.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/05 14:55:26 by mtice             #+#    #+#             */
/*   Updated: 2025/12/05 15:50:22 by mtice            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3D.h"

//-----------------------------------------------------------------------------
//checks whether the name of the map is valid (extension must be .cub)
static int	file_invalid_name(char *file_name)
{
	char	*extension;
	char	*real_file_name;

	if (!file_name || file_name[0] == '\0')
		return (FAILURE);
	extension = ft_strchr(file_name, '.');
	if (extension == NULL || extension != ft_strrchr(file_name, '.'))
		ft_exit(ERR_FILE_NAME, EXIT_FAILURE);
	if (ft_strncmp(extension, ".cub\0", 5))
		ft_exit(ERR_FILE_NAME, EXIT_FAILURE);
	real_file_name = ft_strrchr(file_name, '/');
	if (real_file_name)
	{
		real_file_name++;
		if (ft_strlen(real_file_name) < 5)
			ft_exit(ERR_FILE_NAME, EXIT_FAILURE);
	}
	else if (ft_strlen(file_name) < 5)
		ft_exit(ERR_FILE_NAME, EXIT_FAILURE);
	return (SUCCESS);
}

//-----------------------------------------------------------------------------
//checks if map exists and has correct permissions
int	file_no_exist(char *file_name)
{
	int	fd;

	fd = open(file_name, O_RDONLY);
	if (fd < 0 || fd > 1024)
		ft_exit(ERR_FILE_NOEXIST, EXIT_FAILURE);
	return (fd);
}

//-----------------------------------------------------------------------------
static int	record_file_attributes(t_data *all, int fd)
{
	char	*line;
	char	*p_line;

	line = get_next_line(fd);
	if (!line)
		close(fd), ft_exit(ERR_FILE_EMPTY, EXIT_FAILURE);
	while (line != NULL)
	{
		p_line = ft_strtrim(line, "\n");
		if (!p_line || !(*p_line))
		{
			free(p_line), free(line);
			line = get_next_line(fd);
			continue ;
		}
		if (ft_strchr(line, 'F'))
			all->floor_col = check_colour();
		else if (ft_strchr(line, 'C'))
			all->ceiling_col = check_colour();
		else if (ft_strstr(line, "NO") && !all->north_text)
			all->north_text = find_text();
		else if (ft_strstr(line, "EA") && !all->east_text)
			all->east_text = find_text();
		else if (ft_strstr(line, "SO") && !all->south_text)
			all->south_text = find_text();
		else if (ft_strstr(line, "WE") && !all->west_text)
			all->west_text = find_text();
		
	}
}

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
		close(fd), ft_exit(ERR_FILE_EMPTY, EXIT_FAILURE);
	while (line != NULL)
	{
		p_line = ft_strtrim(line, "\n");
		if (!p_line || !(*p_line))
		{
			free(p_line);
			free(line);
			line = get_next_line(fd);
			continue ;
		}
		if (all->width < ft_strlen(p_line))
			all->width = ft_strlen(p_line);
		free(line);
		free(p_line);
		all->height++;
		line = get_next_line(fd);
	}
	return (SUCCESS);
}

//-----------------------------------------------------------------------------
//parses input and performs the necessary error checking before
//map-specific checks
int	file_checks(t_data *all, char *file_name)
{
	int	fd;

	if (file_invalid_name(file_name))
		return (FAILURE);
	fd = file_no_exist(file_name);
	if (record_file_attributes(all, fd))
		return (FAILURE);
	printf("---------FILE ATTRIBUTES-------\n");
	printf("MAP:\t height:%d width:%d\n", all->height, all->width);
	printf("COLOURS:\t F: %u C:%u\n", all->floor_col, all->ceiling_col);
	printf("SO:\t %s\n", all->south_text);
	printf("NO:\t %s\n", all->north_text);
	printf("EA:\t %s\n", all->east_text);
	printf("WE:\t %s\n", all->west_text);
	printf("PLAYER:\t %d", all->player);
	exit(2);
	if (record_map_attributes(all, fd))
		return (FAILURE);
	// if (record_file_attributes(all, fd))
	// 	return (FAILURE);
	// else if (file_colours(all))
	// 	return (FAILURE);
	// else if (file_textures(all))
	// 	return (FAILURE);
	close(fd);
	return (SUCCESS);
}
