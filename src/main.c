/*
** main.c for main in /home/frejimap/Documents/Epitech/PSU/PSU_2015_myftp
** 
** Made by Frejimap
** Login   <remi.pignol@epitech.eu>
** 
** Started on  Fri May 12 14:12:25 2017 Frejimap
** Last update Sat May 20 19:47:21 2017 Frejimap
*/

#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <unistd.h>
#include "server.h"
#include "error.h"

static void	usage(const char *name)
{
  printf(USAGE, name);
}

int	move_path(const char *path)
{
  if (chdir(path))
    {
      warn(E_CHDIR);
      return (1);
    }
  return (0);
}

static int	server_main(char * const av[], t_server *server)
{
  memset(server, 0, sizeof(t_server));
  if (move_path(av[2])
      || catch_signal()
      || server_init(server, av)
      || server_launch(server))
    return (1);
  server_loop(server);
  return (0);
}

int		main(int ac, char * const av[])
{
  t_server	server_info;

  if (ac == 2 && !strcmp(av[1], HELP))
    usage(av[0]);
  else if (ac != 3)
    {
      usage(av[0]);
      return (EXIT_FAILURE);
    }
  else if (server_main(av, &server_info))
    return (EXIT_FAILURE);
  else
    return (EXIT_SUCCESS);
}
