/*
** command_file.c for file in /home/frejimap/Documents/Epitech/PSU/PSU_2015_myftp
** 
** Made by Frejimap
** Login   <remi.pignol@epitech.eu>
** 
** Started on  Sat May 13 22:41:17 2017 Frejimap
** Last update Sat May 20 19:56:24 2017 Frejimap
*/

#include <fcntl.h>
#include <unistd.h>
#include <sys/stat.h>
#include <stdlib.h>
#include <string.h>
#include "command.h"
#include "RFC959.h"
#include "error.h"

void	command_DELE(t_ftp *ftp)
{
  if (!ftp->user.auth)
    dprintf(ftp->client->socket.fd, C_530 C_NOT_AUTH CRLF);
  else if (ftp->command[sizeof(RFC_DELE) - 1] != ' ')
    dprintf(ftp->client->socket.fd, C_550 C_INV CRLF);
  else
    {
      if (!remove(ftp->command + sizeof(RFC_DELE)))
	{
	  printf(MES_FILE_DELE, ftp->user.name,
		 ftp->command + sizeof(RFC_DELE));
	  dprintf(ftp->client->socket.fd, C_250 C_DELE CRLF);
	}
      else
	dprintf(ftp->client->socket.fd, C_550 C_DENIED CRLF);
    }
}

static void	do_retr(t_ftp *ftp)
{
  int		fd;
  int		file;
  struct stat	stat;
  char		*buf;

  if ((fd = get_fd_port(ftp)) == -1
      || (file = open(ftp->command + sizeof(RFC_RETR), O_RDONLY)) == -1
      || fstat(file, &stat) == -1
      || !(buf = malloc(stat.st_size)))
    return ;
  printf(MES_FILE_DL, ftp->user.name,
	 ftp->command + sizeof(RFC_RETR));
  dprintf(ftp->client->socket.fd, C_150 C_RETR_START CRLF,
	  ftp->command + sizeof(RFC_RETR), stat.st_size);
  if (read(file, buf, stat.st_size) != -1
      && write(fd, buf, stat.st_size) == -1)
    warn(E_WRITE);
  close(file);
  free(buf);
  close(fd);
}

void		command_RETR(t_ftp *ftp)
{
  if (!ftp->user.auth)
    dprintf(ftp->client->socket.fd, C_530 C_NOT_AUTH CRLF);
  else if (!ftp->data_port)
    dprintf(ftp->client->socket.fd, C_423 C_NOT_PORT CRLF);
  else if (ftp->command[sizeof(RFC_RETR) - 1] == ' ')
    {
      do_retr(ftp);
      close(ftp->data_port);
      ftp->data_port = 0;
      dprintf(ftp->client->socket.fd, C_226 C_RETR_END CRLF);
    }
  else
    dprintf(ftp->client->socket.fd, C_550 C_INV CRLF);
}

static void	do_stor(t_ftp *ftp)
{
  int		fd;
  int		file;
  size_t	len;
  char		*line;
  FILE		*sock;

  if ((fd = get_fd_port(ftp)) == -1
      || !(sock = fdopen(fd, "r")))
    return ;
  if ((file = open(ftp->command + sizeof(RFC_STOR),
		   O_TRUNC | O_CREAT | O_WRONLY, 0644)) == -1)
    {
      fclose(sock);
      return ;
    }
  printf(MES_FILE_ADD, ftp->user.name,
	 ftp->command + sizeof(RFC_STOR));
  line = NULL;
  while ((getline(&line, &len, sock)) != -1)
    if (write(file, line, strlen(line)) == -1)
      break ;
  free(line);
  close(file);
  fclose(sock);
}

void	command_STOR(t_ftp *ftp)
{
  if (!ftp->user.auth)
    dprintf(ftp->client->socket.fd, C_530 C_NOT_AUTH CRLF);
  else if (!ftp->data_port)
    dprintf(ftp->client->socket.fd, C_423 C_NOT_PORT CRLF);
  else if (ftp->command[sizeof(RFC_STOR) - 1] == ' ')
    {
      dprintf(ftp->client->socket.fd, C_150 C_STOR_START CRLF,
	      ftp->command + sizeof(RFC_STOR));
      do_stor(ftp);
      close(ftp->data_port);
      ftp->data_port = 0;
      dprintf(ftp->client->socket.fd, C_226 C_STOR_END CRLF);
    }
  else
    dprintf(ftp->client->socket.fd, C_550 C_INV CRLF);
}
