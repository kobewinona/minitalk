/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   client.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dklimkin <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/27 15:11:40 by dklimkin          #+#    #+#             */
/*   Updated: 2023/11/27 15:11:41 by dklimkin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minitalk.h"

static int	g_is_signal_acknowledged;

static void	handle_error(char *error_message)
{
	ft_putstr_fd(error_message, STDERR_FILENO);
	exit(EXIT_FAILURE);
}

static void	handle_signal_acknowledgement(int signum)
{
	if (signum == SIGUSR1)
		g_is_signal_acknowledged = TRUE;
}

static void	send_bit(int server_pid, int bit)
{
	int	tries;

	tries = 0;
	while (tries++ < 500)
	{
		if (bit == '1')
		{
			if (kill(server_pid, SIGUSR2) == ERROR)
				handle_error(TRANSMISSON_ERR);
		}
		if (bit == '0')
		{
			if (kill(server_pid, SIGUSR1) == ERROR)
				handle_error(TRANSMISSON_ERR);
		}
		usleep(300);
		if (g_is_signal_acknowledged)
		{
			g_is_signal_acknowledged = FALSE;
			return ;
		}
		usleep(2000);
	}
	handle_error(TRANSMISSON_ERR);
}

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
				send_bit(server_pid, '1');
			else
				send_bit(server_pid, '0');
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
	struct sigaction	sa;
	int					server_pid;

	if (argc != 3)
		handle_error(ARGS_NOT_PROVIDED_ERR);
	server_pid = ft_atoi(argv[1]);
	if (!server_pid)
		handle_error(INCORRECT_PID_ERR);
	if (sigaction(SIGUSR1, &sa, NULL) == ERROR)
		handle_error(SIGHANDLER_ERR);
	if (sigaction(SIGUSR2, &sa, NULL) == ERROR)
		handle_error(SIGHANDLER_ERR);
	sa.sa_flags = SA_RESTART;
	sa.sa_handler = handle_signal_acknowledgement;
	sigemptyset(&sa.sa_mask);
	sigaction(SIGUSR1, &sa, NULL);
	send_message(server_pid, argv[2]);
	while (1)
		pause();
	return (0);
}
