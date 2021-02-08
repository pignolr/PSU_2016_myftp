/*
** error.h for error in /home/frejimap/Documents/Epitech/PSU/PSU_2015_myftp
** 
** Made by Frejimap
** Login   <remi.pignol@epitech.eu>
** 
** Started on  Fri May 12 15:11:04 2017 Frejimap
** Last update Sat May 20 19:33:04 2017 Frejimap
*/

#ifndef ERROR_H__
# define ERROR_H__
# include <errno.h>
# include <err.h>

# define E_PATH "path is too long"
# define E_GETCWD "getcwd"
# define E_CHDIR "chdir"
# define E_CLOSE "close"
# define E_LISTEN "listen"
# define E_BIND "bind"
# define E_SOCKET "socket"
# define E_STRTOL "strtol"
# define E_DIGITS "No digits were found\n"
# define E_INV_ARG "Invalid argument\n"
# define E_ON_EXIT "on_exit"
# define E_SIGNAL "signal"
# define E_ACCEPT "accept"
# define E_FORK "fork"
# define E_READ "read"
# define E_DUP2 "dup2"
# define E_FFLUSH "fflush"
# define E_GETLINE "getline"
# define E_FDOPEN "fdopen"
# define E_WRITE "write"

#endif /* !ERROR_H__ */
