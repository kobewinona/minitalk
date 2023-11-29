/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   server.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dklimkin <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/27 15:11:22 by dklimkin          #+#    #+#             */
/*   Updated: 2023/11/27 15:11:23 by dklimkin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minitalk.h"

static void	handle_error(char *error_message)
{
	ft_putstr_fd(error_message, STDERR_FILENO);
	exit(EXIT_FAILURE);
}

static void	handle_signal_message(int signo, siginfo_t *info, void *context)
{
	static char	c;
	static int	bits;

	(void)context;
	c = c | (signo == SIGUSR2);
	bits++;
	if (bits == 8)
	{
		write(1, &c, 1);
		bits = 0;
		c = 0;
	}
	else
		c <<= 1;
	if (kill(info->si_pid, SIGUSR1) == ERROR)
		handle_error(UNKNOWN_SERVER_ERR);
}

int	main(void)
{
	struct sigaction	sa;
	int					server_pid;

	server_pid = getpid();
	sa.sa_flags = SA_SIGINFO;
	sa.sa_sigaction = handle_signal_message;
	sigemptyset(&sa.sa_mask);
	ft_printf("Server PID: %d | ( ᵔ ᵕ ᵔ) ", server_pid);
	if (sigaction(SIGUSR1, &sa, NULL) == ERROR)
		handle_error(SIGHANDLER_ERR);
	if (sigaction(SIGUSR2, &sa, NULL) == ERROR)
		handle_error(SIGHANDLER_ERR);
	sigaction(SIGUSR1, &sa, NULL);
	sigaction(SIGUSR2, &sa, NULL);
	while (1)
		pause();
	return (0);
}
