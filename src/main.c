/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mcaro-ro <mcaro-ro@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/29 22:33:27 by mgalvez-          #+#    #+#             */
/*   Updated: 2025/09/08 06:47:54 by mcaro-ro         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cube.h"

// Muestra el mapa en consola (para debug)
void show_map(t_config *config)
{
    printf("Mapa (%d filas, %d columnas):\n", config->map_rows, config->map_width);
    for (int i = 0; i < config->map_rows; ++i)
    {
        printf("%s", config->map[i]);
    }
}

bool	check_extension(const char *file_name, const char *extension)
{
	size_t	file_len;
	size_t	ext_len;

	file_len = ft_strlen(file_name);
	ext_len = ft_strlen(extension);
	if (file_len < ext_len)
		return (false);
	return (ft_strncmp(file_name + file_len - ext_len, extension, ext_len));
}

int	main(int argc, char **argv)
{
	t_config	*config;
	int			fd;

	if (argc != 2)
		return (error_msg("Error\nNumero de argumentos invalido\n", NULL), 1);
	if (check_extension(argv[1], ".cub"))
		return (error_msg("Error\nExtension de archivo invalida\n", NULL), 1);
	fd = open(argv[1], O_RDONLY);
	if (fd < 0)
		return (error_msg("Error\nNo se pudo abrir el archivo\n", NULL), 1);
	config = ft_calloc(1, sizeof(t_config));
	if (!config)
		return (error_msg("Error\nFallo al asignar de memoria\n", config), 1);
	config->file_path = ft_strdup(argv[1]);
	if (!config->file_path)
		return (error_msg("Error\nFallo al asignar de memoria\n", config), 1);
	parse_file(config, fd);
	show_map(config);
	close(fd);
	run_game(config);
	free_config(&config);
	return (0);
}
