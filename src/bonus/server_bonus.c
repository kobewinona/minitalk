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

// TODO fix header

static void	handle_error(char *error_message)
{
	ft_putstr_fd(error_message, STDERR_FILENO);
	exit(EXIT_FAILURE);
}

static void	handle_signal_message(int signum, siginfo_t *info, void *context)
{
	static char	c;
	static int	bits;

	(void)context;
	c = c | (signum == SIGUSR2);
	bits++;
	if (bits == 8)
	{
        ft_putchar_fd(c, STDOUT_FILENO);
        if (kill(info->si_pid, SIGUSR1) == ERROR)
            handle_error(UNKNOWN_SERVER_ERR);
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
	sa.sa_flags = SA_SIGINFO;
	sa.sa_sigaction = &handle_signal_message;
    if (sigaction(SIGUSR1, &sa, NULL) == ERROR)
        handle_error(SIGHANDLER_ERR);
    if (sigaction(SIGUSR2, &sa, NULL) == ERROR)
        handle_error(SIGHANDLER_ERR);
    ft_putstr_fd("Server PID: ", STDOUT_FILENO);
    ft_putnbr_fd(server_pid, STDOUT_FILENO);
    ft_putstr_fd(" | ( ᵔ ᵕ ᵔ) ", STDOUT_FILENO);
	while (1)
		pause();
	return (EXIT_SUCCESS);
}
