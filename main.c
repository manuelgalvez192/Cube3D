/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mgalvez- <mgalvez-@student.42madrid>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/29 22:33:27 by mgalvez-          #+#    #+#             */
/*   Updated: 2025/08/29 23:47:03 by mgalvez-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cube.h"

bool check_extension(const char *file_name, const char *extension)
{
	size_t file_len = ft_strlen(file_name);
	size_t ext_len = ft_strlen(extension);
	if (file_len < ext_len)
		return (false);
	return (ft_strncmp(file_name + file_len - ext_len, extension, ext_len));
}

int	main(int argc, char **argv)
{
	if (argc != 2)
		return (perror("Error\nNumero de argunmentos invalido\n"), 1);
	if (!check_extension(argv[1], ".cub"))
		return (perror("Error\nExtension de archivo invalida\n"), 1);
	t_config config;
	if (parse_file(argv[1], &config))
		return (1);
	
	return (0);
}