/*
 * Universidade Federal do Rio de Janeiro
 * Escola Politecnica
 * Departamento de Eletronica e de Computacao
 *
 * Prof. Marcelo Luiz Drumond Lanza
 * EEL310 - Computacao II - Turma 3112/2
 *
 *
 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "mlcgi.h"
#include "thcTypes.h"
#include "thcFunctions.h"
#include "thcError.h"
#include "thcConfig.h"
#include "thcAddUserToGroup.h" 



char *menssage [][2]=
{
	{"Successfully added to the group","Grupo adicionado com sucesso"}
	
};

int main (int argc, char **argv)
{
	environmentType enviro;
	char nickname[THC_NICKNAME_MAXIMUM_LENGHT+1];
	char groupString [THC_MAXIMUM_GROUP_NAME + 1];
	thcGroupType group;
	thcErrorType errorCode;
	char cookieName [THC_COOKIE_NAME_LENGHT + 1];
	thcLanguageType language = THC_DEFAULT_LANGUAGE;
	

	/*Initiate and check environment*/
	if (mlCgiInitialize (&enviro))
		exit (THC_OK);

	if (enviro == commandLine)
	{
		thcGetTextErrorMessage(language,THC_ERROR_INVALID_INTERFACE);
		mlCgiFreeResources();
		exit (THC_OK);
	}
	

	/*Web interface*/
	mlCgiBeginHttpHeader ("text/html");
	
	errorCode = mlCgiGetFormStringNoNewLines ("thcCookieName",cookieName,THC_COOKIE_NAME_LENGHT);
	if (errorCode == ML_CGI_OK)
	{
		mlCgiEndHttpHeader();
		thcGetHtmlErrorMessage(language, THC_ERROR_ON_WEB_FORM);
		mlCgiFreeResources ();	
		exit(THC_OK);
	}
	
	errorCode = mlCgiGetFormStringNoNewLines ("thcNickname", nickname , THC_NICKNAME_MAXIMUM_LENGHT);
	if (errorCode != ML_CGI_OK)
	{
		mlCgiEndHttpHeader();
		thcGetHtmlErrorMessage(language, THC_ERROR_ON_WEB_FORM);
		mlCgiFreeResources ();	
		exit(THC_OK);
	}
	
	
	errorCode = mlCgiGetFormStringNoNewLines ("thcGroup", groupString, THC_MAXIMUM_GROUP_NAME);
	if (errorCode != ML_CGI_OK)
	{
		mlCgiEndHttpHeader();
		thcGetHtmlErrorMessage(language, THC_ERROR_ON_WEB_FORM);
		mlCgiFreeResources ();	
		exit(THC_OK);		
	}
	
	errorCode = thcRenewCookie (cookieName, &language);
	if (errorCode != THC_OK)
	{
		mlCgiEndHttpHeader();
		thcGetHtmlErrorMessage(language, errorCode);
		mlCgiFreeResources ();	
		exit(THC_OK);		
	}
	
	mlCgiEndHttpHeader();
	
	if (groupString[0] == 'a') group = administrador;
	if (groupString[0] == 'o') group = owner;
	if (groupString[0] == 'u') group = user;
	
	errorCode = thcAddUserToGroup(nickname,group);
	if (errorCode != THC_OK)
	{
		thcGetHtmlErrorMessage(language,errorCode);
		mlCgiFreeResources();
		exit(THC_OK);
	}
	
	
	thcWebShowHeader();
	printf("<body>               \n");
	printf("<div class='content'>\n");
	printf("%s<br>               \n",menssage[0][language]);
	printf("                     \n");
	printf("</div>               \n");
	thcWebShowFooter();


	mlCgiFreeResources ();
	thcGenerateTextFile();

	return THC_OK;
}