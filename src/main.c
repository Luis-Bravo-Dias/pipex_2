/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lleiria- <lleiria-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/30 12:20:10 by lleiria-          #+#    #+#             */
/*   Updated: 2022/08/30 17:08:13 by lleiria-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../pipex.h"

int main(int ac, char **av, char **env)
{
    char *options[3] = {"ls", "-la", NULL};

    (void)ac;
    (void)av;
    execve("/usr/bin/ls", options, env);
    return (0);
}