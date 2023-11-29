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
# define ARGS_NOT_PROVIDED_ERR "please provide PID and a string\n"
# define INCORRECT_PID_ERR "please provide correct server PID\n"
# define SIGHANDLER_ERR "Error setting signal handler"
# define TRANSMISSON_ERR "\n\nmessage transmission failed ｡°(.◜ᯅ◝)°｡\n\n\n"
# define UNKNOWN_SERVER_ERR "an unknown error occured"

#endif
