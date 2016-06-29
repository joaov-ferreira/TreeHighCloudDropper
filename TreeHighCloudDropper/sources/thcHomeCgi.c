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
 * $Log: thcHomeCgi.c,v $
 * Revision 1.2  2013/04/06 18:55:09  joao.duarte
 * Final Revision for first part
 *
 * Revision 1.1  2013/03/21 23:15:27  joao.duarte
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
#include "thcConfig.h"
#include "thcRenewCookie.h"
                   
#include "mlcgi.h"
                
char *menssages[][2]=
{
	{"Full name :","Nome completo :"},
	{"E-mail :","E-mail :"},	
	{"You have 1 friend =D","Você tem 1 amigo =D"},
};                
                
                                              
int main (int argc, char **argv)
{
	environmentType enviro;
	thcErrorType errorCode;
	thcLanguageType language = english;
	thcUserDataType data;
	char nickname [THC_NICKNAME_MAXIMUM_LENGHT+1];
	char cookieName[THC_COOKIE_NAME_LENGHT + 1];
	
		
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
		mlCgiEndHttpHeader ();
		thcGetHtmlErrorMessage(language,THC_ERROR_ON_WEB_FORM);
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

	errorCode = thcRenewCookie(cookieName, &language);
	mlCgiEndHttpHeader();
	
	if (errorCode != THC_OK)
	{
		thcGetHtmlErrorMessage(language,errorCode);
		mlCgiFreeResources();
		exit(THC_OK);	
	}
	
	
	
	
	/*Grab the user data*/
	thcSearchUser(nickname,&data);
	
	/*Show home screen*/
	thcWebShowHeader();
	
	thcWebShowMenu(language,data);
	
	printf("	<body>                                               \n");
	printf("		<div class=\"content\">                          \n");
	printf("			    %s   %s<br>                              \n",menssages[0][language],data.fullName);
	printf("				%s   %s<br>                              \n",menssages[1][language],data.email);
	printf("				%s<br>                                   \n",menssages[2][language]);
	printf("		<img border='0' src='images/img01.jpg'>          \n");
	printf("			</form>                                      \n");
	printf("		</div>                                           \n");
	
	thcWebShowFooter();
	
	return THC_OK;
}
                                                                                        
/*$RCSfile: thcHomeCgi.c,v $*/                                  
