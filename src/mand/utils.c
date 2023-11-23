/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pabpalma <pabpalma>                        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/17 12:04:46 by pabpalma          #+#    #+#             */
/*   Updated: 2023/11/22 16:50:15 by pabpalma         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

void	handle_error(const char *msg, int use_perror, int error_code)
{
	if (use_perror)
		perror(msg);
	else
		ft_printf("%s\n", msg);
	exit(error_code);
}

void	initialize_pipex(t_pipex *pipex, char **argv, char **envp)
{
	pipex->envp = envp;
	pipex->fd_in = open(argv[1], O_RDONLY);
	if (pipex->fd_in < 0)
		handle_error("Error opening file1", 1, ERROR_OPEN_FILE1);
	pipex->fd_out = open(argv[4], O_WRONLY | O_CREAT | O_TRUNC, 0644);
	if (pipex->fd_out < 0)
		handle_error("Error opening file2", 1, ERROR_OPEN_FILE2);
	if (pipe(pipex->pipes) == -1)
		handle_error("pipe failed", 1, ERROR_PIPE_CREATION);
}
