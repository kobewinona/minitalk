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
	while (tries < 100)
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
		tries++;
	}
	ft_printf("message transmission failed ｡°(.◜ᯅ◝)°｡\n\n\n");
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
	ft_printf("%s ⸜(ˆᗜ ˆ˵)⸝\n\n\n", message);
}

int	main(int argc, char **argv)
{
	struct sigaction	sa;
	char				*message;
	int					server_pid;

	ft_printf("BONUS\n\n");
	if (argc != 3)
	{
		ft_printf("please provide PID and a string\n");
		exit(1);
	}
	server_pid = ft_atoi(argv[1]);
	if (!server_pid)
	{
		ft_printf("please provide correct server PID\n");
		exit (1);
	}
	message = argv[2];
	sa.sa_flags = SA_SIGINFO;
	sa.sa_handler = handle_signal_acknowledgement;
	sigaction(SIGUSR1, &sa, NULL);
	send_message(server_pid, message);
	return (0);
}
