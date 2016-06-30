/*
 * Universidade Federal do Rio de Janeiro
 * Escola Politecnica
 * Departamento de Eletronica e de Computacao
 *
 * Prof. Marcelo Luiz Drumond Lanza
 * EEL310 - Computacao II - Turma 3112/2
 *
 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "thcFunctions.h"
#include "thcConst.h"
#include "thcError.h"
#include "thcTypes.h"
#include "thcAddUser.h"
#include "thcConfig.h"

#include "mlcgi.h"

char *homepage[][2]=
{
	{"function not implemented","função nao implementada"},
};


int main (int argc, char **argv)
{
	thcUserDataType data;
	environmentType enviro;
	thcErrorType errorCode;
	thcLanguageType language = THC_DEFAULT_LANGUAGE;
	time_t localTime;
	char nickname[THC_NICKNAME_MAXIMUM_LENGHT+1];
	char cookieName [THC_COOKIE_NAME_LENGHT + 1];
	char cookieContent [THC_COOKIE_CONTENT_LENGHT + 1];

	if (mlCgiInitialize (&enviro))
		exit (THC_OK);

	if (enviro == commandLine)
	{
		thcGetTextErrorMessage(language,THC_ERROR_INVALID_INTERFACE);
		mlCgiFreeResources();
		exit (THC_OK);
	}
	
	/*Start header*/
	mlCgiBeginHttpHeader("text/html");
	
	/*Get nickname*/
	errorCode = mlCgiGetFormStringNoNewLines ("thcNickname",nickname,THC_NICKNAME_MAXIMUM_LENGHT);
	if (errorCode != ML_CGI_OK)
	{
		mlCgiEndHttpHeader();
		thcGetHtmlErrorMessage(language, THC_ERROR_ON_WEB_FORM);
		mlCgiFreeResources();
		exit(THC_OK);
	}
	
	/*Get the cookie name*/
	errorCode = thcSearchUser(nickname,&data);
	if (errorCode != THC_OK)
	{
		mlCgiEndHttpHeader ();
		thcGetHtmlErrorMessage(language, errorCode);
		mlCgiFreeResources();
		exit(THC_OK);
	}

	if (sprintf(cookieName,THC_COOKIE_NAME_PRINTF_FORMAT,data.UID) != THC_COOKIE_NAME_LENGHT)
	{
		mlCgiEndHttpHeader ();
		thcGetHtmlErrorMessage(language,THC_ERROR_GENERATING_COOKIE_NAME);
		exit(THC_OK);			
	}	
	
	/*Send cookie with expiration time 0*/
	mlCgiGetSpecificCookie (cookieName,THC_NICKNAME_MAXIMUM_LENGHT,cookieContent,THC_COOKIE_CONTENT_LENGHT);
	mlCgiSetCookie(cookieName,cookieContent,0,NULL,NULL,NULL);
	mlCgiEndHttpHeader();
	
	localTime = time(NULL);
	thcGenerateCookie(cookieName, &localTime, cookieContent, THC_DEFAULT_COOKIE_IP);	
	
	printf("<head>       \n");
	if (cookieContent[0] == 'e')
		printf("<meta HTTP-EQUIV='REFRESH' content='0; url=%s'>  ",THC_WEB_SERVER_URL);
	if (cookieContent[0] == 'b')
		printf("<meta HTTP-EQUIV='REFRESH' content='0; url=%s'>  ",THC_WEB_SERVER_URL_BR);
	printf("</head>      \n");
	

	mlCgiFreeResources();
	return THC_OK;
}