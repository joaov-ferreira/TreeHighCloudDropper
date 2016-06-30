/*                                            
 * Universidade Federal do Rio de Janeiro     
 * Escola Politecnica                         
 * Departamento de Eletronica e de Computacao 
 * EEL270 - Computacao II - Turma 2012/2      
 * Prof. Marcelo Luiz Drumond Lanza           
 * Autor Joao Vitor Ferreira Duarte           
 *
 *                                      
 */                                           
                                              
#include <stdlib.h>                           
#include <stdio.h>                            
#include <string.h>
                             
#include "thcConst.h"                       
#include "thcTypes.h"                       
#include "thcError.h"                       
#include "thcFunctions.h"                   
#include "mlcgi.h"
#include "thcRenewCookie.h"
                
char *menssages[][2]=
{
	{"Enter with the new full name","Entre com o nome completo"},
	{"Full name :","Nome completo :"},
	{"Retype the full name :","Confirme o nome :"},		
	{"en","br"},	
	{"Enter with the user nickname : ","Entre com o nome de usuario"}	
};                
                
                                              
int main (int argc, char **argv)
{
	environmentType enviro;
	thcErrorType errorCode;
	thcLanguageType language = THC_DEFAULT_LANGUAGE;
	thcUserDataType data;
	char nickname [THC_NICKNAME_MAXIMUM_LENGHT+1];
	char cookieName [THC_COOKIE_NAME_LENGHT + 1];
	
		
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
	
	errorCode = thcRenewCookie(cookieName, &language);
	
	mlCgiEndHttpHeader();
	if (errorCode != THC_OK)
	{
		thcGetHtmlErrorMessage(language, errorCode);
		mlCgiFreeResources();
		exit(THC_OK);
	}
	
	/*Grab the user name*/
	thcSearchUser(nickname,&data);
	
	
	/*Check for admin member*/
	if ((data.group != administrador) && (data.group != userAdmin) && (data.group != ownerAdmin) &&(data.group != root))
	{
		/*Show the user form*/
		thcWebShowHeader();
		
		printf("	<body>                                                                                                                     \n");
		printf("		<ul class=\"table\">                                                                                                   \n");
		printf("			<form action='thcChangeUsername.cgi' method='post'>                                                                \n");
		printf("			    %s<br><br>                                                                                                     \n",menssages[0][language]);
		printf("				%s<br><INPUT TYPE=\"text\" NAME=\"thcUsername\" SIZE=\"25\" MAXLENGTH=\"100\"><br>                             \n",menssages[1][language]);
		printf("				%s<br><INPUT TYPE=\"text\" NAME=\"thcConfirm\" SIZE=\"25\" MAXLENGTH=\"100\"><br>                              \n",menssages[2][language]);
		printf("				<input type=\"hidden\" name=\"thcNickname\" value=\"%s\">	                                                   \n",data.nickname);
		printf("				<input type=\"hidden\" name=\"thcCookieName\" value=\"%s\">	                                                   \n",cookieName);
		printf("				<input type=\"submit\" value=\"enter\">                                                                        \n");
		printf("			</form>                                                                                                            \n");
		printf("		</ul>                                                                                                                  \n");
		
		thcWebShowFooter();
		
		return THC_OK;
	}	

	/*Show the admin form*/
	thcWebShowHeader();
	
	printf("	<body>                                                                                                                     \n");
	printf("		<ul class=\"table\">                                                                                                   \n");
	printf("			<form action='thcChangeUsername.cgi' method='post'>                                                                \n");
	printf("			    %s<br><br>                                                                                                     \n",menssages[0][language]);
	printf("				%s<br><input type=\"text\" name=\"thcNickname\" value=\"%s\" SIZE=\"25\" MAXLENGTH=\"100\"><br>                \n",menssages[4][language],data.nickname);
	printf("				%s<br><INPUT TYPE=\"text\" NAME=\"thcUsername\" SIZE=\"25\" MAXLENGTH=\"100\"><br>                             \n",menssages[1][language]);
	printf("				%s<br><INPUT TYPE=\"text\" NAME=\"thcConfirm\" SIZE=\"25\" MAXLENGTH=\"100\"><br>                              \n",menssages[2][language]);
	printf("				<input type=\"hidden\" name=\"thcCookieName\" value=\"%s\">	                                                   \n",cookieName);
	printf("				<input type=\"submit\" value=\"enter\">                                                                        \n");
	printf("			</form>                                                                                                            \n");
	printf("		</ul>                                                                                                                  \n");
	
	thcWebShowFooter();
	
	return THC_OK;
}