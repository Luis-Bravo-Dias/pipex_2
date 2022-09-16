/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lleiria- <lleiria-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/30 12:20:10 by lleiria-          #+#    #+#             */
/*   Updated: 2022/09/16 13:01:18 by lleiria-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../pipex.h"

//Redirects the input and output file descriptors by duplicating
//the given fds to the standard input and standard output respectively.
static void	redirect_in_out(int input, int output, t_all *pp)
{
	if (dup2(input, STDIN_FILENO) == -1)
		exit_error(1, pp);
	if (dup2(output, STDOUT_FILENO) == -1)
		exit_error(1, pp);
}

//if(first), if else(final), else(midle)
static void	set_child_in_out(t_all *pp)
{
	if (pp->child == 0)
		redirect_in_out(pp->fd_in, pp->pipe_fd[1], pp);
	else if (pp->child == pp->nbr_cmds - 1)
		redirect_in_out(pp->pipe_fd[2 * pp->child - 2], pp->fd_out, pp);
	else
		redirect_in_out(pp->pipe_fd[2 * pp->child - 2],
			pp->pipe_fd[2 * pp->child + 1], pp);
	close_fds(pp);
	if (pp->cmd_op == NULL || pp->cmd_path == NULL)
		exit_error(1, pp);
	if (execve(pp->cmd_path, pp->cmd_op, pp->env) == -1)
		exit_error(er_msg(pp->cmd_op[0], ": ", strerror(errno), 1), pp);
}

static int	wait_parent(t_all *pp)
{
	pid_t	wpid;
	int		status;
	int		exit_code;

	close_fds(pp);
	pp->child--;
	exit_code = 1;
	while (pp->child >= 0)
	{
		wpid = waitpid(pp->pids[pp->child], &status, 0);
		if (wpid == pp->pids[pp->nbr_cmds - 1])
			if ((pp->child == (pp->nbr_cmds - 1)) && WIFEXITED(status))
				exit_code = WEXITSTATUS(status);
		pp->child--;
	}
	free(pp->pipe_fd);
	free(pp->pids);
	return (exit_code);
}

static int	pipex(t_all *pp)
{
	int	exit_code;

	if (pipe(pp->pipe_fd) == -1)
		exit_error(er_msg("pipe", ": ", strerror(errno), 1), pp);
	pp->child = 0;
	while (pp->child < pp->nbr_cmds)
	{
		pp->cmd_op = ft_split(pp->av[pp->child + 2 + pp->heredoc], '');
		if (!pp->cmd_op)
			exit_error(er_msg("unexpected error", "". "", 1), pp);
		pp->cmd_path = get_cmd(pp->cmd_op[0], pp);
		pp->pids[pp->child] = fork();
		if (pp->pids[pp] == -1)
			exit_error(er_msg("fork", ": ", strerror(errno), 1), pp);
		else if (pp->pids[pp->child] == 0)
			set_child_in_out(pp);
		free_strs(pp->cmd_path, pp->cmd_op);
		pp->child++;
	}
	exit_code = wait_parent(pp);
	if (pp->heredoc == 1)
		unlink(".heredoc.tmp");
	return (exit_code);
}

int	main(int ac, char **av, char **env)
{
	t_all	pp;
	int		exit_code;

	if (ac < 5)
	{
		if (ac > 2 && !ft_strncmp("here_doc", av[1], 9))
			return (er_msg("Use format: ",
					"./pipex here_doc LIMITER cmd1 cmd2 ... cmdn file2.",
					"", 1));
		return (er_msg("Use format: ",
				"./pipex file1 cmd1 cmd2 ... cmdn file2.", "", 1));
	}
	else if (ac < 6 && !ft_strncmp("here_doc", av[1], 9))
		return (er_msg("Use format: ",
				"./pipex here_doc LIMITER cmd1 cmd2 ... cmdn file2.", "", 1));
	if (!env || env[0][0] == '\0')
		exit_error(er_msg("Unexpected error.", "", "", &pp));
	pp = lets_init(ac, av, env);
	exit_code = pipex(&pp);
	return (exit_code);
}

/*char	*get_cmd(char *cmd, char **env)
{
	char	*env_path;
	char	**paths;
	char	*cmd_path;
	char	*tmp;
	int		i;

	i = 0;
	while (env[i])
	{
		env_path = ft_strnstr(env[i], "PATH=", ft_strlen(env[i]));
		if (env_path)
		{
			env_path = ft_substr(env[i], 0, ft_strlen(env[i]));
			break ;
		}
		i++;
	}
	paths = ft_split(env_path, ':');
	free(env_path);
	i = 0;
	while (paths[i])
	{
		tmp = paths[i];
		paths[i] = ft_strjoin(paths[i], "/");
		free(tmp);
		i++;
	}
	i = 0;
	while (paths[i])
	{
		cmd_path = ft_strjoin(paths[i], cmd);
		if (access(cmd_path, F_OK | X_OK) == 0)
			return (cmd_path);
		free(cmd_path);
		i++;
	}
	free(paths);
	return (cmd_path);
}*/

/*int	main(int ac, char **av, char **env)
{
	char	*cmd_path;
	char	*options[3] = {"ls", "-la", NULL};
	char	*cmd;

	cmd = "ls";
	(void)ac;
	(void)av;
	cmd_path = get_cmd(cmd, env);
	if (!cmd_path)
	{
		perror(cmd_path);
		return (-1);
	}
	execve("/usr/bin/ls", options, env);
	printf("Victory!\n");
	free(cmd_path);
	return (0);
}*/