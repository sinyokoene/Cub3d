/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   debug.c                                            :+:    :+:            */
/*                                                     +:+                    */
/*   By: aaoulad- <aaoulad-@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2024/11/05 18:39:40 by aaoulad-      #+#    #+#                 */
/*   Updated: 2024/11/09 00:02:37 by skoene        ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "../include/cub3d.h"

void	print_map(char **map)
{
	int	i;

	i = 0;
	printf("Map:\n");
	while (map[i])
	{
		printf("%s\n", map[i]);
		i++;
	}
}
