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
# include "libft.h"
# include <signal.h>
# include <stdio.h>

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

#endif
