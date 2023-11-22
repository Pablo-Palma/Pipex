/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute_bonus.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pabpalma <pabpalma>                        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/17 15:07:55 by pabpalma          #+#    #+#             */
/*   Updated: 2023/11/22 10:30:53 by pabpalma         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex_bonus.h"

void	execute_command_child(t_pipex *pipex, char *cmd, int input, int output)
{
	char	**cmd_args;
	char	*cmd_path;

	cmd_args = split_cmd(cmd);
	if (!cmd_args)
		handle_error("Error splitting command", 0, 2);
	cmd_path = get_path(cmd_args[0], getenv("PATH"));
	if (!cmd_path)
		handle_error("command not found", 0, 127);
	if (dup2 (input, STDIN_FILENO) == -1
		|| dup2 (output, STDOUT_FILENO) == -1)
		handle_error("Error in dup2", 1, EXIT_FAILURE);
	close(input);
	close(output);
	execve(cmd_path, cmd_args, pipex->envp);
	ft_free_arrays(cmd_args);
	handle_error("Error in execve", 1, EXIT_FAILURE);
	free(cmd_path);
}

void	execute_single_cmd(t_pipex *pipex, char *cmd, int input, int output)
{
	pid_t	pid;
	int		status;
	int		exit_status;

	exit_status = 0;
	pid = fork();
	if (pid == -1)
		handle_error("Error in fork", 1, EXIT_FAILURE);
	else if (pid == 0)
		execute_command_child(pipex, cmd, input, output);
	else
	{
		waitpid(pid, &status, 0);
		if (WIFEXITED(status))
		{
			exit_status = WEXITSTATUS(status);
			if (exit_status == EXIT_FAILURE)
				exit(EXIT_FAILURE);
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
			create_pipe(pipes);
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
