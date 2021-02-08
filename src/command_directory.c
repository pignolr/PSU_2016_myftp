/*
** command_directory.c for drectory* in /home/frejimap/Documents/Epitech/PSU/PSU_2015_myftp
** 
** Made by Frejimap
** Login   <remi.pignol@epitech.eu>
** 
** Started on  Sat May 13 22:07:25 2017 Frejimap
** Last update Sun May 21 22:21:11 2017 Frejimap
*/

#include <unistd.h>
#include <string.h>
#include "error.h"
#include "client.h"
#include "RFC959.h"

void	command_PWD(t_ftp* ftp)
{
  if (!ftp->user.auth)
    dprintf(ftp->client->socket.fd, C_530 C_NOT_AUTH CRLF);
  else
    dprintf(ftp->client->socket.fd, C_257 " \"%s\" " CRLF, ftp->client->path);
}

void	command_CWD(t_ftp* ftp)
{
  char	path[BUFF_SIZE];

  if (!ftp->user.auth)
    dprintf(ftp->client->socket.fd, C_530 C_NOT_AUTH CRLF);
  else if (ftp->command[sizeof(RFC_CWD) - 1] != ' ')
    dprintf(ftp->client->socket.fd, C_550 C_INV CRLF);
  else
    {
      memset(path, 0 , BUFF_SIZE);
      strncpy(path, ftp->command + sizeof(RFC_CWD),
	      strlen(ftp->command + sizeof(RFC_CWD)));
      if (!path[BUFF_SIZE - 1] && !chdir(path))
	{
	  printf(MES_MOVE, ftp->user.name, path);
	  if (!getcwd(ftp->client->path, BUFF_SIZE))
	    warn(E_GETCWD);
	  dprintf(ftp->client->socket.fd, C_250 C_CWD CRLF);
	}
      else
	dprintf(ftp->client->socket.fd, C_550 C_CWD_FAIL CRLF);
    }
}

void	command_CDUP(t_ftp *ftp)
{
  if (!ftp->user.auth)
    dprintf(ftp->client->socket.fd, C_530 C_NOT_AUTH CRLF);
  else if (!chdir(MOVE_TO_PARENT))
    {
      printf(MES_MOVE_PARENT, ftp->user.name);
      if (!getcwd(ftp->client->path, BUFF_SIZE))
	warn(E_GETCWD);
      dprintf(ftp->client->socket.fd, C_250 C_CWD CRLF);
    }
  else
    dprintf(ftp->client->socket.fd, C_550 C_CWD_FAIL CRLF);
}
