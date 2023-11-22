/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser_bonus.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pabpalma <pabpalma>                        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/18 10:46:14 by pabpalma          #+#    #+#             */
/*   Updated: 2023/11/22 10:02:10 by pabpalma         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex_bonus.h"

void	validate_args(int argc, char **argv)
{
	int	i;

	i = 2;
	if (argc < 5)
		handle_error("Usage: ./pipex file1 cmd1 cmd2 ... file2", 0, 5);
	if (ft_strncmp(argv[1], "here_doc", 8) != 0)
	{
		if (access(argv[1], R_OK) == -1)
			handle_error("Input Error", 1, 6);
	}
	while (i < argc -1)
	{
		if (ft_strlen(argv[i]) == 0)
			handle_error("Error: commands cannot be empty", 0, 7);
		i++;
	}
}
