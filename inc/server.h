/*
** server.h for server in /home/frejimap/Documents/Epitech/PSU/PSU_2015_myftp
** 
** Made by Frejimap
** Login   <remi.pignol@epitech.eu>
** 
** Started on  Fri May 12 11:58:01 2017 Frejimap
** Last update Wed May 17 15:33:49 2017 Frejimap
*/

#ifndef SERVER_H__
# define SERVER_H__
# include "t_fd.h"
# include "typedef.h"

# define BUFF_SIZE 512
# define MAX_USR 48
# define USAGE "Usage : %s port path\n"
# define HELP "-h"

typedef struct	s_server
{
  char		path[BUFF_SIZE];
  t_fd		socket;
  t_sockaddr_in	addr;
  short		port;
}		t_server;

int	server_init(t_server *info, char * const av[]);
int	server_launch(t_server *info);
void	server_loop(t_server *info);
int	catch_signal(void);

#endif  /* !SERVER_H__ */
