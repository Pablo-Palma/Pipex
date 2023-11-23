/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pabpalma <pabpalma>                        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/17 15:07:55 by pabpalma          #+#    #+#             */
/*   Updated: 2023/11/22 18:56:01 by pabpalma         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

void	execute_command_child(t_pipex *pipex, char *cmd, int input, int output)
{
	char	**cmd_args;
	char	*cmd_path;

	cmd_args = split_cmd(cmd);
	if (!cmd_args)
		handle_error("Error splitting command", 0, ERROR_SPLIT_CMD);
	cmd_path = get_path(cmd_args[0], getenv("PATH"));
	if (!cmd_path)
		handle_error("command not found", 0, ERROR_COMMAND_NOT_FOUND);
	if (dup2 (input, STDIN_FILENO) == -1
		|| dup2 (output, STDOUT_FILENO) == -1)
		handle_error("Error in dup2", 1, EXIT_FAILURE);
	close(input);
	close(output);
	execve(cmd_path, cmd_args, pipex->envp);
	ft_free_arrays(cmd_args);
	handle_error("Error in execve", 1, ERROR_EXECVE);
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

void	execute_command(t_pipex *pipex, char *cmd1, char *cmd2)
{
	execute_single_cmd(pipex, cmd1, pipex->fd_in, pipex->pipes[1]);
	close(pipex->pipes[1]);
	execute_single_cmd(pipex, cmd2, pipex->pipes[0], pipex->fd_out);
	close(pipex->pipes[0]);
}
