/*
** tab_rfc.h for tab rfc in /home/frejimap/Documents/Epitech/PSU/PSU_2015_myftp
** 
** Made by Frejimap
** Login   <remi.pignol@epitech.eu>
** 
** Started on  Sat May 13 16:28:10 2017 Frejimap
** Last update Sat May 20 17:32:19 2017 Frejimap
*/

#ifndef TAB_RFC__
# define TAB_RFC__
# include "client.h"
# include "RFC959.h"
# include "command.h"

typedef struct	s_ptr_rfcfunc
{
  const char*	code;
  unsigned int	len;
  void		(*func)(t_ftp*);
}		t_ptr_rfcfunc;

static const t_ptr_rfcfunc	g_tab_command[] =
  {
    { RFC_USER, sizeof(RFC_USER) - 1, command_USER },
    { RFC_PASS, sizeof(RFC_PASS) - 1, command_PASS },
    { RFC_CWD, sizeof(RFC_CWD) - 1, command_CWD },
    { RFC_CDUP, sizeof(RFC_CDUP) - 1, command_CDUP },
    { RFC_QUIT, sizeof(RFC_QUIT) - 1, command_QUIT },
    { RFC_DELE, sizeof(RFC_DELE) - 1, command_DELE },
    { RFC_PWD, sizeof(RFC_PWD) - 1, command_PWD },
    { RFC_PASV, sizeof(RFC_PASV) - 1, command_PASV },
    { RFC_PORT, sizeof(RFC_PORT) - 1, command_PORT },
    { RFC_HELP, sizeof(RFC_HELP) - 1, command_HELP },
    { RFC_NOOP, sizeof(RFC_NOOP) - 1, command_NOOP },
    { RFC_RETR, sizeof(RFC_RETR) - 1, command_RETR },
    { RFC_STOR, sizeof(RFC_STOR) - 1, command_STOR },
    { RFC_LIST, sizeof(RFC_LIST) - 1, command_LIST },
    { RFC_INVALID, sizeof(RFC_INVALID), command_INVALID }
  };

#endif
