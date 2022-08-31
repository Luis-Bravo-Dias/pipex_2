/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lleiria- <lleiria-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/30 12:20:10 by lleiria-          #+#    #+#             */
/*   Updated: 2022/08/31 18:12:27 by lleiria-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../pipex.h"

char    *get_cmd(char *cmd, char **env)
{
    char    *env_path;
    char    **paths;
    char    *cmd_path;
    char    *tmp;
    int     i;
    
    i = 0;
    while (env[i])
    {
        env_path = ft_strnstr(env[i], "PATH=", ft_strlen(env[i]));
        if (env_path)
        {
            env_path = ft_substr(env[i], 0, ft_strlen(env[i]));
            break;
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
}

int main(int ac, char **av, char **env)
{
    char    *cmd_path;
    char    *options[3] = {"ls", "-la", NULL};
    char    *cmd;

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
    printf("Victory!");
    free(cmd_path);
    return (0);
}