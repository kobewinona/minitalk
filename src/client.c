/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   client.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dklimkin <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/23 15:22:14 by dklimkin          #+#    #+#             */
/*   Updated: 2023/11/23 15:22:14 by dklimkin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minitalk.h"

static int	g_is_signal_acknowledged;

static void	handle_signal_acknowledgement(int signum)
{
	(void)signum;
	g_is_signal_acknowledged = TRUE;
}

static void	send_client_pid(int server_pid)
{
	int	cleint_pid;
	int	i;

	cleint_pid = getpid();
	i = 31;
	while (i >= 0)
	{
		if ((cleint_pid >> i) & 1)
			kill(server_pid, SIGUSR2);
		else
			kill(server_pid, SIGUSR1);
		usleep(500);
		i--;
	}
}

static void	send_bit(int server_pid, int bit)
{
	while (1)
	{
		if (bit == '1')
			kill(server_pid, SIGUSR2);
		if (bit == '0')
			kill(server_pid, SIGUSR1);
		usleep(100);
		if (g_is_signal_acknowledged)
		{
			g_is_signal_acknowledged = FALSE;
			break ;
		}
	}
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
			usleep(100);
			k--;
		}
		i++;
	}
}

int	main(int argc, char **argv)
{
	struct sigaction	sa;
	char				*message;
	int					server_pid;

	ft_printf("Client PID: %d\n\n", getpid());
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
	send_client_pid(server_pid);
	sa.sa_flags = 0;
	sa.sa_handler = handle_signal_acknowledgement;
	sigaction(SIGUSR1, &sa, NULL);
	ft_printf("client says:\n\n%s ⸜(ˆᗜˆ˵ )⸝\n\n\n", message);
	send_message(server_pid, message);
	return (0);
}
