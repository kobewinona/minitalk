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

static int	g_is_char_received;

static void	handle_error(char *error_message)
{
	ft_putstr_fd(error_message, STDERR_FILENO);
	exit(EXIT_FAILURE);
}

static void	handle_signal_acknowledgement(int signum)
{
	if (signum == SIGUSR1)
        g_is_char_received = TRUE;
}

static void	send_character(int server_pid, char c, int delay)
{
	int	bits;

	bits = 7;
	while (bits >= 0)
	{
		if ((c >> bits) & 1)
		{
			if (kill(server_pid, SIGUSR2) == ERROR)
				handle_error(TRANSMISSON_ERR);
		}
		else
		{
			if (kill(server_pid, SIGUSR1) == ERROR)
				handle_error(TRANSMISSON_ERR);
		}
		usleep(delay);
		bits--;
	}
}

static void	send_message(int server_pid, char *message)
{
	int		i;
    int     tries;
    int     delay;

	i = 0;
    tries = 0;
    delay = 40;
	while (message[i] != '\0')
	{
		send_character(server_pid, message[i], delay);
        usleep(delay);
        if (g_is_char_received == TRUE)
        {
            g_is_char_received = FALSE;
            i++;
        }
        else
        {
            tries++;
            delay += 10;
            if (tries >= 50)
                handle_error(TRANSMISSON_ERR);
        }
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
    sigemptyset(&sa.sa_mask);
    sa.sa_flags = SA_SIGINFO;
    sa.sa_handler = &handle_signal_acknowledgement;
	if (!server_pid)
		handle_error(INCORRECT_PID_ERR);
	if (sigaction(SIGUSR1, &sa, NULL) == ERROR)
		handle_error(SIGHANDLER_ERR);
	if (sigaction(SIGUSR2, &sa, NULL) == ERROR)
		handle_error(SIGHANDLER_ERR);
	send_message(server_pid, argv[2]);
	while (1)
        pause();
	return (EXIT_SUCCESS);
}
