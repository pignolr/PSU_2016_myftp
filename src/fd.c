/*
** fd.c for fd in /home/frejimap/Documents/Epitech/PSU/PSU_2015_myftp
** 
** Made by Frejimap
** Login   <remi.pignol@epitech.eu>
** 
** Started on  Fri May 12 14:41:01 2017 Frejimap
** Last update Sat May 20 19:46:56 2017 Frejimap
*/

#include <unistd.h>
#include <stdlib.h>
#include "t_fd.h"
#include "error.h"

int	unset_fd(t_fd* ptr)
{
  if (ptr->set == TRUE)
    {
      ptr->set = FALSE;
      if (close(ptr->fd) == -1)
	{
	  warn(E_CLOSE);
	  return (-1);
	}
      else
	return (0);
    }
  return (0);
}

void	auto_unset(int err, void *ptr)
{
  (void)err;
  unset_fd(ptr);
}

int	set_fd(t_fd* ptr, int fd)
{
  ptr->fd = fd;
  ptr->set = TRUE;
  if (on_exit(auto_unset, ptr))
    {
      warn(E_ON_EXIT);
      return (1);
    }
  else
    return (0);
}
