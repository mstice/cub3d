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
//checks if file exists and has correct permissions
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
static int	file_err_elements(t_data *all, int fd)
{
	int	ret;

	ret = FAILURE;
	if (invalid_col(all))
		close(fd), ft_exit(all, NULL);
	else if (invalid_txt(all->north) || invalid_txt(all->east)
			|| invalid_txt (all->south) || invalid_txt(all->west))
		close(fd), ft_exit(all, NULL);
	else if (!ft_strcmp(all->north, all->east)
			|| !ft_strcmp(all->north, all->south)
		  	|| !ft_strcmp(all->north, all->west)
		  	|| !ft_strcmp(all->east, all->south)
		  	|| !ft_strcmp(all->east, all->west)
		  	|| !ft_strcmp(all->south, all->west))
			ft_putendl_fd(ERR, 2), ft_putendl_fd(ERR_TXT_DUP, 2);
	else
		ret = SUCCESS;
	if (ret == FAILURE)
		close(fd), ft_exit(all, NULL);
	return (SUCCESS);
}

//-----------------------------------------------------------------------------
//records textures, colours, and the line at which the map contents start
//stores this information in the t_data struct
//p_line: processed line (after \n char removal)
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
		if (p_line && *p_line
			&& (!record_col(all, line, p_line, fd) && !record_text(all, line, p_line, fd)))
		{
			while (ft_isspace(*p_line))
				p_line++;
			if (*p_line)
			{
				free(p_line), free(line);
				file_err_elements(all, fd);
				close(fd), ft_exit(all, ERR_MAP_LAST);
			}
		}
		free(line), free(p_line);
		if (all->floor && all->ceiling && all->north
			&& all->east && all->south && all->west)
			break ;
		line = get_next_line(fd);
	}
	return (SUCCESS);
}

//-----------------------------------------------------------------------------
//checks if map is populated
//records height and maximum width of the map
//stores this information in the t_data struct
static int	record_map_attributes(t_data *all, int fd)
{
	char	*line;
	char	*p_line;

	line = get_next_line(fd);
	if (!line)
		close(fd), ft_exit(all, ERR_MALLOC);
	p_line = ft_strtrim(line, "\n");
	while ((!p_line || !(*p_line)) && all->map_start < 1000)
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
	if (all->height == 0 || all->width == 0)
		close(fd), ft_exit(all, ERR_MAP_LAST);
	else if (all->height < 3 || all->width < 3)
		close(fd), ft_exit(all, ERR_MAP_S);
	return (SUCCESS);
}

//-----------------------------------------------------------------------------
//performs the necessary error checking on the file and its contents before
//map-specific checks
int	file_checks(t_data *all, char *file_name)
{
	int	fd;

	if (file_invalid_name(file_name, ".cub"))
		ft_exit(all, ERR_FILE_NAME);
	fd = file_no_exist(file_name);
	if (fd == -1)
		ft_exit(all, ERR_FILE_NOEXIST);
	if (record_file_attributes(all, fd))
		return (FAILURE);
	if (file_err_elements(all, fd))
		return (FAILURE);
	if (record_map_attributes(all, fd))
		return (FAILURE);
	close(fd);
	return (SUCCESS);
}
