/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main_bonus.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pabpalma <pabpalma>                        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/15 17:50:47 by pabpalma          #+#    #+#             */
/*   Updated: 2023/11/22 10:01:56 by pabpalma         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex_bonus.h"

/*void	leaks()
{
	system("leaks -q pipex");
}*/

int	main(int argc, char **argv, char **envp)
{
	t_pipex	pipex;

	validate_args(argc, argv);
	initialize_pipex(&pipex, argc, argv, envp);
	if (ft_strncmp(argv[1], "here_doc", 8) == 0)
		execute_command(&pipex, argv + 3, argc - 4);
	else
		execute_command(&pipex, argv + 2, argc - 3);
	return (0);
}
