/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map_checks.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mtice <mtice@student.42belgium.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/02 13:26:22 by mtice             #+#    #+#             */
/*   Updated: 2025/12/02 17:42:30 by mtice            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3D.h"

//-----------------------------------------------------------------------------
//checks whether the name of the map is valid (extension must be .cub)
static int	map_invalid_name(char *map_name)
{
	char	*extension;

	if (!map_name || map_name[0] == '\0')
		return (FAILURE);
	extension = ft_strchr(map_name, '.');
	if (extension == NULL || extension != ft_strrchr(map_name, '.'))
		ft_exit(ERR_FILE_NAME, EXIT_FAILURE);
	if (ft_strncmp(extension, ".cub\0", 5))
		ft_exit(ERR_FILE_NAME, EXIT_FAILURE);
	if (ft_strlen(map_name) < 5)
		ft_exit(ERR_FILE_NAME, EXIT_FAILURE);
	return (SUCCESS);
}

//-----------------------------------------------------------------------------
//checks if map exists and has correct permissions
static int	map_no_exist(char *map_name)
{
	int	fd;

	fd = open(map_name, O_RDONLY);
	if (fd < 0 || fd > 1024)
		ft_exit(ERR_FILE_NOEXIST, EXIT_FAILURE);
	return (fd);
}

//-----------------------------------------------------------------------------
//finds height of map for later reference
//checks if map is populated
//p_line -> processed line (after \n char removal)
static int	record_map_attributes(t_data *all, int fd)
{
	int		height;
	int		width;
	char	*line;
	char	*p_line;

	height = 0;
	width = 0;
	line = get_next_line(fd);
	if (!line)
		ft_exit(ERR_FILE_EMPTY, EXIT_FAILURE);
	while (line != NULL)
	{
		p_line = ft_strtrim(line, "\n");
		free(line);
		line = get_next_line(fd);
		if (!p_line || p_line[0] == '\0')
		{
			free(p_line);
			continue ;
		}
		if (width < ft_strlen(p_line))
			width = ft_strlen(p_line);
		free(p_line);
		height++;
	}
	free(line);
	close(fd);
	all->height = height;
	return (SUCCESS);
}

//-----------------------------------------------------------------------------
//creates a 2-dimensional array of the map in chars
//TODO: what if there are multiple empty lines or newlines in map?
static int	create_raw_map(t_data *all, char *map_name)
{
	int		fd;
	char	**map;
	char	*line;
	int		i;
	int		width;

	fd = map_no_exist(map_name);
	if (fd == -1)
		ft_exit(ERR_FILE_OPEN, EXIT_FAILURE);
	map = ft_calloc(sizeof(char *), all->height + 1);
	if (!map)
		ft_exit(ERR_MALLOC, EXIT_FAILURE);
	i = -1;
	width = 0;
	while (i++ < all->height)
	{
		line = get_next_line(fd);
		if (!line)
			continue ;
		map[i] = ft_strtrim(line, "\n");
		if (!map[i] || map[i][0] == '\0')
			continue ;
		if (width <= ft_strlen(map[i]))
			width = ft_strlen(map[i]);
		free(line);
	}
	map[i] = NULL;
	all->raw_map = map;
	close(fd);
	return (SUCCESS);
}

//-----------------------------------------------------------------------------
static int	create_uniform_map(t_data *all, char *map_name)
{
	int	fd;

	fd = map_no_exist(map_name);
	if (fd == -1)
		free_all(all), ft_exit(ERR_FILE_OPEN, EXIT_FAILURE)
	
	
}
////-----------------------------------------------------------------------------
//static int	map_err_walls(t_data *all)
//{
//
//}

int	map_checks(t_data *all, char *map_name)
{
	int	fd;

	if (map_invalid_name(map_name))
		return (FAILURE);
	fd = map_no_exist(map_name);
	if (fd == -1)
		return (FAILURE);
	else if (record_map_attributes(all, fd))
		return (FAILURE);
	else if (create_raw_map(all, map_name))
		return (FAILURE);
	int	i;
	i = 0;
	while (all->raw_map[i] != NULL)
	{
		printf("line[%d]: %s\n", i, all->raw_map[i]);
		i++;
	}
	
	// else if (map_err_walls(all))
	// 	return (FAILURE);
	// else if (map_err_elements(all))
	// 	return (FAILURE);
	return (SUCCESS);
}
