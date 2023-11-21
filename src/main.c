/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pabpalma <pabpalma>                        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/15 17:50:47 by pabpalma          #+#    #+#             */
/*   Updated: 2023/11/21 07:32:24 by pabpalma         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

/*void	leaks()
{
	system("leaks -q pipex");
}*/

int	main(int argc, char **argv, char **envp)
{
	t_pipex	pipex;

//	atexit(leaks);
	validate_args(argc, argv);
	initialize_pipex(&pipex, argc, argv, envp);
	execute_command(&pipex, argv + 2, argc - 3);
	return (0);
}
