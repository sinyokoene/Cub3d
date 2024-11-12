/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   map_utils.c                                        :+:    :+:            */
/*                                                     +:+                    */
/*   By: skoene <skoene@student.codam.nl>             +#+                     */
/*                                                   +#+                      */
/*   Created: 2024/11/08 22:20:08 by skoene        #+#    #+#                 */
/*   Updated: 2024/11/09 00:19:09 by skoene        ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "../include/cub3d.h"

void	ft_free_str_array(char **array);
int		ft_str_array_len(char **array);
size_t	ft_strcspn(const char *s1, const char *s2);
void	parse_color(char *line, t_color *color, t_data *data);

void	ft_free_str_array(char **array)
{
	int	i;

	i = 0;
	while (array[i])
		free(array[i++]);
	free(array);
}

int	ft_str_array_len(char **array)
{
	int	len;

	len = 0;
	while (array[len])
		len++;
	return (len);
}

size_t	ft_strcspn(const char *s1, const char *s2)
{
	size_t	i;
	size_t	j;

	i = 0;
	while (s1[i] != '\0')
	{
		j = 0;
		while (s2[j] != '\0')
		{
			if (s1[i] == s2[j])
				return (i);
			j++;
		}
		i++;
	}
	return (i);
}

void	parse_color(char *line, t_color *color, t_data *data)
{
	char	**rgb_values;
	char	*trimmed_line;

	trimmed_line = ft_strtrim(line, " \n");
	rgb_values = ft_split(trimmed_line, ',');
	free(trimmed_line);
	if (!rgb_values || ft_str_array_len(rgb_values) != 3)
	{
		fprintf(stderr, "Error\nInvalid color format.\n");
		terminate(data);
	}
	color->r = ft_atoi(rgb_values[0]);
	color->g = ft_atoi(rgb_values[1]);
	color->b = ft_atoi(rgb_values[2]);
	ft_free_str_array(rgb_values);
	if (color->r < 0 || color->r > 255 || color->g < 0 || color->g > 255
		|| color->b < 0 || color->b > 255)
	{
		fprintf(stderr, "Error\nColor values must be in range 0-255.\n");
		terminate(data);
	}
}
