/*
 * Universidade Federal do Rio de Janeiro
 * Escola Politecnica
 * Departamento de Eletronica e de Computacao
 *
 * Prof. Marcelo Luiz Drumond Lanza
 * EEL310 - Computacao II - Turma 2012/2
 * Autor Joao Vitor Ferreira Duarte 
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
#include "thcChangeUserEmail.h"
#include "thcRenewCookie.h"

#include "mlcgi.h"

char *menssages[][2]=
{
	{"A confirmation code was sent to your new e-mail","Um código de comfirmação foi enviado para o seu novo e-mail"},
	{"And a deny code was sent to your old e-mail","E um código para cancelar esta operação foi enviado para o e-mail antigo"},	
	{"Click here to return","Clique aqui para retornar"}	
};

int main (int argc, char **argv)
{
	thcUserDataType data;
	environmentType enviro;
	thcErrorType errorCode;
	thcLanguageType language = THC_DEFAULT_LANGUAGE;
	char email   [THC_EMAIL_MAXIMUM_LENGHT+1];
	char confirm [THC_EMAIL_MAXIMUM_LENGHT+1];
	char nickname[THC_NICKNAME_MAXIMUM_LENGHT+1];
	char cookieName[THC_COOKIE_NAME_LENGHT+1];
	char user [THC_NICKNAME_MAXIMUM_LENGHT + 1];


	/*Clears trash from data*/
	memset(&data,0x00,sizeof(thcUserDataType));

	if (mlCgiInitialize (&enviro))
		exit (THC_OK);

	if (enviro == commandLine) /* programa executado via CLI */
	{
		thcGetTextErrorMessage(THC_DEFAULT_LANGUAGE, THC_ERROR_INVALID_INTERFACE);
		mlCgiFreeResources();
		exit (THC_OK);
	}

	/* programa executado via web */
	mlCgiBeginHttpHeader ("text/html");
	
	errorCode = mlCgiGetFormStringNoNewLines ("thcCookieName",cookieName,THC_COOKIE_NAME_LENGHT);
	if (errorCode != ML_CGI_OK)
	{
		mlCgiEndHttpHeader ();
		thcGetHtmlErrorMessage(language, THC_ERROR_ON_WEB_FORM);
		mlCgiFreeResources ();
		exit(THC_OK);		
	}
	

	errorCode = mlCgiGetFormStringNoNewLines ("thcEmail", email, THC_FULL_NAME_MAXIMUM_LENGHT);
	if (errorCode != ML_CGI_OK)
	{
		mlCgiEndHttpHeader ();
		thcGetHtmlErrorMessage(language, THC_ERROR_ON_WEB_FORM);
		mlCgiFreeResources ();
		exit(THC_OK);		
	}
	
	errorCode = mlCgiGetFormStringNoNewLines ("thcConfirm", confirm, THC_FULL_NAME_MAXIMUM_LENGHT);
	if (errorCode != ML_CGI_OK)
	{
		mlCgiEndHttpHeader ();
		thcGetHtmlErrorMessage(language, THC_ERROR_ON_WEB_FORM);
		mlCgiFreeResources ();
		exit(THC_OK);		
	}

	errorCode = mlCgiGetFormStringNoNewLines ("thcNickname", nickname, THC_NICKNAME_MAXIMUM_LENGHT);
	if (errorCode != ML_CGI_OK)
	{
		mlCgiEndHttpHeader ();
		thcGetHtmlErrorMessage(language, THC_ERROR_ON_WEB_FORM);
		mlCgiFreeResources ();
		exit(THC_OK);		
	}

	

	errorCode = thcRenewCookie(cookieName, &language);
	if (errorCode != THC_OK)
	{
		mlCgiEndHttpHeader();
		thcGetHtmlErrorMessage(language, errorCode);
		mlCgiFreeResources();
		exit(THC_OK);
	}	

	/* mlCgiBeginHttpHeader (NULL); */
	mlCgiEndHttpHeader ();
	
	/*Check for e-mail*/
	if (strcmp(email,confirm) != 0)
	{
		thcGetTextErrorMessage(language,THC_INVALID_ARGUMENT);
		exit(THC_OK);
		
	}
	
	if (strlen(email) == 0)
	{
		thcGetTextErrorMessage(language,THC_INVALID_ARGUMENT);
		exit(THC_OK);	
		
	}
    
    errorCode = thcSearchUser(nickname,&data);
    if (errorCode != THC_OK)
    {
		thcGetTextErrorMessage(language,errorCode);
		mlCgiFreeResources();
		exit (THC_OK);
	}
 
	
	data.UID = (unsigned long long)language;
	strcpy(data.email,email);
	
	errorCode = thcChangeUserEmail(&data);
	if (errorCode != THC_OK)
    {
		thcGetTextErrorMessage(language,errorCode);
		mlCgiFreeResources();
		exit (THC_OK);
	}
	
	/*Get the nickname*/
	errorCode = thcCookieNameToNickname (cookieName, user);
	if (errorCode != THC_OK)
	{
		thcGetTextErrorMessage(language,errorCode);
		mlCgiFreeResources();
		exit (THC_OK);
	}
	
	thcWebShowHeader();
	
	printf("<body>                                         \n");
	printf("<div class='content'>                          \n");
	printf("                                               \n");
	printf("%s<br>                                         \n",menssages[0][language]);
	printf("%s<br>                                         \n",menssages[1][language]);
	printf("<a href='thcHome.cgi?thcNickname='%s>%s</a>    \n",user,menssages[2][language]);
	printf("</div>                                         \n");
	printf("                                               \n");


	
	thcWebShowFooter();

	mlCgiFreeResources();
	return THC_OK;
}
