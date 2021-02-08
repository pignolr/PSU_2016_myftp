/*
** server_loop.c for serveur loop in /home/frejimap/Documents/Epitech/PSU/PSU_2015_myftp
** 
** Made by Frejimap
** Login   <remi.pignol@epitech.eu>
** 
** Started on  Fri May 12 15:57:53 2017 Frejimap
** Last update Sun May 21 22:41:03 2017 Frejimap
*/

#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include "client.h"
#include "error.h"

static void	client_fork(t_ftp *ftp, int fd)
{
  if (fork())
    {
      if (errno)
	warn(E_FORK);
      return ;
    }
  unset_fd(&ftp->server->socket);
  if (set_fd(&ftp->client->socket, fd))
    exit(EXIT_FAILURE);
  client_main(ftp);
  exit(EXIT_SUCCESS);
}

void		server_loop(t_server *server)
{
  unsigned int	len;
  t_client	client;
  t_ftp		ftp;
  int		fd;

  len = sizeof(t_sockaddr_in);
  memset(&client, 0, sizeof(t_client));
  memset(&ftp, 0, sizeof(t_ftp));
  strcpy(client.path, server->path);
  ftp.client = &client;
  ftp.server = server;
  printf(MES_READY);
  while (1)
    {
      if ((fd = accept(ftp.server->socket.fd,
		       (t_sockaddr*)&ftp.client->addr,
		       &len)) == -1)
	warn(E_ACCEPT);
      else
	{
	  client_fork(&ftp, fd);
	  if (close(fd) == -1)
	    warn(E_CLOSE);
	}
    }
}
