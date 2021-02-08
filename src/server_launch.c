/*
** server_launch.c for launch in /home/frejimap/Documents/Epitech/PSU/PSU_2015_myftp
** 
** Made by Frejimap
** Login   <remi.pignol@epitech.eu>
** 
** Started on  Fri May 12 15:01:24 2017 Frejimap
** Last update Sat May 20 19:47:52 2017 Frejimap
*/

#include <limits.h>
#include <stdlib.h>
#include <stdio.h>
#include <unistd.h>
#include "server.h"
#include "error.h"

static short	get_port(char *nptr)
{
  char		*endptr;
  long		n;

  n = strtol(nptr, &endptr, 10);
  if ((errno == ERANGE && (n == LONG_MAX || n == LONG_MIN))
      || (errno && !n))
    perror(E_STRTOL);
  else if (endptr == nptr)
    fprintf(stderr, E_DIGITS);
  else if (*endptr)
    fprintf(stderr, E_INV_ARG);
  else
    return ((short)n);
  exit(EXIT_FAILURE);
}

int	server_init(t_server *server, char * const av[])
{
  int	socket_id;

  server->port = get_port(av[1]);
  if (!getcwd(server->path, BUFF_SIZE))
    return (fprintf(stderr, E_PATH));
  server->addr.sin_family = AF_INET;
  server->addr.sin_addr.s_addr = htonl(INADDR_ANY);
  server->addr.sin_port = htons(server->port);
  if ((socket_id = socket(AF_INET, SOCK_STREAM, 0)) == -1)
    {
      warn(E_SOCKET);
      return (1);
    }
  if (set_fd(&server->socket, socket_id))
    return (1);
  return (0);
}

int	server_launch(t_server *server)
{
  if (bind(server->socket.fd,
	   (t_sockaddr*)&server->addr,
	   sizeof(t_sockaddr_in))
      == -1)
    {
      warn(E_BIND);
      return (1);
    }
  if (listen(server->socket.fd, MAX_USR) == -1)
    {
      warn(E_LISTEN);
      return (1);
    }
  return (0);
}
