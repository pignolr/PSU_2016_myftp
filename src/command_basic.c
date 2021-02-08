/*
** basic_command.c for basic in /home/frejimap/Documents/Epitech/PSU/PSU_2015_myftp
** 
** Made by Frejimap
** Login   <remi.pignol@epitech.eu>
** 
** Started on  Sat May 13 18:06:56 2017 Frejimap
** Last update Sun May 21 22:15:11 2017 Frejimap
*/

#include <unistd.h>
#include <stdlib.h>
#include "tab_rfc.h"

void		command_HELP(t_ftp* ftp)
{
  unsigned int	i;

  if (!ftp->user.auth)
    dprintf(ftp->client->socket.fd, C_530 C_NOT_AUTH CRLF);
  else
    {
      i = 0;
      dprintf(ftp->client->socket.fd, C_214 C_HELP1);
      while (g_tab_command[i].code)
	{
	  if (i % 14 == 0)
	    dprintf(ftp->client->socket.fd, CRLF);
	  dprintf(ftp->client->socket.fd, " %s", g_tab_command[i].code);
	  ++i;
	}
      if (i % 14 != 1)
	dprintf(ftp->client->socket.fd, CRLF);
      dprintf(ftp->client->socket.fd, C_214 C_HELP2 CRLF);
    }
}

void	command_NOOP(t_ftp* ftp)
{
  dprintf(ftp->client->socket.fd, C_200 C_OKAY CRLF);
}

void	command_QUIT(t_ftp* ftp)
{
  dprintf(ftp->client->socket.fd, C_221 C_EXIT CRLF);
  exit(EXIT_SUCCESS);
}

void	command_INVALID(t_ftp* ftp)
{
  dprintf(ftp->client->socket.fd, C_500 C_UNKNOWN CRLF);
}
