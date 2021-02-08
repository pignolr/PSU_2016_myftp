/*
** client.h for client in /home/frejimap/Documents/Epitech/PSU/PSU_2015_myftp
** 
** Made by Frejimap
** Login   <remi.pignol@epitech.eu>
** 
** Started on  Fri May 12 16:52:21 2017 Frejimap
** Last update Sun May 21 22:21:54 2017 Frejimap
*/

#ifndef CLIENT_H__
# define CLIENT_H__
# include <stdio.h>
# include "server.h"
# include "t_fd.h"

typedef t_server	t_client;

typedef struct	s_user
{
  char		*name;
  char		*pass;
  int		auth;
}		t_user;

typedef struct	s_ftp
{
  t_server	*server;
  t_client	*client;
  FILE		*read;
  char		*command;
  t_user	user;
  t_sockaddr_in	data_addr;
  int		data_port;
  int		is_pasv;
}		t_ftp;

void	client_main(t_ftp*);

# define MES_READY "[+] Server is ready.\n"
# define MES_CONNECT "[+] A client connected.\n"
# define MES_DISCONNECT "[+] A client disconnected.\n"
# define MES_LOGIN "[+] User '%s' logged in.\n"
# define MES_LOGOUT "[+] User '%s' logged out.\n"
# define MES_FILE_DELE "[+] User '%s' deleted file: '%s'.\n"
# define MES_FILE_ADD "[+] User '%s' uploaded file: '%s'.\n"
# define MES_FILE_DL "[+] User '%s' download file: '%s'.\n"
# define MES_MOVE_PARENT "[+] User '%s' move to parent directory.\n"
# define MES_MOVE "[+] User '%s' move to '%s'.\n"

#endif /* !CLIENT_H__ */
