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
}

int	main(void)
{
	struct sigaction	sa;
	int					server_pid;

	server_pid = getpid();
	sa.sa_flags = 0;
	sa.sa_handler = handle_signal_message;
	sigemptyset(&sa.sa_mask);
	ft_printf("˖⁺｡˚⋆˙₊˚✧  ੈ‧₊˚*‧.₊˚˖⁺｡˚⋆˙₊˚\n\n");
	ft_printf("Server PID: %d | ( ᵔ ᵕ ᵔ) ", server_pid);
	if (sigaction(SIGUSR1, &sa, NULL) == ERROR)
	{
		ft_putstr_fd(SIGHANDLER_ERR, STDERR_FILENO);
		return (1);
	}
	if (sigaction(SIGUSR2, &sa, NULL) == ERROR)
	{
		ft_putstr_fd(SIGHANDLER_ERR, STDERR_FILENO);
		return (1);
	}
	sigaction(SIGUSR1, &sa, NULL);
	sigaction(SIGUSR2, &sa, NULL);
	while (1)
		pause();
	return (0);
}
