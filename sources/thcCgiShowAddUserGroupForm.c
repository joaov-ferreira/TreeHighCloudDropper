/*                                            
 * Universidade Federal do Rio de Janeiro     
 * Escola Politecnica                         
 * Departamento de Eletronica e de Computacao 
 * EEL270 - Computacao II - Turma 2012/2      
 * Prof. Marcelo Luiz Drumond Lanza           
 * Autor Joao Vitor Ferreira Duarte           
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
	{"Select user to change add to a group","Selecione o usuário para adicionar ao grupo"},
	{"Nickname","Nome de usuário"},
	{"Select the new group :","Selecione o grupo : "},		
	{"en","br"},	
	{"admin","administrador"},
	{"owner","proprietário"},
	{"user","usuárior"},
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
		/*Deny normal user to access this form*/
		thcWebShowHeader();
		thcGetHtmlErrorMessage(language, THC_PERMISSION_DENIED);
		thcWebShowFooter();
		
		return THC_OK;
	}	

	/*Show the admin form*/
	thcWebShowHeader();
	
	printf("	<body>                                                                                                                     \n");
	printf("		<ul class=\"table\">                                                                                                   \n");
	printf("			<form action='thcAddUserToGroup.cgi' method='post'>                                                                \n");
	printf("			    %s<br><br>                                                                                                     \n",menssages[0][language]);
	printf("				%s<br><input type=\"text\" name=\"thcNickname\" SIZE=\"25\" MAXLENGTH=\"100\"><br>                             \n",menssages[1][language]);
	printf("                <br>%s<br>                                                                                                     \n",menssages[2][language]);
	printf("                <select name='thcGroup'>                                                                                       \n");
	printf("                <option value='admin'>%s</option>                                                                              \n",menssages[4][language]);
	printf("                <option value='owner'>%s</option>                                                                              \n",menssages[5][language]);
	printf("                <option value='user' >%s</option>                                                                              \n",menssages[6][language]);
	printf("                </select>                                                                                                      \n");
	printf("				<input type=\"hidden\" name=\"thcCookieName\" value=\"%s\">	                                                   \n",cookieName);
	printf("				<input type=\"submit\" value=\"enter\">                                                                        \n");
	printf("			</form>                                                                                                            \n");
	printf("		</ul>                                                                                                                  \n");
	
	thcWebShowFooter();
	
	return THC_OK;
}                                           