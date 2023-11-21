/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pabpalma <pabpalma>                        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/17 12:04:46 by pabpalma          #+#    #+#             */
/*   Updated: 2023/11/21 11:33:55 by pabpalma         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

void	read_from_stdin(const char *limit, int write_fd)
{
	char	*line;

	while ((line = get_next_line(STDIN_FILENO)))
	{
		if (strncmp(line, limit, ft_strlen(limit)) == 0)
		{
			free(line);
			break ;
		}
		write(write_fd, line, ft_strlen(line));
		free(line);
	}
}

void	handle_error(const char *msg, int use_perror, int error_code)
{
	if (use_perror)
		perror(msg);
	else
		ft_printf("%s\n", msg);
	exit(error_code);
}

void	initialize_pipex(t_pipex *pipex, int argc, char **argv, char **envp)
{
	int	temp_pipe[2];

	pipex->envp = envp;
	if (ft_strncmp(argv[1], "here_doc", 8) == 0)
	{
		if (pipe(temp_pipe) == -1)
			handle_error("Error creating pipe for here_doc", 1, EXIT_FAILURE);
		read_from_stdin(argv[2], temp_pipe[1]);
		close(temp_pipe[1]);
		pipex->fd_in = temp_pipe[0];
		pipex->fd_out = open(argv[argc -1], O_WRONLY | O_CREAT
				| O_APPEND, 0644);
		if (pipex->fd_out < 0)
			handle_error("Error opening output file in here_doc mode", 1, 3);
	}
	else
	{
		pipex->fd_in = open(argv[1], O_RDONLY);
		if (pipex->fd_in < 0)
			handle_error("Error opening file1", 1, 2);
		pipex->fd_out = open(argv[argc - 1], O_WRONLY | O_CREAT | O_TRUNC, 0644);
		if (pipex->fd_out < 0)
			handle_error("Error opening file2", 1, 3);
	}
}
