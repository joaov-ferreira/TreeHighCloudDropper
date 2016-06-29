/*
 * Universidade Federal do Rio de Janeiro
 * Escola Politecnica
 * Departamento de Eletronica e de Computacao
 *
 * Prof. Marcelo Luiz Drumond Lanza
 * EEL310 - Computacao II - Turma 2012/2
 * Autor Joao Vitor Ferreira Duarte 
 *     
 * $Author: joao.duarte $
 * $Date: 2013/04/06 18:55:09 $
 * $Log: thcChangeUsernameCgi.c,v $
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

#include "mlcgi.h"

char *menssages[][2]=
{
	{"Name successfully changed","Nome alterado com sucesso"},
	{"This is your new login : ","Este é o seu novo nome de usuario :"},	
	{"Click here to return","Clique aqui para retornar"}	
};

int main (int argc, char **argv)
{
	thcUserDataType data;
	environmentType enviro;
	thcErrorType errorCode;
	thcLanguageType language = THC_DEFAULT_LANGUAGE;
	char username[THC_FULL_NAME_MAXIMUM_LENGHT+1];
	char confirm [THC_FULL_NAME_MAXIMUM_LENGHT+1];
	char nickname[THC_NICKNAME_MAXIMUM_LENGHT+1];
	char cookieName[THC_COOKIE_NAME_LENGHT+1];
	char user[THC_NICKNAME_MAXIMUM_LENGHT + 1];


	if (mlCgiInitialize (&enviro))
		exit (THC_OK);

	if (enviro == commandLine)
	{
		thcGetTextErrorMessage(language, THC_ERROR_INVALID_INTERFACE);
		mlCgiFreeResources();
		exit (THC_OK);
	}

	mlCgiBeginHttpHeader ("text/html");
	
	errorCode = mlCgiGetFormStringNoNewLines ("thcUsername", username, THC_FULL_NAME_MAXIMUM_LENGHT);
	if (errorCode != ML_CGI_OK)
	{
		mlCgiEndHttpHeader();
		thcGetHtmlErrorMessage(language, THC_ERROR_ON_WEB_FORM);
		mlCgiFreeResources();
		exit(THC_OK);
	}
	
	errorCode = mlCgiGetFormStringNoNewLines ("thcConfirm", confirm, THC_FULL_NAME_MAXIMUM_LENGHT);
	if (errorCode != ML_CGI_OK)
	{
		mlCgiEndHttpHeader();
		thcGetHtmlErrorMessage(language, THC_ERROR_ON_WEB_FORM);
		mlCgiFreeResources();
		exit(THC_OK);
	}

	errorCode = mlCgiGetFormStringNoNewLines ("thcNickname", nickname, THC_NICKNAME_MAXIMUM_LENGHT);
	if (errorCode != ML_CGI_OK)
	{
		mlCgiEndHttpHeader();
		thcGetHtmlErrorMessage(language, THC_ERROR_ON_WEB_FORM);
		mlCgiFreeResources();
		exit(THC_OK);
	}

	errorCode = mlCgiGetFormStringNoNewLines ("thcCookieName",cookieName,THC_COOKIE_NAME_LENGHT);
	if (errorCode != ML_CGI_OK)
	{
		mlCgiEndHttpHeader();
		thcGetHtmlErrorMessage(language, THC_ERROR_ON_WEB_FORM);
		mlCgiFreeResources();
		exit(THC_OK);
	}

	errorCode = thcRenewCookie(cookieName, &language);
	mlCgiEndHttpHeader();
	if (errorCode != THC_OK)
	{
		thcGetHtmlErrorMessage(language, errorCode);
		mlCgiFreeResources();
		exit(THC_OK);		
	}
	
	
	/*Check for e-mail*/
	if (strcmp(username,confirm) != 0)
	{
		thcGetHtmlErrorMessage(language, THC_INVALID_ARGUMENT);
		mlCgiFreeResources();
		exit(THC_OK);
	}
	
	if ((strlen(confirm) == 0) || (strlen(username) == 0 ))
	{
		thcGetHtmlErrorMessage(language, THC_INVALID_ARGUMENT);
		mlCgiFreeResources();
		exit(THC_OK);
	}
    
    errorCode = thcSearchUser(nickname,&data);
    if (errorCode != THC_OK)
	{
		thcGetHtmlErrorMessage(language, errorCode);
		mlCgiFreeResources();
		exit(THC_OK);
	}
	
    strcpy(data.fullName,username);
    
    errorCode = thcCookieNameToNickname (cookieName, user);
    if (errorCode != THC_OK)
    {
		thcGetHtmlErrorMessage(language, errorCode);
		mlCgiFreeResources();
		exit(THC_OK);
	}
    
    errorCode = thcEditUserName(&data); 
	if (errorCode != THC_OK)
    {
		thcGetHtmlErrorMessage(language, errorCode);
		mlCgiFreeResources();
		exit(THC_OK);
	}
	
	thcWebShowHeader();
	
	printf("<body>                                         \n");
	printf("<div class='content'>                          \n");
	printf("                                               \n");
	printf("%s<br>                                         \n",menssages[0][language]);
	printf("%s %s<br>                                      \n",menssages[1][language],data.nickname);
	printf("<a href='thcHome.cgi?thcNickname=%s'>%s</a>    \n",user,menssages[2][language]);
	printf("</div>                                         \n");
	printf("                                               \n");


	
	thcWebShowFooter();

	mlCgiFreeResources();
	return THC_OK;
}

/*$RCSfile: thcChangeUsernameCgi.c,v $*/
