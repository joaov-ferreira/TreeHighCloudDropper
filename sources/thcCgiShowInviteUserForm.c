/*                                            
 * Universidade Federal do Rio de Janeiro     
 * Escola Politecnica                         
 * Departamento de Eletronica e de Computacao 
 * EEL270 - Computacao II - Turma 2012/2      
 * Prof. Marcelo Luiz Drumond Lanza           
 * Autor Joao Vitor Ferreira Duarte           
 *                                            
 * $Author: joao.duarte $                                   
 * $Date: 2013/04/06 18:55:09 $                                     
 * $Log: thcCgiShowInviteUserForm.c,v $
 * Revision 1.2  2013/04/06 18:55:09  joao.duarte
 * Final Revision for first part
 *
 * Revision 1.1  2013/03/26 21:16:01  joao.duarte
 * Initial revision
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
#include "thcRenewCookie.h"                   
#include "mlcgi.h"
                
char *menssages[][2]=
{
	{"Enter with your friend's data ","Entre com os dados de seu amigo"},
	{"Full name :","Nome completo :"},
	{"E-mail :","E-mail :"},	
	{"Retype the E-mail:","Digite novamente o e-mail:"},	
	{"en","br"}	
};                
                
                                              
int main (int argc, char **argv)
{
	environmentType enviro;
	thcErrorType errorCode;
	thcLanguageType language = english;
	thcUserDataType data;
	char nickname [THC_NICKNAME_MAXIMUM_LENGHT+1];
	char cookieName [THC_COOKIE_NAME_LENGHT + 1];
	
		
	if (mlCgiInitialize (&enviro))
		exit (THC_OK);

	if (enviro == commandLine)
	{
		mlCgiEndHttpHeader();
		thcGetTextErrorMessage(language,THC_ERROR_INVALID_INTERFACE);
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
		thcGetHtmlErrorMessage(language,errorCode);
		mlCgiFreeResources();
		exit(THC_OK);
	}
	
	
	/*Grab the user name*/
	thcSearchUser(nickname,&data);
	
	/*Show the form*/
	thcWebShowHeader();
	
	printf("	<body>                                                                                                                     \n");
	printf("		<ul class=\"table\">                                                                                                   \n");
	printf("			<form action='thcInviteUser.cgi' method='post'>                                                                    \n");
	printf("			    %s<br><br>                                                                                                     \n",menssages[0][language]);
	printf("				%s<br><INPUT TYPE=\"text\" NAME=\"thcUsername\" SIZE=\"25\" MAXLENGTH=\"100\"><br>                             \n",menssages[1][language]);
	printf("				%s<br><INPUT TYPE=\"text\" NAME=\"thcEmail\" SIZE=\"25\" MAXLENGTH=\"100\"><br>                                \n",menssages[2][language]);
	printf("				%s<br><INPUT TYPE=\"text\" NAME=\"thcConfirm\" SIZE=\"25\" MAXLENGTH=\"100\"><br>                              \n",menssages[3][language]);
	printf("				<input type=\"hidden\" name=\"thcInviterName\" value=\"%s\">	                                               \n",data.fullName);
	printf("				<input type=\"hidden\" name=\"thcCookieName\" value=\"%s\">	                                                   \n",cookieName);
	printf("				<input type=\"submit\" value=\"enter\">                                                                        \n");
	printf("			</form>                                                                                                            \n");
	printf("		</ul>                                                                                                                  \n");
	
	thcWebShowFooter();
	

	
	return THC_OK;
}                                          
                                              
/*$RCSfile: thcCgiShowInviteUserForm.c,v $*/                                  
