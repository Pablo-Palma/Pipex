/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pabpalma <pabpalma>                        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/17 15:07:55 by pabpalma          #+#    #+#             */
/*   Updated: 2023/11/21 11:31:24 by pabpalma         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

void	execute_single_cmd(t_pipex *pipex, char *cmd, int input, int output)
{
	pid_t	pid;
	int		status;
	char	**cmd_args;
	char	*cmd_path;
	int		exit_status;

	exit_status = 0;
	pid = fork();
	if (pid == -1)
		handle_error("Error in fork", 1, EXIT_FAILURE);
	else if (pid == 0)
	{
		if (dup2 (input, STDIN_FILENO) == -1
			|| dup2 (output, STDOUT_FILENO) == -1)
			handle_error("Error in dup2", 1, EXIT_FAILURE);
		close(input);
		close(output);
		cmd_args = split_cmd(cmd);
		if (!cmd_args)
			handle_error("Error splitting command", 0, 2);
		cmd_path = get_path(cmd_args[0], getenv("PATH"));
		if (!cmd_path)
			handle_error("command not found", 0, 127);
		execve(cmd_path, cmd_args, pipex->envp);
		ft_free_arrays(cmd_args);
		handle_error("Error in execve", 1, EXIT_FAILURE);
		free(cmd_path);
	}
	else
	{
		waitpid(pid, &status, 0);
		if (WIFEXITED(status))
		{
			exit_status = WEXITSTATUS(status);
			if (exit_status == 127)
				handle_error("Error: Command not found", 0, 127);
			else if (exit_status != 0)
				ft_printf("Error code: %d\n", exit_status);
		}
	}
}

void	execute_command(t_pipex *pipex, char **cmds, int num_cmds)
{
	int	i;
	int	input_fd;
	int	pipes[2];

	i = 0;
	input_fd = pipex->fd_in;
	while (i < num_cmds)
	{
		if (i < num_cmds - 1)
		{
			if (pipe(pipes) == -1)
				handle_error("Error creating pipe", 1, EXIT_FAILURE);
		}
		if (i == num_cmds - 1)
			execute_single_cmd(pipex, cmds[i], input_fd, pipex->fd_out);
		else
			execute_single_cmd(pipex, cmds[i], input_fd, pipes[1]);
		if (input_fd != pipex->fd_in)
			close(input_fd);
		if (i < num_cmds -1)
		{
			close(pipes[1]);
			input_fd = pipes[0];
		}
		i++;
	}
}
