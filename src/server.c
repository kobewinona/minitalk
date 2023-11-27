/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   server.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dklimkin <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/23 15:21:42 by dklimkin          #+#    #+#             */
/*   Updated: 2023/11/23 15:21:43 by dklimkin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minitalk.h"

static int	g_client_pid;

static void	handle_signal_message(int signum)
{
	static char	c;
	static int	bits;

	c = c | (signum == SIGUSR2);
	bits++;
	if (bits == 8)
	{
		write(1, &c, 1);
		bits = 0;
		c = 0;
	}
	else
		c <<= 1;
	kill(g_client_pid, SIGUSR1);
}

static void	get_client_pid(int signum)
{
	struct sigaction	sa;
	static int			bits;

	g_client_pid |= (signum == SIGUSR2);
	bits++;
	if (bits == 32)
	{
		ft_printf("Client PID: %d\n", g_client_pid);
		sigemptyset(&sa.sa_mask);
		sa.sa_flags = 0;
		sa.sa_handler = handle_signal_message;
		sigaction(SIGUSR1, &sa, NULL);
		sigaction(SIGUSR2, &sa, NULL);
	}
	else
		g_client_pid <<= 1;
}

int	main(void)
{
	struct sigaction	sa;
	int					server_pid;
	int					client_pid;

	sigemptyset(&sa.sa_mask);
	sa.sa_flags = 0;
	sa.sa_handler = get_client_pid;
	server_pid = getpid();
	ft_printf("˖⁺｡˚⋆˙₊˚✧  ੈ‧₊˚*‧.₊˚\n\nServer PID: %d | ( ᵔ ᵕ ᵔ) ", server_pid);
	client_pid = 0;
	if (sigaction(SIGUSR1, &sa, NULL) == ERROR)
	{
		write(STDERR_FILENO, "Error setting SIGUSR1 handler", 29);
		return (1);
	}
	if (sigaction(SIGUSR2, &sa, NULL) == ERROR)
	{
		write(STDERR_FILENO, "Error setting SIGUSR2 handler", 29);
		return (1);
	}
	sigaction(SIGUSR1, &sa, NULL);
	sigaction(SIGUSR2, &sa, NULL);
	while (1)
		pause();
	return (0);
}
