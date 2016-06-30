/*
 * Universidade Federal do Rio de Janeiro
 * Escola Politecnica
 * Departamento de Eletronica e de Computacao
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

char *menssage [][2]=
{
	{"This looks to be your fisrt access, click here to change your password","Este parece ser seu primeiro acesso, clique aqui para trocar sua senha"},
	{"Successfully logged in","Logado com sucesso"},
	{"You have reseted your password, click here to set a new one","Voce resetou sua senha, clique aqui para criar uma nova"},
};

int main (int argc, char **argv)
{
	environmentType enviro;
	thcUserDataType data;       
	char cookieName [THC_COOKIE_NAME_LENGHT + 1];      
	char username [THC_NICKNAME_MAXIMUM_LENGHT + 1];
	char password [THC_PASSWORD_MAXIMUM_LENGHT + 1];
	thcErrorType errorCode;
	char cookieContent [THC_COOKIE_CONTENT_LENGHT+1];
	time_t expiration;
	char languageString[THC_LANGUAGE_MAXIMUM_LENGHT+1];
	thcLanguageType language = THC_DEFAULT_LANGUAGE;

	/*Initiate and check environment*/
	if (mlCgiInitialize (&enviro))
		exit (THC_OK);

	if (enviro == commandLine) 
	{
		thcGetTextErrorMessage(language, THC_ERROR_INVALID_INTERFACE);
		exit (THC_OK);
	}

	/*Web interface*/
	mlCgiBeginHttpHeader ("text/html");
	
	errorCode = mlCgiGetFormStringNoNewLines ("thcLanguage",languageString,THC_LANGUAGE_MAXIMUM_LENGHT);
	if (errorCode == ML_CGI_OK)
	{
		if (strcmp(languageString,"br") == 0) language = portuguese;
		if (strcmp(languageString,"en") == 0) language = english;	
	}
	
	
	errorCode = mlCgiGetFormStringNoNewLines ("thcUsername", username, THC_NICKNAME_MAXIMUM_LENGHT);
	if (errorCode != ML_CGI_OK)
	{
		thcGetHtmlErrorMessage(language, THC_ERROR_ON_WEB_FORM);
		exit(THC_OK);
	}
	
	errorCode = mlCgiGetFormStringNoNewLines ("thcPassword", password, THC_PASSWORD_MAXIMUM_LENGHT);
	if (errorCode != ML_CGI_OK)
	{
		thcGetHtmlErrorMessage(language, THC_ERROR_ON_WEB_FORM);
		exit(THC_OK);	
	}
	
	
	
	errorCode = thcUserLogin(username,password,&data);
	if (errorCode != THC_OK)
	{
		mlCgiEndHttpHeader ();
		thcGetHtmlErrorMessage(language,errorCode);
		exit(THC_OK);
	}	
	
	
	
	/*Login correct*/
	
	/*Generate the cookie content*/
	errorCode = thcGenerateCookieContent(cookieContent);
	if (errorCode != THC_OK)
	{
		mlCgiEndHttpHeader ();
		thcGetHtmlErrorMessage(language,errorCode);
		exit(THC_OK);		
	}
	
	/*send language information to cookie*/
	if (language == english) cookieContent[0] = 'e';
	if (language == portuguese) cookieContent[0] = 'b';
	
	/*Generate cookie name using the user ID*/
	if (sprintf(cookieName,THC_COOKIE_NAME_PRINTF_FORMAT,data.UID) != THC_COOKIE_NAME_LENGHT)
	{
		mlCgiEndHttpHeader ();
		thcGetHtmlErrorMessage(language,THC_ERROR_GENERATING_COOKIE_NAME);
		exit(THC_OK);			
	}
	
	
	/*send cookie*/
	expiration = time(NULL) + THC_COOKIE_EXPIRATION;
	
	errorCode = thcGenerateCookie(cookieName, &expiration, cookieContent, THC_DEFAULT_COOKIE_IP);
	if (errorCode != THC_OK)
	{
		mlCgiEndHttpHeader ();
		thcGetHtmlErrorMessage(language,errorCode);
		exit(THC_OK);		
	}
	
	/*Sends the cookie to user*/
	mlCgiSetCookie(cookieName, cookieContent, THC_COOKIE_EXPIRATION, NULL, NULL, NULL);
	mlCgiEndHttpHeader ();
	
	if (data.flag == abeyance)
	{
		
		thcWebShowHeader();
		     
		
		printf("<body>                                                                \n");          
		printf("  <div class=\"content\">                                             \n");                               
		printf("	<h1>%s</h1>                                                       \n",menssage[1][language]);                                                       
		printf("    <a href='thcCgiShowChangePasswordForm.cgi?thcNickname=%s'>%s</a>  \n",data.nickname,menssage[0][language]);
		printf("  </div>	                                                          \n");               
		printf("</body>                                                               \n");
		
			
		exit(THC_OK);
	}
	
	if (data.flag == passwordReset)
	{
		
		thcWebShowHeader();
		     
		
		printf("<body>                                                                \n");          
		printf("  <div class=\"content\">                                             \n");                               
		printf("	<h1>%s</h1>                                                       \n",menssage[1][language]);                                                       
		printf("    <a href='thcCgiShowChangePasswordForm.cgi?thcNickname=%s'>%s</a>  \n",data.nickname,menssage[2][language]);
		printf("  </div>	                                                          \n");               
		printf("</body>                                                               \n");
		
			
		exit(THC_OK);
	}
	
	
	/*Prints header*/		
	
	thcWebShowHeader();
	
	printf("	<body>                          \n");          
	printf("		<div class=\"content\">     \n");                               
	printf("			<h1>%s</h1>             \n",menssage[1][language]);                                                                                            
	printf("		</div>	                    \n");               
	printf("                                    \n");
	
	/*Prints menu*/
	thcWebShowMenu(language,data);
	                                                                                                                            
	/*Prints footer*/
	thcWebShowFooter();

	mlCgiFreeResources ();
	return THC_OK;
}