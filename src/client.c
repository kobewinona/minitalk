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

static void	handle_error(char *error_message)
{
	ft_putstr_fd(error_message, STDERR_FILENO);
	exit(EXIT_FAILURE);
}

static void	send_bit(int server_pid, int signum)
{
	if (kill(server_pid, signum) == ERROR)
		handle_error(TRANSMISSON_ERR);
}

static void	send_message(int server_pid, char *message)
{
	char	c;
	int		i;
	int		k;

	i = 0;
	while (message[i] != '\0')
	{
		c = message[i];
		k = 7;
		while (k >= 0)
		{
			if ((c >> k) & 1)
				send_bit(server_pid, SIGUSR2);
			else
				send_bit(server_pid, SIGUSR1);
			usleep(500);
			k--;
		}
		i++;
	}
	ft_putstr_fd(message, STDOUT_FILENO);
	ft_putstr_fd("  ⸜(ˆᗜ ˆ˵)⸝\n\n\n", STDOUT_FILENO);
	exit(EXIT_SUCCESS);
}

int	main(int argc, char **argv)
{
	int	server_pid;

	if (argc != 3)
		handle_error(ARGS_NOT_PROVIDED_ERR);
	server_pid = ft_atoi(argv[1]);
	if (!server_pid)
		handle_error(INCORRECT_PID_ERR);
	send_message(server_pid, argv[2]);
	while (1)
		pause();
	return (0);
}
