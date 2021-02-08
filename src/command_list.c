/*
** command_list.c for command_list in /home/frejimap/Documents/Epitech/PSU/PSU_2015_myftp
** 
** Made by Frejimap
** Login   <remi.pignol@epitech.eu>
** 
** Started on  Wed May 17 18:47:27 2017 Frejimap
** Last update Sat May 20 19:56:59 2017 Frejimap
*/

#include <dirent.h>
#include <unistd.h>
#include "command.h"
#include "RFC959.h"

int		get_fd_port(t_ftp *ftp)
{
  unsigned int	len;

  len = sizeof(t_sockaddr_in);
  if (ftp->is_pasv)
    return (accept(ftp->data_port, (t_sockaddr*)&ftp->data_addr, &len));
  else
    return (ftp->data_port);
}

static void	do_list(t_ftp *ftp)
{
  int		fd;
  DIR		*dir;
  struct dirent	*file;
  char		*path;

  path = ftp->command[sizeof(RFC_LIST) - 1] != ' ' ?
    THIS_DIR : ftp->command + sizeof(RFC_LIST);
  if ((fd = get_fd_port(ftp)) == -1)
    return ;
  if ((dir = opendir(path)))
    while ((file = readdir(dir)))
      if (file->d_name[0] != '.')
	dprintf(fd, "%s\n", file->d_name);
  closedir(dir);
  close(fd);
}

void	command_LIST(t_ftp *ftp)
{
  if (!ftp->user.auth)
    dprintf(ftp->client->socket.fd, C_530 C_NOT_AUTH CRLF);
  else if (!ftp->data_port)
    dprintf(ftp->client->socket.fd, C_423 C_NOT_PORT CRLF);
  else
    {
      dprintf(ftp->client->socket.fd, C_150 C_LIST_START CRLF);
      do_list(ftp);
      close(ftp->data_port);
      ftp->data_port = 0;
      dprintf(ftp->client->socket.fd, C_226 C_LIST_END CRLF);
    }
}
