/*
 * Universidade Federal do Rio de Janeiro
 * Escola Politecnica
 * Departamento de Eletronica e de Computacao
 *
 * Prof. Marcelo Luiz Drumond Lanza
 * EEL270 - Computacao II - Turma 2012/2
 * Autor Joao Vitor Ferreira Duarte 
 *     
 * $Author: joao.duarte $
 * $Date: 2013/04/06 18:55:09 $
 * $Log: thcRemoveUserCgi.c,v $
 * Revision 1.1  2013/04/06 18:55:09  joao.duarte
 * Initial revision
 *
 *
 *
 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "thcFunctions.h"
#include "thcConst.h"
#include "thcError.h"
#include "thcTypes.h"
#include "thcEditUserName.h"
#include "thcRenewCookie.h"
#include "thcRemoveUser.h"

#include "mlcgi.h"

char *mensages[][2]=
{
	{"User wasn't removed","Usuário nao foi removido"},
	{"User removed","Usuário removido"},	
};

int main (int argc, char **argv)
{
	environmentType enviro;
	thcErrorType errorCode;
	thcLanguageType language;
	char nickname[THC_NICKNAME_MAXIMUM_LENGHT+1];
	char cookieName [THC_COOKIE_NAME_LENGHT + 1];
	char confirm [THC_CONFIRM_FORM_NAME_LENGHT + 1];

	if (mlCgiInitialize (&enviro))
		exit (THC_OK);

	if (enviro == commandLine)
	{
		thcGetTextErrorMessage(language,THC_ERROR_INVALID_INTERFACE);
		mlCgiFreeResources();
		exit (THC_OK);
	}

	/* programa executado via web */
	mlCgiBeginHttpHeader ("text/html");
	/* mlCgiBeginHttpHeader (NULL); */
	

	errorCode = mlCgiGetFormStringNoNewLines ("thcNickname", nickname, THC_NICKNAME_MAXIMUM_LENGHT);
	if (errorCode != ML_CGI_OK)
	{
		mlCgiEndHttpHeader();
		thcGetHtmlErrorMessage(language,THC_ERROR_ON_WEB_FORM);
		mlCgiFreeResources();
		exit(THC_OK);
	}
	
	errorCode = mlCgiGetFormStringNoNewLines ("thcCookieName", cookieName, THC_COOKIE_NAME_LENGHT);
	if (errorCode != ML_CGI_OK)
	{
		mlCgiEndHttpHeader();
		thcGetHtmlErrorMessage(language,THC_ERROR_ON_WEB_FORM);
		mlCgiFreeResources();
		exit(THC_OK);
	}
	
	errorCode = mlCgiGetFormStringNoNewLines ("thcConfirm", confirm, THC_CONFIRM_FORM_NAME_LENGHT);
	if (errorCode != ML_CGI_OK)
	{
		mlCgiEndHttpHeader();
		thcGetHtmlErrorMessage(language,THC_ERROR_ON_WEB_FORM);
		mlCgiFreeResources();
		exit(THC_OK);
	}
	
	errorCode = thcRenewCookie(cookieName, &language);
	mlCgiEndHttpHeader();
	if (errorCode != THC_OK)
	{
		thcGetHtmlErrorMessage(language,errorCode);
		mlCgiFreeResources();
		exit(THC_OK);
	}
	
	
	if (strcmp(confirm,"yes") != 0)
	{
		thcWebShowHeader();
		printf("<body>                          \n");
		printf("<div class='content'>           \n");
		printf(" %s                             \n",mensages[0][language]);
		printf("</div>                          \n");	
		thcWebShowFooter();
		return THC_OK;
	}
	
	thcRemoveUser(nickname);
	
	thcWebShowHeader();
	
	printf("<body>                                         \n");
	printf("<div class='content'>                          \n");
	printf("%s<br>                                         \n",mensages[1][language]);
	printf("</div>                                         \n");

	thcWebShowFooter();

	mlCgiFreeResources();
	return THC_OK;
}

/*$RCSfile: thcRemoveUserCgi.c,v $*/
