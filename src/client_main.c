/*
** client_main.c for client main in /home/frejimap/Documents/Epitech/PSU/PSU_2015_myftp
** 
** Made by Frejimap
** Login   <remi.pignol@epitech.eu>
** 
** Started on  Sat May 13 17:06:27 2017 Frejimap
** Last update Sun May 21 22:31:17 2017 Frejimap
*/

#include <unistd.h>
#include <stdlib.h>
#include <string.h>
#include "tab_rfc.h"
#include "error.h"

char		*get_command(FILE *read_stream, char **command)
{
  size_t	len;
  size_t	i;

  len = 0;
  if (getline(command, &len, read_stream) == -1)
    {
      if (errno)
	err(EXIT_FAILURE, E_GETLINE);
      else
	return (NULL);
    }
  i = 0;
  while ((*command)[i] && i < len)
    if ((*command)[i] == '\n' || (*command)[i] == '\r')
      break;
    else
      ++i;
  (*command)[i] = 0;
  return (*command);
}

void		do_command(t_ftp *ftp)
{
  unsigned int	i;

  i = 0;
  while (g_tab_command[i].code != RFC_INVALID
	 && (g_tab_command[i].len > strlen(ftp->command)
	     || strncasecmp(ftp->command,
			    g_tab_command[i].code,
			    g_tab_command[i].len)))
    ++i;
  g_tab_command[i].func(ftp);
}

void	client_init_stream(t_ftp *ftp)
{
  if (!(ftp->read = fdopen(ftp->client->socket.fd, "r")))
    err(EXIT_FAILURE, E_FDOPEN);
  if (fflush(stdout))
    warn(E_FFLUSH);
}

void	free_ftp(int stat, void *data)
{
  t_ftp	*ftp;

  (void)stat;
  ftp = data;
  if (ftp->user.auth)
    printf(MES_LOGOUT , ftp->user.name);
  printf(MES_DISCONNECT);
  free(ftp->command);
  free(ftp->user.name);
  free(ftp->user.pass);
  if (ftp->data_port)
    close(ftp->data_port);
  fclose(ftp->read);
  ftp->client->socket.set = FALSE;
}

void	client_main(t_ftp *ftp)
{
  printf(MES_CONNECT);
  client_init_stream(ftp);
  dprintf(ftp->client->socket.fd, C_220 C_START CRLF);
  on_exit(free_ftp, ftp);
  while (get_command(ftp->read, &ftp->command))
    {
      if (strcmp(ftp->command, NOTHING))
	do_command(ftp);
      free(ftp->command);
      ftp->command = NULL;
    }
}
