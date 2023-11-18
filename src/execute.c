/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pabpalma <pabpalma>                        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/17 15:07:55 by pabpalma          #+#    #+#             */
/*   Updated: 2023/11/18 12:34:45 by pabpalma         ###   ########.fr       */
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
		if(dup2(input, STDIN_FILENO) == -1 
			|| dup2(output, STDOUT_FILENO) == -1)
			handle_error("Error in dup2", 1, EXIT_FAILURE);
		close(input);
		close(output);
		cmd_args = ft_split(cmd, ' ');
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

void	execute_command(t_pipex *pipex, char *cmd1, char *cmd2)
{
	execute_single_cmd(pipex, cmd1, pipex->fd_in, pipex->pipes[1]);
	close(pipex->pipes[1]);
	execute_single_cmd(pipex, cmd2, pipex->pipes[0], pipex->fd_out);
	close(pipex->pipes[0]);
}
