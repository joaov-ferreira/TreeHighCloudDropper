/*
 * Universidade Federal do Rio de Janeiro
 * Escola Politecnica
 * Departamento de Eletronica e de Computacao
 * Prof. Marcelo Luiz Drumond Lanza
 *
 * File:                sendmail.h
 * Author:              Marcelo Luiz Drumond Lanza
 * 
 * $Date: 2013/03/20 23:05:16 $
 * $Log: sendmail.h,v $
 *
 * Revision 1.1  2007/12/06 00:13:15  lanza
 * Initial revision
 *
 *
 */

#ifndef __SENDMAIL__
#define __SENDMAIL__ "@(#)sendmail.h $Revision: 1.1 $"

#define SENDMAIL_OK				0
#define INVALID_SMTP_SERVER_ADDRESS		1
#define INVALID_FROM				2
#define INVALID_TO				3
#define INVALID_CC				4
#define INVALID_BCC				5
#define INVALID_BODY				6
#define SOCKET_ERROR				7
#define CONNECT_ERROR				8
#define RECV_ERROR				9
#define SMTP_SERVER_ERROR			10
#define INVALID_CHARACTER			11
#define INVALID_CLIENT_DOMAIN			12

/*
 *
 * Arguments:
 *	char * - client domain (p.ex. "del.ufrj.br").
 *	char * - SMTP server ip address (p.ex. "smtp.del.ufrj.br").
 *	unsigned - SMTP server port (p. ex. 25).
 *	char * - from
 *	char * - to
 *	char * - cc
 *	char * - bcc
 * 	char * - subject
 *	char * - body
 * 	char * - attachment
 */
unsigned sendMail (char *, char *, unsigned, char *, char *, char *, char *, char *, char *, char *); 

#endif

/* $RCSfile: sendmail.h,v $ */
