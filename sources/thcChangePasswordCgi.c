/*
 * Universidade Federal do Rio de Janeiro
 * Escola Politecnica
 * Departamento de Eletronica e de Computacao
 *
 * Prof. Marcelo Luiz Drumond Lanza
 * EEL310 - Computacao II - Turma 3112/2
 *
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
#include "thcChangeUserPassword.h"
#include "thcRenewCookie.h"

char *errorMensages [][2] =
{
	{"This program can only be used via web","Este programa só pode ser usado via web"},
	{"Incorrect User","Usuario Incorreto"},
		
};

char *menssage [][2]=
{
	{"Password Successfull changed","Senha alterada com sucesso"},
	{"Click here to return","Clique aqui para voltar"},
	
};

int main (int argc, char **argv)
{
	environmentType enviro;
	thcUserDataType data;   
	thcLanguageType language = THC_DEFAULT_LANGUAGE;         
	char password [THC_PASSWORD_MAXIMUM_LENGHT + 1];
	char passwordConfirm [THC_PASSWORD_MAXIMUM_LENGHT + 1];
	char nickname[THC_NICKNAME_MAXIMUM_LENGHT+1];
	char user [THC_NICKNAME_MAXIMUM_LENGHT + 1];
	char cookieName [THC_COOKIE_NAME_LENGHT + 1];
	thcErrorType errorCode;
	

	/*Initiate and check environment*/
	if (mlCgiInitialize (&enviro))
		exit (THC_OK);

	if (enviro == commandLine) 
	{
		printf ("%s\n",errorMensages[0][0]);
		exit (THC_OK);
	}

	/*Web interface*/
	mlCgiBeginHttpHeader ("text/html");
	
	errorCode = mlCgiGetFormStringNoNewLines ("thcNickname", nickname , THC_NICKNAME_MAXIMUM_LENGHT);
	if (errorCode != ML_CGI_OK)
	{
		mlCgiEndHttpHeader();
		thcGetHtmlErrorMessage(language, THC_ERROR_ON_WEB_FORM);
		mlCgiFreeResources ();	
		exit(THC_OK);
	}
	
	errorCode = mlCgiGetFormStringNoNewLines ("thcCookieName", cookieName , THC_COOKIE_NAME_LENGHT);
	if (errorCode != ML_CGI_OK)
	{
		mlCgiEndHttpHeader();
		thcGetHtmlErrorMessage(language, THC_ERROR_ON_WEB_FORM);
		mlCgiFreeResources ();	
		exit(THC_OK);
	}
	
	errorCode = mlCgiGetFormStringNoNewLines ("thcPassword", password, THC_PASSWORD_MAXIMUM_LENGHT);
	if (errorCode != ML_CGI_OK)
	{
		mlCgiEndHttpHeader();
		thcGetHtmlErrorMessage(language, THC_ERROR_ON_WEB_FORM);
		mlCgiFreeResources ();	
		exit(THC_OK);		
	}
	
	errorCode = mlCgiGetFormStringNoNewLines ("thcConfirm", passwordConfirm, THC_PASSWORD_MAXIMUM_LENGHT);
	if (errorCode != ML_CGI_OK)
	{
		mlCgiEndHttpHeader();
		thcGetHtmlErrorMessage(language, THC_ERROR_ON_WEB_FORM);
		mlCgiFreeResources ();	
		exit(THC_OK);		
	}
	
	errorCode = thcRenewCookie (cookieName, &language);
	mlCgiEndHttpHeader ();
	
	if (errorCode != THC_OK)
	{
		thcGetHtmlErrorMessage(language, errorCode);
		mlCgiFreeResources ();	
		exit(THC_OK);		
	}
	
	/*Check if password match*/
	if (strcmp(password, passwordConfirm) != 0)
	{
		thcGetHtmlErrorMessage(language, THC_INCORRECT_PASSWORD);
		mlCgiFreeResources ();	
		exit(THC_OK);		
	}
	
	errorCode = thcSearchUser(nickname,&data);	
	if (errorCode != THC_OK)
	{
		thcGetHtmlErrorMessage(language, errorCode);
		mlCgiFreeResources ();	
		exit(THC_OK);
	}
	
	strcpy(data.codedPassword,password);
	
	/*Change user password*/
	errorCode = thcChangeUserPassword(&data);
	if (errorCode != THC_OK)
	{
		thcGetHtmlErrorMessage(language, errorCode);
		mlCgiFreeResources ();	
		exit(THC_OK);
	}
	
	/*Get username*/
	errorCode = thcCookieNameToNickname(cookieName, user);
	if (errorCode != THC_OK)
	{
		thcGetHtmlErrorMessage(language, errorCode);
		mlCgiFreeResources ();	
		exit(THC_OK);
	}
	
	thcWebShowHeader();
	printf("<body>                                         \n");
	printf("<div class='content'>                          \n");
	printf("                                               \n");
	printf("%s<br>                                         \n",menssage[0][language]);
	printf("<a href='thcHome.cgi?thcNickname='%s>%s</a>    \n",user,menssage[1][language]);
	printf("</div>                                         \n");

	thcWebShowFooter();

	mlCgiFreeResources ();
	return THC_OK;
}
