/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pabpalma <pabpalma>                        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/17 10:45:41 by pabpalma          #+#    #+#             */
/*   Updated: 2023/11/22 18:55:00 by pabpalma         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PIPEX_H
# define PIPEX_H

# define ERROR_OPEN_FILE1 2
# define ERROR_OPEN_FILE2 3
# define ERROR_PIPE_CREATION 4
# define ERROR_SPLIT_CMD 5
# define ERROR_EXECVE 6
# define ERROR_COMMAND_NOT_FOUND 127

# include "libft.h"
# include <sys/wait.h> //waitpid
# include <fcntl.h> //open

typedef struct s_pipex
{
	int		fd_in;
	int		fd_out;
	int		pipes[2];
	char	**envp;
}			t_pipex;

///###   PARSER
void	validate_args(int argc, char **argv);

///###   SPLIT_CMD
char	**split_cmd(const char *cmd);

////###   GET_PATH
char	*get_path(char *cmd, const char *env_path);

///###   EXECUTE
void	execute_command(t_pipex *pipex, char *cmd1, char *cmd2);

///###   UTILS
void	initialize_pipex(t_pipex *pipex, char **argv, char **envp);
void	handle_error(const char *msg, int use_perror, int error_code);

#endif
