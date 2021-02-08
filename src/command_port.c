/*
** command_port.c for command_port in /home/frejimap/Documents/Epitech/PSU/PSU_2015_myftp
** 
** Made by Frejimap
** Login   <remi.pignol@epitech.eu>
** 
** Started on  Mon May 15 19:21:36 2017 Frejimap
** Last update Sun May 21 22:40:48 2017 Frejimap
*/

#include <ctype.h>
#include <unistd.h>
#include <stdlib.h>
#include <string.h>
#include "client.h"
#include "RFC959.h"

int	socket_create(t_ftp *ftp)
{
  if (ftp->data_port)
    close(ftp->data_port);
  if ((ftp->data_port = socket(AF_INET, SOCK_STREAM, 0)) == -1)
    {
      ftp->data_port = 0;
      return (1);
    }
  return (0);
}

static int	valid_port(char * port)
{
  unsigned int	count;
  char		rec;

  count = 0;
  rec = 1;
  while (*port && count != 6)
    {
      if (!isdigit(*port) && *port != ',')
	  return (1);
      if (*port == ',')
	{
	  if (rec)
	    return (1);
	  *port = count != 3 ? '.' : 0;
	  ++count;
	  rec = 1;
	}
      else
	rec = 0;
      ++port;
    }
  return (count != 5 || !isdigit(*(port - 1)));
}

static int	get_port(char *str)
{
  int		port1;
  int		port2;

  if ((port1 = strtol(str, &str, 10)) >= 256)
    return (-1);
  ++str;
  if ((port2 = strtol(str, &str, 10)) >= 256)
    return (-1);
  return (port1 * 256 + port2);
}

static int	do_port(t_ftp *ftp)
{
  short	port;

  ftp->data_addr.sin_family = AF_INET;
  if ((int)(ftp->data_addr.sin_addr.s_addr =
	    inet_addr(ftp->command + sizeof(RFC_PORT))) == -1
      || (port = get_port(ftp->command + strlen(ftp->command) + 1)) == -1)
    return (dprintf(ftp->client->socket.fd, C_550 C_PORT_FAIL CRLF));
  ftp->data_addr.sin_port = htons(port);
  if (socket_create(ftp))
    return (dprintf(ftp->client->socket.fd, C_550 C_SOCKET_FAIL CRLF));
  ftp->is_pasv = FALSE;
  if (connect(ftp->data_port, (t_sockaddr*)&ftp->data_addr,
	      sizeof(t_sockaddr_in)))
    {
      dprintf(ftp->client->socket.fd, C_550 C_CONNECT_FAIL CRLF);
      close(ftp->data_port);
      ftp->data_port = 0;
      return (1);
    }
  else
    return (0);
}

void	command_PORT(t_ftp *ftp)
{
  if (!ftp->user.auth)
    dprintf(ftp->client->socket.fd, C_530 C_NOT_AUTH CRLF);
  else if (ftp->command[sizeof(RFC_PORT) - 1] != ' '
	   || valid_port(ftp->command + sizeof(RFC_PORT)))
    dprintf(ftp->client->socket.fd, C_550 C_INV CRLF);
  else if (!do_port(ftp))
    dprintf(ftp->client->socket.fd, C_200 C_PORT CRLF);
}
