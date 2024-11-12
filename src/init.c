/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   init.c                                             :+:    :+:            */
/*                                                     +:+                    */
/*   By: aaoulad- <aaoulad-@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2024/11/05 18:38:08 by aaoulad-      #+#    #+#                 */
/*   Updated: 2024/11/12 20:56:07 by skoene        ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "../include/cub3d.h"

void	init_game(t_data *data)
{
	data->player.move_speed = 0.07;
	data->player.rot_speed = 0.05;
	ft_bzero(data->key_states, sizeof(data->key_states));
	mlx_set_cursor_mode(data->mlx, MLX_MOUSE_DISABLED);
	data->frame_count = 0;
	data->fps = 0.0;
	data->last_time = mlx_get_time();
}
