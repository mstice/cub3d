/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map_checks.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mtice <mtice@student.42belgium.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/02 13:26:22 by mtice             #+#    #+#             */
/*   Updated: 2025/12/03 11:10:45 by mtice            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3D.h"

//-----------------------------------------------------------------------------
//checks whether the name of the map is valid (extension must be .cub)
static int	map_invalid_name(char *map_name)
{
	char	*extension;
	char	*real_map_name;

	if (!map_name || map_name[0] == '\0')
		return (FAILURE);
	extension = ft_strchr(map_name, '.');
	if (extension == NULL || extension != ft_strrchr(map_name, '.'))
		ft_exit(ERR_FILE_NAME, EXIT_FAILURE);
	if (ft_strncmp(extension, ".cub\0", 5))
		ft_exit(ERR_FILE_NAME, EXIT_FAILURE);
	real_map_name = ft_strrchr(map_name, '/');
	if (real_map_name)
	{
		real_map_name++;
		if (ft_strlen(real_map_name) < 5)
			ft_exit(ERR_FILE_NAME, EXIT_FAILURE);
	}
	else if (ft_strlen(map_name) < 5)
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
//TODO: free_all() is not well equipped to deal with exiting this function
static int	create_raw_map(t_data *all, char *map_name)
{
	int		fd;
	char	**map;
	int		j;
	char	*line;

	fd = map_no_exist(map_name);
	map = ft_calloc(sizeof(char *), all->height + 1);
	if (!map)
		return (close(fd), free_all(all), ft_exit(ERR_MALLOC, EXIT_FAILURE), FAILURE);
	j = 0;
	while (j < all->height)
	{
		line = get_next_line(fd);
		if (!line)
			break ;
		map[j] = ft_strtrim(line, "\n");
		if (!map[j]|| !(*map[j]))
		{
			free(map[j]);
			free(line);
			continue ;
		}
		if (all->width < ft_strlen(map[j]))
			all->width = ft_strlen(map[j]);
		free(line);
		all->height++;
		j++;
	}
	map[j] = NULL;
	all->raw_map = map;
	close(fd);
	return (SUCCESS);
}

//-----------------------------------------------------------------------------
 // static int	reformat_map(t_data *all, char *map_name)
 // {
 // 	int	fd;
 // 	int	j;
 // 	int	i;
 // bool wall;
 //
 // 	fd = map_no_exist(map_name);
 // wall = false;
 // 	j = 0;
 // 	while (all->raw_map[j] != NULL)
 // 	{
 // 		i = 0;
 // 		while (all->raw_map[j][i] != '\0')
 // 		{
 // 		if (all->raw_map[j][i] == '1')
 // 			wall = true;
 // 		else if (all->raw_map[j][i] == ' ' && !wall)
 // 			//nothing;
 // 		else if (all->raw_map[j][i] == '0' && !wall)
 // 		i++;
 // 		}
 // 	j++;
 // 	}
 // 	close(fd);
 // 	return (SUCCESS);
 //  }

//-----------------------------------------------------------------------------
static int	map_err_elements(t_data *all)
{
	int		j;
	int		i;

	j = 0;
	while (all->raw_map[j] != NULL)
	{
		i = 0;
		while (all->raw_map[j][i] != '\0')
		{
			// if ((j == 0 || j == all->height - 1) && all->raw_map[j][i] != ' '
			// 	&& all->raw_map[j][i] != '1' && all->raw_map[j][i] != SUB)
			// 	return (free_all(all), ft_exit(ERR_WALLS, EXIT_FAILURE), FAILURE);
			// if ((i == 0 || i == all->width - 1) && all->raw_map[j][i] != '1')
			// 	return (free_all(all), ft_exit(ERR_WALLS, EXIT_FAILURE), FAILURE);
			if (all->raw_map[j][i] == 'N' || all->raw_map[j][i] == 'E'
				|| all->raw_map[j][i] == 'S' || all->raw_map[j][i] == 'W')
			{
				if (all->player != NOPLAYER)
					return (free_all(all), ft_exit(ERR_MANY_POS, EXIT_FAILURE), FAILURE);
				all->player = all->raw_map[j][i];
			}
			if (!accepted(all->raw_map[j][i]))
				return (free_all(all), ft_exit(ERR_INV_EL, EXIT_FAILURE), FAILURE);
			i++;
		}
		j++;
	}
	if (all->player == NOPLAYER)
		return (free_all(all), ft_exit(ERR_NO_POS, EXIT_FAILURE), FAILURE);
	return (SUCCESS);
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
	close(fd);
	if (map_err_elements(all))
		return (FAILURE);
	// else if (map_err_walls(all))
	// 	return (FAILURE);
	int	i;
	i = 0;
	while (all->raw_map[i] != NULL)
	{
		printf("line[%d]: %s\n", i, all->raw_map[i]);
		i++;
	}
	return (SUCCESS);
}
