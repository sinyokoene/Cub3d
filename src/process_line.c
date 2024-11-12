/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   process_line.c                                     :+:    :+:            */
/*                                                     +:+                    */
/*   By: skoene <skoene@student.codam.nl>             +#+                     */
/*                                                   +#+                      */
/*   Created: 2024/11/08 23:26:25 by skoene        #+#    #+#                 */
/*   Updated: 2024/11/08 23:26:30 by skoene        ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "../include/cub3d.h"

void	process_texture_line(char *line, t_data *data, int *handled);
void	process_color_line(char *line, t_data *data, int *handled);
void	process_map_line(char *line, t_list **map_lines, int *in_map,
			int *handled);
void	handle_invalid_line(char *line, int handled, t_data *data);
void	process_line(char *line, t_data *data, t_list **map_lines, int *in_map);

void	process_texture_line(char *line, t_data *data, int *handled)
{
	if (ft_strncmp(line, "NO ", 3) == 0)
		data->north_texture_path = ft_strdup(line + 3);
	else if (ft_strncmp(line, "SO ", 3) == 0)
		data->south_texture_path = ft_strdup(line + 3);
	else if (ft_strncmp(line, "WE ", 3) == 0)
		data->west_texture_path = ft_strdup(line + 3);
	else if (ft_strncmp(line, "EA ", 3) == 0)
		data->east_texture_path = ft_strdup(line + 3);
	else
		return ;
	*handled = 1;
}

void	process_color_line(char *line, t_data *data, int *handled)
{
	if (ft_strncmp(line, "F ", 2) == 0)
		parse_color(line + 1, &data->floor_color, data);
	else if (ft_strncmp(line, "C ", 2) == 0)
		parse_color(line + 1, &data->ceiling_color, data);
	else
		return ;
	*handled = 1;
}

void	process_map_line(char *line, t_list **map_lines, int *in_map,
		int *handled)
{
	if (line[0] == '1' || line[0] == '0' || line[0] == ' ')
	{
		*in_map = 1;
		ft_lstadd_back(map_lines, ft_lstnew(ft_strdup(line)));
		*handled = 1;
	}
}

void	handle_invalid_line(char *line, int handled, t_data *data)
{
	if (!handled)
	{
		fprintf(stderr, "Error\nInvalid line in map file: %s\n", line);
		free(line);
		terminate(data);
	}
}

void	process_line(char *line, t_data *data, t_list **map_lines, int *in_map)
{
	int	handled;

	handled = 0;
	line[ft_strcspn(line, "\n")] = '\0';
	if (line[0] == '\0')
	{
		free(line);
		return ;
	}
	if (!*in_map)
	{
		process_texture_line(line, data, &handled);
		process_color_line(line, data, &handled);
	}
	process_map_line(line, map_lines, in_map, &handled);
	handle_invalid_line(line, handled, data);
	free(line);
}
