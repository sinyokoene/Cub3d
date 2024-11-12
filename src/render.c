/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   render.c                                           :+:    :+:            */
/*                                                     +:+                    */
/*   By: skoene <skoene@student.codam.nl>             +#+                     */
/*                                                   +#+                      */
/*   Created: 2024/11/12 20:38:04 by skoene        #+#    #+#                 */
/*   Updated: 2024/11/12 20:51:02 by skoene        ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "../include/cub3d.h"

void	clear_screen(t_data *data)
{
	memset(data->image->pixels, 0, WINDOW_WIDTH * WINDOW_HEIGHT
		* sizeof(uint32_t));
}

void	draw_floor_ceiling(t_data *data, uint32_t floor_color,
		uint32_t ceiling_color)
{
	uint32_t	color;
	int			y;
	int			x;

	y = 0;
	while (y < WINDOW_HEIGHT)
	{
		if (y < WINDOW_HEIGHT / 2)
			color = ceiling_color;
		else
			color = floor_color;
		x = 0;
		while (x < WINDOW_WIDTH)
		{
			mlx_put_pixel(data->image, x, y, color);
			x++;
		}
		y++;
	}
}

void	draw_vertical_line(t_data *data, int x, t_ray *ray,
		mlx_texture_t *texture)
{
	int			y;
	uint32_t	color;
	int			tex_y;

	y = ray->draw_start;
	while (y < ray->draw_end)
	{
		tex_y = (int)ray->tex_pos & (texture->height - 1);
		ray->tex_pos += ray->step;
		color = get_texture_pixel(texture, ray->tex_x, tex_y);
		if (ray->side == 1)
			color = (color >> 1) & 0x7F7F7F7F;
		mlx_put_pixel(data->image, x, y, color);
		y++;
	}
}

void	mlx_draw_rectangle(mlx_image_t *image, t_coords pos, t_coords size,
		uint32_t color)
{
	int	i;
	int	j;

	j = pos.y;
	while (j < pos.y + size.y)
	{
		i = pos.x;
		while (i < pos.x + size.x)
		{
			if (i >= 0 && i < (int)image->width && j >= 0
				&& j < (int)image->height)
				mlx_put_pixel(image, i, j, color);
			i++;
		}
		j++;
	}
}

void	render(t_data *data)
{
	uint32_t		floor_color;
	uint32_t		ceiling_color;
	t_ray			ray;
	int				x;
	mlx_texture_t	*texture;

	floor_color = rgb_to_hex(data->floor_color);
	ceiling_color = rgb_to_hex(data->ceiling_color);
	x = 0;
	clear_screen(data);
	draw_floor_ceiling(data, floor_color, ceiling_color);
	while (x < WINDOW_WIDTH)
	{
		calculate_ray(data, x, &ray);
		calculate_step_initial_side_dist(data, &ray);
		perform_dda(data, &ray);
		calculate_perp_wall_dist(data, &ray);
		calculate_line_dimensions(&ray);
		texture = select_texture(data, &ray);
		calculate_texture_coordinates(data, &ray, texture);
		draw_vertical_line(data, x, &ray, texture);
		x++;
	}
	draw_fps(data);
	draw_minimap(data);
}
