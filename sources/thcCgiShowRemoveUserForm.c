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
#include "thcConfig.h"
#include "thcRenewCookie.h"

#include "mlcgi.h"                
char *menssages[][2]=
{
	{"Enter with user nickname : ","Entre com o nome de usuário : "},
	{"Are you sure you want to delete this account ? ","Você tem certeza que deseja apagar a conta ?"},
	{"yes","sim"},	
	{"no","não"}	
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
		mlCgiFreeResources();
		exit(THC_OK);			
	}	
	
	errorCode = thcRenewCookie(cookieName,&language);
	
	mlCgiEndHttpHeader();
	if (errorCode != THC_OK)
	{
		thcGetHtmlErrorMessage(language, errorCode);
		mlCgiFreeResources();
		exit(THC_OK);
	}
	
	
	/*Check for admin member*/
	if ((data.group != administrador) && (data.group != userAdmin) && (data.group != ownerAdmin) &&(data.group != root))
	{
		/*Show the user form*/
		thcWebShowHeader();
		
		printf("	<body>                                                                                          \n");
		printf("		<ul class=\"table\">                                                                        \n");
		printf("		     %s <br>                                                                                \n",menssages[1][language]);
		printf("			<form action='thcRemoveUser.cgi' method='post'><br>                                     \n");
		printf("				<input type='radio' name='thcConfirm' value='yes'>%s<br>                            \n",menssages[2][language]);  
		printf("                <input type='radio' name='thcConfirm' value='no' checked>%s<br>                     \n",menssages[3][language]);
		printf("				<input type=\"hidden\" name=\"thcNickname\" value=\"%s\">	                        \n",nickname);
		printf("				<input type=\"hidden\" name=\"thcCookieName\" value=\"%s\">	                        \n",cookieName);
		printf("				<input type=\"submit\" value=\"enter\">                                             \n");
		printf("			</form>                                                                                 \n");
		printf("		</ul>                                                                                       \n");
		
		thcWebShowFooter();
	}
	
	
	/*Show the admin form*/
	thcWebShowHeader();
		
	printf("	<body>                                                                                          \n");
	printf("		<ul class=\"table\">                                                                        \n");
	printf("		     %s <br>                                                                                \n",menssages[1][language]);
	printf("			<form action='thcRemoveUser.cgi' method='post'>                                         \n");
	printf("				%s<br><input type=\"text\" name=\"thcNickname\" value=\"%s\"><br>                   \n",menssages[0][language],nickname);
	printf("				<input type='radio' name='thcConfirm' value='yes'>%s<br>                            \n",menssages[2][language]);  
	printf("                <input type='radio' name='thcConfirm' value='no' checked>%s<br>                     \n",menssages[3][language]);
	printf("				<input type=\"hidden\" name=\"thcCookieName\" value=\"%s\">	                        \n",cookieName);
	printf("				<input type=\"submit\" value=\"enter\">                                             \n");
	printf("			</form>                                                                                 \n");
	printf("		</ul>                                                                                       \n");
	
	thcWebShowFooter();
	
	
	return THC_OK;
}