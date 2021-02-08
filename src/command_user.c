/*
** command_user.c for user in /home/frejimap/Documents/Epitech/PSU/PSU_2015_myftp
** 
** Made by Frejimap
** Login   <remi.pignol@epitech.eu>
** 
** Started on  Sat May 13 19:47:08 2017 Frejimap
** Last update Sun May 21 22:02:19 2017 Frejimap
*/

#include <unistd.h>
#include <stdlib.h>
#include <string.h>
#include "tab_user.h"
#include "RFC959.h"

int	user_connect(t_user *user)
{
  unsigned int	i;

  i = 0;
  while (g_users[i].name && strcmp(user->name, g_users[i].name))
    ++i;
  if (g_users[i].name && !strcmp(user->pass, g_users[i].pass))
    {
      printf(MES_LOGIN, user->name);
      user->auth = TRUE;
      return (0);
    }
  else
    return (1);
}

void	command_USER(t_ftp* ftp)
{
  if (ftp->command[sizeof(RFC_USER) - 1] != ' ')
    dprintf(ftp->client->socket.fd, C_530 C_INV CRLF);
  else if (ftp->user.auth)
    dprintf(ftp->client->socket.fd, C_530 C_GUEST_LOGIN CRLF);
  else
    {
      if (ftp->user.name)
	{
	  free(ftp->user.name);
	  free(ftp->user.pass);
	  ftp->user.pass = NULL;
	}
      ftp->user.name =
	strndup(ftp->command + sizeof(RFC_USER),
		strlen(ftp->command + sizeof(RFC_USER)));
      ftp->user.auth = FALSE;
      if (!ftp->user.pass)
	dprintf(ftp->client->socket.fd, C_331 C_NEED_PASS CRLF);
    }
}

void	command_PASS(t_ftp* ftp)
{
  if (!ftp->user.name)
    dprintf(ftp->client->socket.fd, C_503 C_NOT_USER CRLF);
  else if (ftp->user.auth)
    dprintf(ftp->client->socket.fd, C_230 C_ALREADY_LOGIN CRLF);
  else
    {
      free(ftp->user.pass);
      ftp->user.pass = ftp->command[sizeof(RFC_PASS) - 1] != ' ' ?
	strndup(ftp->command + sizeof(RFC_PASS),
		strlen(ftp->command + sizeof(RFC_USER))) :
	strndup(NOTHING, 1);
      ftp->user.auth = FALSE;
      if (user_connect(&ftp->user))
	{
	  free(ftp->user.name);
	  free(ftp->user.pass);
	  ftp->user.name = NULL;
	  ftp->user.pass = NULL;
	  dprintf(ftp->client->socket.fd, C_530 C_LOGIN_FAIL CRLF);
	}
      else
	dprintf(ftp->client->socket.fd, C_230 C_LOGIN CRLF);
    }
}
