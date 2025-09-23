/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mcaro-ro <mcaro-ro@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/29 22:33:27 by mgalvez-          #+#    #+#             */
/*   Updated: 2025/09/23 17:30:13 by mcaro-ro         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cube.h"

// Muestra el mapa en consola (para debug)
void	show_map(t_config *config)
{
	int	i;

	i = 0;
	printf("Mapa (%d filas, %f angle,:\n",
		config->map_rows, config->player_angle);
	while (i < config->map_rows)
	{
		printf("%s", config->map[i]);
		i++;
	}
}

void	drain_gnl(int fd)
{
	char	*tmp;

	tmp = get_next_line(fd);
	while (tmp)
	{
		free(tmp);
		tmp = get_next_line(fd);
	}
}

bool	check_extension(const char *arg, const char *extension)
{
	const char	*base;
	const char	*p;
	size_t		base_len;
	size_t		ext_len;

	base = arg;
	p = arg;
	ext_len = ft_strlen(extension);
	if (!arg || !*arg)
		return (true);
	while (*p)
	{
		if (*p == '/')
			base = p + 1;
		p++;
	}
	base_len = ft_strlen(base);
	if (base[0] == '.')
		return (true);
	if (base_len <= ext_len)
		return (true);
	if (ft_strncmp(base + base_len - ext_len, extension, ext_len) != 0)
		return (true);
	return (false);
}

int	main(int argc, char **argv)
{
	t_config	*config;
	int			fd;

	if (argc != 2)
		return (error_msg("Error\tNumero de argumentos invalido.\n"));
	if (check_extension(argv[1], ".cub"))
		return (error_msg("Error\tExtension de archivo invalida.\n"));
	fd = open(argv[1], O_RDONLY);
	if (fd < 0)
		return (error_msg("Error\tNo se pudo abrir el archivo.\n"));
	config = ft_calloc(1, sizeof(t_config));
	if (!config)
	{
		close(fd);
		return (error_msg("Error\tFallo al asignar de memoria.\n"));
	}
	config->file_path = ft_strdup(argv[1]);
	if (!config->file_path)
	{
		close(fd);
		free(config);
		return (error_msg("Error\tFallo al asignar de memoria.\n"));
	}
	if (parse_file(config, fd) == EXIT_FAILURE)
	{
		close(fd);
		free_config(&config);
		return (EXIT_FAILURE);
	}
	close(fd);
	if (run_game(config) == EXIT_FAILURE)
	{
		free_mlx(config);
		return (EXIT_FAILURE);
	}
	free_mlx(config);
	return (EXIT_SUCCESS);
}
