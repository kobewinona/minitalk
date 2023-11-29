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

static void	handle_signal_acknowledgement(int signum)
{
	if (signum == SIGUSR1)
		g_is_signal_acknowledged = TRUE;
}

static void	send_bit(int server_pid, int bit)
{
	int	tries;

	tries = 0;
	while (tries < 500)
	{
		if (bit == '1')
			kill(server_pid, SIGUSR2);
		if (bit == '0')
			kill(server_pid, SIGUSR1);
		usleep(300);
		if (g_is_signal_acknowledged)
		{
			g_is_signal_acknowledged = FALSE;
			return ;
		}
		usleep(2000);
		tries++;
	}
	ft_putstr_fd(TRANSMISSON_ERR, STDERR_FILENO);
	exit(1);
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
}

int	main(int argc, char **argv)
{
	struct sigaction	sa;
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
	sa.sa_flags = SA_SIGINFO;
	sa.sa_handler = handle_signal_acknowledgement;
	sigemptyset(&sa.sa_mask);
	sigaction(SIGUSR1, &sa, NULL);
	send_message(server_pid, message);
	return (0);
}
