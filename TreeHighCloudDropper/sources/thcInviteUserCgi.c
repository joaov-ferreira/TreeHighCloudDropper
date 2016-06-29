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
 * $Log: thcInviteUserCgi.c,v $
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
#include "thcAddUser.h"
#include "thcConfig.h"
#include "thcRenewCookie.h"

#include "mlcgi.h"

char *menssages[][2]=
{
	{"User invited","Usuario convidado"},
};

int main (int argc, char **argv)
{
	thcUserDataType data;
	environmentType enviro;
	thcErrorType errorCode;
	thcLanguageType language = THC_DEFAULT_LANGUAGE;
	char username[THC_FULL_NAME_MAXIMUM_LENGHT+1];
	char inviter [THC_FULL_NAME_MAXIMUM_LENGHT+1];
	char email   [THC_EMAIL_MAXIMUM_LENGHT+1];
	char confirm [THC_EMAIL_MAXIMUM_LENGHT+1];
	char cookieName [THC_COOKIE_NAME_LENGHT + 1];

	if (mlCgiInitialize (&enviro))
		exit (THC_OK);

	if (enviro == commandLine)
	{
		thcGetTextErrorMessage(language,THC_ERROR_INVALID_INTERFACE);
		exit (THC_OK);
	}

	mlCgiBeginHttpHeader ("text/html");

	
	
	errorCode = mlCgiGetFormStringNoNewLines ("thcUsername", username, THC_FULL_NAME_MAXIMUM_LENGHT);
	if (errorCode != ML_CGI_OK)
	{
		mlCgiEndHttpHeader ();
		thcGetHtmlErrorMessage(language, THC_ERROR_ON_WEB_FORM);
		mlCgiFreeResources();
		exit(THC_OK);
	}
	
	errorCode = mlCgiGetFormStringNoNewLines ("thcEmail", email, THC_FULL_NAME_MAXIMUM_LENGHT);
	if (errorCode != ML_CGI_OK)
	{
		thcGetHtmlErrorMessage(language, THC_ERROR_ON_WEB_FORM);
		mlCgiFreeResources();
		exit(THC_OK);
	}

	errorCode = mlCgiGetFormStringNoNewLines ("thcConfirm", confirm, THC_NICKNAME_MAXIMUM_LENGHT);
	if (errorCode != ML_CGI_OK)
	{
		mlCgiEndHttpHeader ();
		thcGetHtmlErrorMessage(language, THC_ERROR_ON_WEB_FORM);
		mlCgiFreeResources();
		exit(THC_OK);
	}

	errorCode = mlCgiGetFormStringNoNewLines ("thcInviterName", inviter, THC_NICKNAME_MAXIMUM_LENGHT);
	if (errorCode != ML_CGI_OK)
	{
		mlCgiEndHttpHeader ();
		thcGetHtmlErrorMessage(language, THC_ERROR_ON_WEB_FORM);
		mlCgiFreeResources();
		exit(THC_OK);
	}

	errorCode = mlCgiGetFormStringNoNewLines ("thcCookieName",cookieName,THC_COOKIE_NAME_LENGHT);
	if (errorCode != ML_CGI_OK)
	{
		mlCgiEndHttpHeader ();
		thcGetHtmlErrorMessage(language, THC_ERROR_ON_WEB_FORM);
		mlCgiFreeResources();
		exit(THC_OK);
	}
	

	errorCode = thcRenewCookie(cookieName, &language);
	mlCgiEndHttpHeader ();
	if (errorCode != THC_OK)
	{
		thcGetHtmlErrorMessage(language, errorCode);
		mlCgiFreeResources();
		exit(THC_OK);
	}
	
	/*Check for e-mail*/
	if (strcmp(email,confirm) != 0)
	{
		thcGetHtmlErrorMessage(language,THC_ERROR_EMAIL);
		mlCgiFreeResources();
		exit(THC_OK);
		
	}
	
	if ((strlen(confirm) == 0) || (strlen(username) == 0 ))
	{
		thcGetHtmlErrorMessage(language,THC_INVALID_ARGUMENT);
		mlCgiFreeResources();
		exit(THC_OK);	
		
	}
    
    data.group = 4;
    strcpy(data.fullName,username);
    strcpy(data.email,email);
    
    errorCode = thcAddUser(&data);
	if (errorCode != THC_OK)
	{
		thcGetHtmlErrorMessage(language,errorCode);
		mlCgiFreeResources ();
		exit(THC_OK);		
	}
	
	errorCode = thcGenerateTextFile();
	if (errorCode != THC_OK)
	{
		thcGetHtmlErrorMessage(language,errorCode);
		mlCgiFreeResources ();
		exit(THC_OK);		
	}
	errorCode = thcInvitationMail(username, inviter,data.codedPassword,email,data.nickname,language);
	if (errorCode != THC_OK)
	{
		thcGetHtmlErrorMessage(language,THC_ERROR_EMAIL);
		mlCgiFreeResources ();
		exit(THC_OK);		
	}
	
	thcWebShowHeader();
	
	printf("<body>                                         \n");
	printf("<div class='content'>                          \n");
	printf("                                               \n");
	printf("%s<br>                                         \n",menssages[0][language]);
	printf("</div>                                         \n");
	printf("                                               \n");


	
	thcWebShowFooter();

	mlCgiFreeResources();
	thcGenerateTextFile();
	return THC_OK;
}

/*$RCSfile: thcInviteUserCgi.c,v $*/
