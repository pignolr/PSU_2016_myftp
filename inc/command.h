/*
** command.h for command in /home/frejimap/Documents/Epitech/PSU/PSU_2015_myftp
** 
** Made by Frejimap
** Login   <remi.pignol@epitech.eu>
** 
** Started on  Sat May 13 17:35:31 2017 Frejimap
** Last update Sat May 20 18:19:23 2017 Frejimap
*/

#ifndef COMMAND_H__
# define COMMAND_H__
# include "client.h"

int	get_fd_port(t_ftp*);
int	socket_create(t_ftp*);
void	command_USER(t_ftp*);
void	command_PASS(t_ftp*);
void	command_CWD(t_ftp*);
void	command_CDUP(t_ftp*);
void	command_QUIT(t_ftp*);
void	command_DELE(t_ftp*);
void	command_PWD(t_ftp*);
void	command_PASV(t_ftp*);
void	command_PORT(t_ftp*);
void	command_HELP(t_ftp*);
void	command_NOOP(t_ftp*);
void	command_RETR(t_ftp*);
void	command_STOR(t_ftp*);
void	command_LIST(t_ftp*);
void	command_INVALID(t_ftp*);

#endif /* !COMMAND_H__ */
