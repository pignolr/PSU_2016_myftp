/*
** command_passv.c for passv in /home/frejimap/Documents/Epitech/PSU/PSU_2015_myftp
** 
** Made by Frejimap
** Login   <remi.pignol@epitech.eu>
** 
** Started on  Sat May 20 17:28:34 2017 Frejimap
** Last update Sun May 21 19:08:55 2017 Frejimap
*/

#include "command.h"
#include "RFC959.h"

int		socket_bind(t_ftp * ftp)
{
  unsigned int	len;

  len = sizeof(t_sockaddr_in);
  ftp->data_addr.sin_family = AF_INET;
  ftp->data_addr.sin_addr.s_addr = htonl(INADDR_ANY);
  ftp->data_addr.sin_port = 0;
  if (bind(ftp->data_port, (t_sockaddr*)&ftp->data_addr, len))
    return (1);
  if (getsockname(ftp->data_port, (t_sockaddr*)&ftp->data_addr, &len))
    return (1);
  return (0);
}

void			command_PASV(t_ftp *ftp)
{
  unsigned short	port;

  if (!ftp->user.auth)
    dprintf(ftp->client->socket.fd, C_530 C_NOT_AUTH CRLF);
  else if (socket_create(ftp))
    dprintf(ftp->client->socket.fd, C_550 C_SOCKET_FAIL CRLF);
  else
    {
      ftp->is_pasv = TRUE;
      socket_bind(ftp);
      port = ntohs(ftp->data_addr.sin_port);
      listen(ftp->data_port, 1);
      dprintf(ftp->client->socket.fd, C_227 C_PASSV CRLF,
	      127, 0, 0, 1, port / 256, port % 256);
    }
}
