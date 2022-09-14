/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lleiria- <lleiria-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/20 11:01:20 by lleiria-          #+#    #+#             */
/*   Updated: 2022/09/14 16:43:05 by lleiria-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PIPEX_H
# define PIPEX_H

# include "ft_printf/ft_printf.h"
# include "libft/libft.h"
# include "get_next_line/get_next_line.h"
# include <stdio.h>
# include <errno.h>
# include <string.h>
# include <unistd.h>
# include <fcntl.h>
# include <sys/types.h>
# include <sys/wait.h>

typedef struct	s_all
{
	char	**env;
	char	**av;
	int		ac;
	int		heredoc;
	int		fd_in;
	int		fd_out;
	int		*pipe_fd;
	int		nbr_cmds;
	int		child;
	int		*pids;
	char	**cmd_op;
	char	**cmd_path;
}	t_all;

# define ERROR 1

char			*get_cmd(char *cmd, char **env);
//utils.c
int				er_msg(char *str1, char *str2, char *str3, int erno);
static void		close_pipe_fds(t_all *pp);
void			close_fds(t_all *pp);
void			free_strs(char *str, char **strs);
void			exit_error(int status, t_all *pp);
//files.c
void			get_heredoc(t_all *pp);
void			get_input(t_all *pp);
void			get_output(t_all *pp);
//initiation.c
static t_all	clear_init(void);
static void		create_pipes(t_all *pp);
t_all			lets_init(int ac, char **av, char **env);

#endif