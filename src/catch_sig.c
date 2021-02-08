/*
** catch_sig.c for sig in /home/frejimap/Documents/Epitech/PSU/PSU_2015_myftp
** 
** Made by Frejimap
** Login   <remi.pignol@epitech.eu>
** 
** Started on  Fri May 12 15:48:00 2017 Frejimap
** Last update Sat May 20 19:48:22 2017 Frejimap
*/

#include <stdlib.h>
#include <signal.h>
#include "error.h"

static void	catch(int sig)
{
  (void)sig;
  exit(0);
}

int	catch_signal()
{
  if (signal(SIGINT, catch) == SIG_ERR
      || signal(SIGTERM, catch) == SIG_ERR
      || signal(SIGPIPE, catch) == SIG_ERR)
    {
      warn(E_SIGNAL);
      return (1);
    }
  return (0);
}
