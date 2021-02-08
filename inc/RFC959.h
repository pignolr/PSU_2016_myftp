/*
** RFC959.h for RFC in /home/frejimap/Documents/Epitech/PSU/PSU_2015_myftp
** 
** Made by Frejimap
** Login   <remi.pignol@epitech.eu>
** 
** Started on  Sat May 13 16:22:09 2017 Frejimap
** Last update Sun May 21 22:17:24 2017 Frejimap
*/

#ifndef RFC959_H__
# define RFC959_H__

/*
** Command
*/
# define NOTHING ""
# define RFC_USER "USER"
# define RFC_PASS "PASS"
# define RFC_CWD "CWD"
# define RFC_CDUP "CDUP"
# define RFC_QUIT "QUIT"
# define RFC_DELE "DELE"
# define RFC_PWD "PWD"
# define RFC_PASV "PASV"
# define RFC_PORT "PORT"
# define RFC_HELP "HELP"
# define RFC_NOOP "NOOP"
# define RFC_RETR "RETR"
# define RFC_STOR "STOR"
# define RFC_LIST "LIST"
# define RFC_INVALID 0

/*
** Code response
*/
# define C_150 "150"
# define C_200 "200"
# define C_214 "214"
# define C_220 "220"
# define C_221 "221"
# define C_226 "226"
# define C_227 "227"
# define C_230 "230"
# define C_250 "250"
# define C_257 "257"
# define C_331 "331"
# define C_332 "332"
# define C_423 "423"
# define C_500 "500"
# define C_503 "503"
# define C_530 "530"
# define C_550 "550"

/*
** Message code
*/
# define C_START " Service ready for new user."
# define C_EXIT " Service closing control connection."
# define C_LOGOUT " Logged out."

# define C_LOGIN " User logged in, proceed."
# define C_NEED_PASS " User name okay, need password."
# define C_NEED_USER " Need account for login."

# define C_INV " Command is invalid."
# define C_LOGIN_FAIL " User can't be logged in."
# define C_ALREADY_LOGIN " User Already logged in."
# define C_GUEST_LOGIN " Can't change from guest user."
# define C_OKAY " Command okay."
# define C_PASSV " Entering Passive Mode (%d,%d,%d,%d,%d,%d)."
# define C_PORT " Entering Port Mode"
# define C_CWD " Directory successfully changed."
# define C_CWD_FAIL " Failed to change directory."
# define C_NOT_USER " Login with USER first."
# define C_NOT_AUTH " Please login with USER and PASS."
# define C_NOT_PORT " Use PORT or PASV first."
# define C_PORT_FAIL " Creation port fail."
# define C_SOCKET_FAIL " Creation socket fail."
# define C_CONNECT_FAIL " Connection to port fail."
# define C_HELP1 " The following commands are recognized."
# define C_HELP2 " Help Ok."
# define C_UNKNOWN " Unknown command."
# define C_DENIED " Permission denied."
# define C_DELE " File successfully remove"
# define C_LIST_START " Here comes the directory listing."
# define C_LIST_END " Directory send OK."
# define C_RETR_START " Opening ASCII mode data connection for %s (%lu bytes)."
# define C_RETR_END " Transfer complete."
# define C_STOR_START " Opening ASCII mode data connection for %s."
# define C_STOR_END " Transfer complete."
/*
** End Message Code
*/

/*
** end of line
*/
# define CRLF "\r\n"

/*
** cwd command
*/
# define THIS_DIR "."
# define MOVE_TO_PARENT ".."

#endif /* !RFC959_H__ */
