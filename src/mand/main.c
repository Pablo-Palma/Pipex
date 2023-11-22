/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pabpalma <pabpalma>                        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/15 17:50:47 by pabpalma          #+#    #+#             */
/*   Updated: 2023/11/22 12:20:06 by pabpalma         ###   ########.fr       */
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

	validate_args(argc, argv);
	initialize_pipex(&pipex, argv, envp);
	execute_command(&pipex, argv[2], argv[3]);
	return (0);
}
