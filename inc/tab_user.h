/*
** tab_user.h for tab user in /home/frejimap/Documents/Epitech/PSU/PSU_2015_myftp
** 
** Made by Frejimap
** Login   <remi.pignol@epitech.eu>
** 
** Started on  Sat May 13 20:02:57 2017 Frejimap
** Last update Sat May 13 20:05:04 2017 Frejimap
*/

#ifndef TAB_USER__
# define TAB_USER__
# include "client.h"

static const t_user	g_users[] =
  {
    { "Anonymous", "", 0},
    { "ADMIN", "ADMIN", 0},
    { 0, 0, 0 }
  };

#endif /* !TAB_USER__ */
