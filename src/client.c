/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   client.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dklimkin <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/27 15:11:30 by dklimkin          #+#    #+#             */
/*   Updated: 2023/11/27 15:11:31 by dklimkin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minitalk.h"

static void	send_message(int server_pid, char *message)
{
	char	c;
	char	bit;
	int		i;
	int		k;

	i = 0;
	bit = 0;
	while (message[i] != '\0')
	{
		c = message[i];
		k = 7;
		while (k >= 0)
		{
			if ((c >> k) & 1)
				kill(server_pid, SIGUSR2);
			else
				kill(server_pid, SIGUSR1);
			usleep(500);
			k--;
		}
		i++;
	}
	ft_putstr_fd(message, STDOUT_FILENO);
	ft_putstr_fd("  ⸜(ˆᗜ ˆ˵)⸝\n\n\n", STDOUT_FILENO);
}

int	main(int argc, char **argv)
{
	char				*message;
	int					server_pid;

	if (argc != 3)
	{
		ft_putstr_fd(ARGS_NOT_PROVIDED_ERR, STDERR_FILENO);
		exit(1);
	}
	server_pid = ft_atoi(argv[1]);
	if (!server_pid)
	{
		ft_putstr_fd(INCORRECT_PID_ERR, STDERR_FILENO);
		exit (1);
	}
	message = argv[2];
	send_message(server_pid, message);
	return (0);
}
