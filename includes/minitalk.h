/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minitalk.h                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dklimkin <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/23 15:30:29 by dklimkin          #+#    #+#             */
/*   Updated: 2023/11/23 15:30:30 by dklimkin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINITALK_H
# define MINITALK_H
# include "libftprintf.h"
# include <signal.h>

// magic numbers
# define TRUE 1
# define FALSE 0
# define ERROR -1

// error messages
# define ARGS_NOT_PROVIDED_ERR "\nplease provide PID and a string\n\n"
# define INCORRECT_PID_ERR "\nplease provide correct server PID\n\n"
# define SIGHANDLER_ERR "\n\nerror setting signal handler\n\n\n"
# define TRANSMISSON_ERR "\n\nmessage transmission failed ｡°(.◜ᯅ◝)°｡\n\n\n"
# define UNKNOWN_SERVER_ERR "\n\nan unknown error occurred\n\n\n"

# include <unistd.h>
# include <signal.h>
# include <stdlib.h>
# include <sys/types.h>
# include "libft.h"

# define C_ERROR "\n\033[0;91mError !\033[0m"
# define C_ARGS "\033[38;5;214mAdd the server PID and a string or smiley.\033[0m"
# define C_EX_ARGS "\033[0;92mExample : ./client 4242(PID) Hello(Message)\033[0m\n"

# define C_NOTIFICATION "\033[0;90mWaiting for notification...\033[0m\n"

# define S_PID "\033[0;96mMy PID : [%d], parameter for the client.\033[0m\n\n"
# define S_WLC "\n\033[0;94mI print messages sent by the client.\033[0m\n"
# define S_CHEV "\033[0;90m>>\033[0m "

# define NOTIFICATION_R1 "\033[0;91mR\033[38;5;214mE\033[0;93mC\033[0;92mE"
# define NOTIFICATION_R2 "\033[0;96mI\033[0;94mV\033[0;95mE\033[0;97mD\033[0m\n"

# define SA_USR1_FAIL "SIGUSR1 failed\n"
# define SA_USR2_FAIL "SIGUSR2 failed\n"

# define SERV_FAIL_USR1 "SIGUSR1"
# define SERV_FAIL_USR2 "Server failed to send SIGUSR2"

# define UNICODE "\033[0;90m(Undefined with unicode...)\033[0m\n"

typedef struct s_mini
{
    char	*s;
    int		waiting;
}		t_minitalk;

/* *** client.c & bonus *** */

void	convert_and_send(int server_pid, char c);
int		str_isdigit(char *s);

void	signal_handler(int signal);
void	def_sigaction(void);

/* *** server.c & bonus *** */

void	new_handler(int signal, siginfo_t *siginfo, void *vd);

#endif
