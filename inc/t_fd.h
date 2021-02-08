/*
** t_fd.h for t_fd in /home/frejimap/Documents/Epitech/PSU/PSU_2015_myftp
** 
** Made by Frejimap
** Login   <remi.pignol@epitech.eu>
** 
** Started on  Fri May 12 11:54:44 2017 Frejimap
** Last update Fri May 12 15:16:27 2017 Frejimap
*/

#ifndef T_FD_H__
# define T_FD_H__
# include "bool.h"

typedef struct	s_fd
{
  int		fd;
  t_bool	set;
}		t_fd;

int	set_fd(t_fd*, int);
int	unset_fd(t_fd*);

#endif /* !T_FD_H__ */
