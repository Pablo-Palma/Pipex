/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pabpalma <pabpalma>                        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/18 10:46:14 by pabpalma          #+#    #+#             */
/*   Updated: 2023/11/20 17:43:36 by pabpalma         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

void	validate_args(int argc, char **argv)
{
	if (argc < 5)
		handle_error("Usage: ./pipex file1 cmd1 cmd2 ... file2", 0, 5);
	if (access(argv[1], R_OK) == -1)
		handle_error("Input Error", 1, 6);
	if (ft_strlen(argv[argc - 1]) == 0 || ft_strlen(argv[3]) == 0)
		handle_error("Error: commands cannot be empty", 0, 7);
}
